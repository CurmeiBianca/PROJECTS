package org.example.movieplatform.service;

import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Map;

@Service
public class MovieService {

    private final JdbcTemplate jdbcTemplate;

    public MovieService(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }

    // Returneaza toate filmele
    public List<Map<String, Object>> getAllMovies() {
        return jdbcTemplate.queryForList("SELECT * FROM get_all_movies()");
    }

    // Returneaza detalii film + actori
    public List<Map<String, Object>> getMovieDetails(int movieId) {
        return jdbcTemplate.queryForList(
                String.format("SELECT * FROM get_movie_details(%d)", movieId)
        );
    }

    // Returneaza istoricul unui client
    public List<Map<String, Object>> getClientHistory(int clientId) {
        return jdbcTemplate.queryForList(
                String.format("SELECT * FROM get_client_history(%d)", clientId)
        );
    }

    // Returneaza recomandari pentru client
    public List<Map<String, Object>> getRecommendations(int clientId) {
        return jdbcTemplate.queryForList(
                "SELECT rec_movie_id, rec_title, rec_category, rec_rating, rec_compatibility_score " +
                        "FROM get_movie_recommendations(" + clientId + ")"
        );
    }

    // Adauga o vizionare
    public void addToWatchlist(int clientId, int movieId, int versionId, int duration) {
        jdbcTemplate.execute(
                String.format(
                        "SELECT add_to_watchlist(%d, %d, %d, %d)",
                        clientId, movieId, versionId, duration
                )
        );
    }

    // Adauga o recenzie
    public void addReview(int clientId, int movieId, int vote, String comment,
                          boolean liked, boolean interesting,
                          boolean wouldRecommend, boolean wouldRewatch,
                          boolean goodActing) {
        jdbcTemplate.execute(
                String.format(
                        "SELECT add_review(%d, %d, %d, '%s', %b, %b, %b, %b, %b)",
                        clientId, movieId, vote, comment,
                        liked, interesting, wouldRecommend, wouldRewatch, goodActing
                )
        );
    }

    // Returneaza toti clientii
    public List<Map<String, Object>> getAllClients() {
        return jdbcTemplate.queryForList("SELECT * FROM clients ORDER BY client_id");
    }

    // Returneaza toate versiunile unui film
    public List<Map<String, Object>> getMovieVersions(int movieId) {
        return jdbcTemplate.queryForList(
                String.format("SELECT * FROM movie_versions WHERE movie_id = %d", movieId)
        );
    }
}