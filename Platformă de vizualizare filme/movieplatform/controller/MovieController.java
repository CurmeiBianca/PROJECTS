package org.example.movieplatform.controller;

import org.example.movieplatform.service.MovieService;

import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Map;

@RestController
@RequestMapping("/api")
@CrossOrigin(origins = "*")
public class MovieController {

    private final MovieService movieService;

    public MovieController(MovieService movieService) {
        this.movieService = movieService;
    }

    // GET toate filmele
    @GetMapping("/movies")
    public List<Map<String, Object>> getAllMovies() {
        return movieService.getAllMovies();
    }

    // GET detalii film
    @GetMapping("/movies/{id}")
    public ResponseEntity<?> getMovieDetails(@PathVariable int id) {
        try {
            List<Map<String, Object>> result = movieService.getMovieDetails(id);
            return ResponseEntity.ok(result);
        } catch (Exception exception) {
            return ResponseEntity.status(HttpStatus.NOT_FOUND)
                    .body("Eroare: " + exception.getMessage());
        }
    }

    // GET istoricul unui client
    @GetMapping("/clients/{id}/history")
    public ResponseEntity<?> getClientHistory(@PathVariable int id) {
        try {
            List<Map<String, Object>> result = movieService.getClientHistory(id);
            return ResponseEntity.ok(result);
        } catch (Exception exception) {
            return ResponseEntity.status(HttpStatus.NOT_FOUND)
                    .body("Eroare: " + exception.getMessage());
        }
    }

    // GET recomandari pentru client
    @GetMapping("/clients/{id}/recommendations")
    public ResponseEntity<?> getRecommendations(@PathVariable int id) {
        try {
            List<Map<String, Object>> result = movieService.getRecommendations(id);
            return ResponseEntity.ok(result);
        } catch (Exception exception) {
            return ResponseEntity.status(HttpStatus.NOT_FOUND)
                    .body("Eroare: " + exception.getMessage());
        }
    }

    // GET toti clientii
    @GetMapping("/clients")
    public List<Map<String, Object>> getAllClients() {
        return movieService.getAllClients();
    }

    // GET versiunile unui film
    @GetMapping("/movies/{id}/versions")
    public List<Map<String, Object>> getMoviesVersions(@PathVariable int id) {
        return movieService.getMovieVersions(id);
    }

    // POST adauga vizionare
    @PostMapping("/watchlist")
    public ResponseEntity<?> addToWatchlist(@RequestBody Map<String, Integer> body) {
        try {
            movieService.addToWatchlist(
                    body.get("clientId"),
                    body.get("movieId"),
                    body.get("versionId"),
                    body.get("duration")
            );
            return ResponseEntity.ok("Vizionare adaugata cu succes!");
        } catch (Exception exception) {
            return ResponseEntity.status(HttpStatus.BAD_REQUEST)
                    .body("Eroare: " + exception.getMessage());
        }
    }

    // POST adauga recenzie
    @PostMapping("/reviews")
    public ResponseEntity<?> addReview(@RequestBody Map<String, Object> body) {
        try {
            movieService.addReview(
                    (Integer) body.get("clientId"),
                    (Integer) body.get("movieId"),
                    (Integer) body.get("vote"),
                    (String) body.get("comment"),
                    (Boolean) body.getOrDefault("liked", false),
                    (Boolean) body.getOrDefault("interesting", false),
                    (Boolean) body.getOrDefault("wouldRecommend", false),
                    (Boolean) body.getOrDefault("wouldRewatch", false),
                    (Boolean) body.getOrDefault("goodActing", false)
            );
            return ResponseEntity.ok("Recenzie adaugata cu succes!");
        } catch (Exception exception) {
            return ResponseEntity.status(HttpStatus.BAD_REQUEST)
                    .body("Eroare: " + exception.getMessage());
        }
    }
}
