-- Stergem tabelele daca exista deja (pentru a putea rerula scriptul)
DROP TABLE IF EXISTS reviews CASCADE;
DROP TABLE IF EXISTS watchlist CASCADE;
DROP TABLE IF EXISTS movie_versions CASCADE;
DROP TABLE IF EXISTS movie_actors CASCADE;
DROP TABLE IF EXISTS actors CASCADE;
DROP TABLE IF EXISTS clients CASCADE;
DROP TABLE IF EXISTS movies CASCADE;

-- 1. Tabelul movies
CREATE TABLE movies (
	movie_id SERIAL PRIMARY KEY,
	title VARCHAR(200) NOT NULL,
	description TEXT,
	category VARCHAR(50) NOT NULL,
	release_date DATE,
	rating NUMERIC(3,2) DEFAULT 0.00,
	CONSTRAINT chk_rating CHECK (rating >= 0 AND rating <= 10)
);

-- 2. Tabelul actors
CREATE TABLE actors (
	actor_id SERIAL PRIMARY KEY,
	stage_name VARCHAR(100),
	first_name VARCHAR(100) NOT NULL,
	last_name VARCHAR(100) NOT NULL,
	birth_date DATE
);

-- 3. Tabelul movie_actors (asociere many-to-many)
CREATE TABLE movie_actors (
	movie_id INT NOT NULL,
	actor_id INT NOT NULL,
	role VARCHAR(100),
	comments TEXT,
	PRIMARY KEY (movie_id, actor_id),
	FOREIGN KEY (movie_id) REFERENCES movies(movie_id) ON DELETE CASCADE,
	FOREIGN KEY (actor_id) REFERENCES actors(actor_id) ON DELETE CASCADE
);

-- 4. Tabelul clients
CREATE TABLE clients (
	client_id SERIAL PRIMARY KEY,
	first_name VARCHAR(100) NOT NULL,
	last_name VARCHAR(100) NOT NULL,
	phone VARCHAR(20),
	address VARCHAR(200),
	city VARCHAR(100),
	email VARCHAR(150) UNIQUE,
	mobile VARCHAR(20)
);

-- 5. Tabelul movie_versions
CREATE TABLE movie_versions (
	version_id SERIAL PRIMARY KEY,
	movie_id INT NOT NULL,
    format VARCHAR(50) NOT NULL,
    resolution VARCHAR(20),
    language VARCHAR(50) NOT NULL,
    FOREIGN KEY (movie_id) REFERENCES movies(movie_id) ON DELETE CASCADE
);

-- 6. Tabelul watchlist
CREATE TABLE watchlist (
    watch_id SERIAL PRIMARY KEY,
    client_id INT NOT NULL,
    movie_id INT NOT NULL,
    version_id INT NOT NULL,
    watch_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    duration_minutes INT,
    status VARCHAR(20) DEFAULT 'completed',
    CONSTRAINT chk_status CHECK (status IN ('completed', 'in_progress', 'abandoned')),
    FOREIGN KEY (client_id) REFERENCES clients(client_id) ON DELETE CASCADE,
    FOREIGN KEY (movie_id) REFERENCES movies(movie_id) ON DELETE CASCADE,
    FOREIGN KEY (version_id) REFERENCES movie_versions(version_id) ON DELETE CASCADE
);

-- 7. Tabelul reviews
CREATE TABLE reviews (
    review_id SERIAL PRIMARY KEY,
    client_id INT NOT NULL,
    movie_id INT NOT NULL,
    vote INT,
    comment TEXT,
    liked BOOLEAN DEFAULT FALSE,
    disliked BOOLEAN DEFAULT FALSE,
    interesting BOOLEAN DEFAULT FALSE,
    emotional BOOLEAN DEFAULT FALSE,
    boring BOOLEAN DEFAULT FALSE,
    would_recommend BOOLEAN DEFAULT FALSE,
    would_rewatch BOOLEAN DEFAULT FALSE,
    good_acting BOOLEAN DEFAULT FALSE,
    weak_script BOOLEAN DEFAULT FALSE,
    review_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT chk_vote CHECK (vote >= 1 AND vote <= 10),
    CONSTRAINT uq_client_movie UNIQUE (client_id, movie_id),
    FOREIGN KEY (client_id) REFERENCES clients(client_id) ON DELETE CASCADE,
    FOREIGN KEY (movie_id) REFERENCES movies(movie_id) ON DELETE CASCADE
);