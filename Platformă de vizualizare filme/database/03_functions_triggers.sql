-- ================================================
-- TRIGGER 1: Actualizare automata rating film
-- Se executa dupa INSERT sau UPDATE pe reviews
-- ================================================
CREATE OR REPLACE FUNCTION update_movie_rating()
RETURNS TRIGGER AS $$
BEGIN
    UPDATE movies
    SET rating = (
        SELECT ROUND(AVG(vote)::NUMERIC, 2)
        FROM reviews
        WHERE movie_id = NEW.movie_id
        AND vote IS NOT NULL
    )
    WHERE movie_id = NEW.movie_id;
    
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_update_rating
AFTER INSERT OR UPDATE ON reviews
FOR EACH ROW
EXECUTE FUNCTION update_movie_rating();

-- ================================================
-- TRIGGER 2: Verificare vizionare inainte de review
-- Un client nu poate recenza un film nevizionat
-- ================================================
CREATE OR REPLACE FUNCTION check_watch_before_review()
RETURNS TRIGGER AS $$
DECLARE
    v_watch_count INT;
BEGIN
    SELECT COUNT(*) INTO v_watch_count
    FROM watchlist
    WHERE client_id = NEW.client_id
    AND movie_id = NEW.movie_id;
    
    IF v_watch_count = 0 THEN
        RAISE EXCEPTION 'Clientul cu id % nu a vizionat filmul cu id %. Nu se poate lasa o recenzie!', 
            NEW.client_id, NEW.movie_id;
    END IF;
    
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_check_watch_before_review
BEFORE INSERT ON reviews
FOR EACH ROW
EXECUTE FUNCTION check_watch_before_review();

-- ================================================
-- FUNCTIE 1: Returneaza toate filmele
-- ================================================
CREATE OR REPLACE FUNCTION get_all_movies()
RETURNS TABLE (
    movie_id INT,
    title VARCHAR,
    category VARCHAR,
    release_date DATE,
    rating NUMERIC
) AS $$
BEGIN
    RETURN QUERY
    SELECT m.movie_id, m.title, m.category, m.release_date, m.rating
    FROM movies m
    ORDER BY m.rating DESC;
END;
$$ LANGUAGE plpgsql;

-- ================================================
-- FUNCTIE 2: Detalii film + actori
-- ================================================
CREATE OR REPLACE FUNCTION get_movie_details(p_movie_id INT)
RETURNS TABLE (
    title VARCHAR,
    description TEXT,
    category VARCHAR,
    release_date DATE,
    rating NUMERIC,
    actor_name VARCHAR,
    role VARCHAR
) AS $$
BEGIN
    IF NOT EXISTS (SELECT 1 FROM movies WHERE movie_id = p_movie_id) THEN
        RAISE EXCEPTION 'Filmul cu id % nu exista in baza de date!', p_movie_id;
    END IF;

    RETURN QUERY
    SELECT 
        m.title, m.description, m.category, m.release_date, m.rating,
        COALESCE(a.stage_name, a.first_name || ' ' || a.last_name)::VARCHAR AS actor_name,
        ma.role
    FROM movies m
    LEFT JOIN movie_actors ma ON m.movie_id = ma.movie_id
    LEFT JOIN actors a ON ma.actor_id = a.actor_id
    WHERE m.movie_id = p_movie_id;
END;
$$ LANGUAGE plpgsql;

-- ================================================
-- FUNCTIE 3: Adauga vizionare
-- ================================================
CREATE OR REPLACE FUNCTION add_to_watchlist(
    p_client_id INT,
    p_movie_id INT,
    p_version_id INT,
    p_duration_minutes INT
)
RETURNS VOID AS $$
BEGIN
    IF NOT EXISTS (SELECT 1 FROM clients WHERE client_id = p_client_id) THEN
        RAISE EXCEPTION 'Clientul cu id % nu exista!', p_client_id;
    END IF;

    IF NOT EXISTS (SELECT 1 FROM movies WHERE movie_id = p_movie_id) THEN
        RAISE EXCEPTION 'Filmul cu id % nu exista!', p_movie_id;
    END IF;

    IF NOT EXISTS (SELECT 1 FROM movie_versions WHERE version_id = p_version_id) THEN
        RAISE EXCEPTION 'Versiunea cu id % nu exista!', p_version_id;
    END IF;

    INSERT INTO watchlist (client_id, movie_id, version_id, duration_minutes, status)
    VALUES (p_client_id, p_movie_id, p_version_id, p_duration_minutes, 'completed');
END;
$$ LANGUAGE plpgsql;

-- ================================================
-- FUNCTIE 4: Adauga recenzie
-- ================================================
CREATE OR REPLACE FUNCTION add_review(
    p_client_id INT,
    p_movie_id INT,
    p_vote INT,
    p_comment TEXT,
    p_liked BOOLEAN,
    p_interesting BOOLEAN,
    p_would_recommend BOOLEAN,
    p_would_rewatch BOOLEAN,
    p_good_acting BOOLEAN
)
RETURNS VOID AS $$
BEGIN
    IF NOT EXISTS (SELECT 1 FROM clients WHERE client_id = p_client_id) THEN
        RAISE EXCEPTION 'Clientul cu id % nu exista!', p_client_id;
    END IF;

    IF EXISTS (SELECT 1 FROM reviews WHERE client_id = p_client_id AND movie_id = p_movie_id) THEN
        RAISE EXCEPTION 'Clientul cu id % a lasat deja o recenzie pentru filmul cu id %!', 
            p_client_id, p_movie_id;
    END IF;

    INSERT INTO reviews (
        client_id, movie_id, vote, comment,
        liked, interesting, would_recommend, would_rewatch, good_acting
    )
    VALUES (
        p_client_id, p_movie_id, p_vote, p_comment,
        p_liked, p_interesting, p_would_recommend, p_would_rewatch, p_good_acting
    );
END;
$$ LANGUAGE plpgsql;

-- ================================================
-- FUNCTIE 5: Istoricul vizionarilor unui client
-- ================================================
CREATE OR REPLACE FUNCTION get_client_history(p_client_id INT)
RETURNS TABLE (
    movie_title VARCHAR,
    category VARCHAR,
    watch_date TIMESTAMP,
    duration_minutes INT,
    status VARCHAR,
    vote INT,
    comment TEXT
) AS $$
BEGIN
    IF NOT EXISTS (SELECT 1 FROM clients WHERE client_id = p_client_id) THEN
        RAISE EXCEPTION 'Clientul cu id % nu exista!', p_client_id;
    END IF;

    RETURN QUERY
    SELECT 
        m.title,
        m.category,
        w.watch_date,
        w.duration_minutes,
        w.status,
        r.vote,
        r.comment
    FROM watchlist w
    JOIN movies m ON w.movie_id = m.movie_id
    LEFT JOIN reviews r ON r.client_id = w.client_id AND r.movie_id = w.movie_id
    WHERE w.client_id = p_client_id
    ORDER BY w.watch_date DESC;
END;
$$ LANGUAGE plpgsql;

-- ================================================
-- FUNCTIE 6: Recomandare filme 
-- Recomanda filme bazat pe categoriile preferate
-- ale clientului, excluzand filmele deja vazute
-- ================================================
CREATE OR REPLACE FUNCTION get_movie_recommendations(p_client_id INT)
RETURNS TABLE (
    rec_movie_id INT,
    rec_title VARCHAR,
    rec_category VARCHAR,
    rec_rating NUMERIC,
    rec_compatibility_score NUMERIC
) AS $$
DECLARE
    v_watch_count INT;
BEGIN
    IF NOT EXISTS (SELECT 1 FROM clients WHERE client_id = p_client_id) THEN
        RAISE EXCEPTION 'Clientul cu id % nu exista!', p_client_id;
    END IF;

    SELECT COUNT(*) INTO v_watch_count
    FROM watchlist
    WHERE client_id = p_client_id;

    IF v_watch_count = 0 THEN
        RETURN QUERY
        SELECT m.movie_id, m.title, m.category, m.rating, m.rating
        FROM movies m
        ORDER BY m.rating DESC
        LIMIT 5;
        RETURN;
    END IF;

    RETURN QUERY
    SELECT
        m.movie_id,
        m.title,
        m.category,
        m.rating,
        ROUND((m.rating * cs.watch_count * cs.avg_vote / 10)::NUMERIC, 2)
    FROM movies m
    JOIN (
        SELECT
            mv.category,
            COUNT(*) AS watch_count,
            COALESCE(AVG(r.vote), 5) AS avg_vote
        FROM watchlist w
        JOIN movies mv ON w.movie_id = mv.movie_id
        LEFT JOIN reviews r ON r.client_id = w.client_id AND r.movie_id = w.movie_id
        WHERE w.client_id = p_client_id
        GROUP BY mv.category
    ) cs ON m.category = cs.category
    WHERE m.movie_id NOT IN (
        SELECT movie_id FROM watchlist WHERE client_id = p_client_id
    )
    ORDER BY rec_compatibility_score DESC, rec_rating DESC
    LIMIT 5;
END;
$$ LANGUAGE plpgsql;