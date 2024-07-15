#ifndef UTECFLIX_MOVIESDATABSE_H
#define UTECFLIX_MOVIESDATABSE_H

#include "AlgoritmoDeBúsqueda.h"
#include <optional>

class MovieDatabase {
private:
    static MovieDatabase* instance;
    std::vector<Movie> getMoviesFromFile(const std::string& filename);
    std::optional<Movie> getMovieById(const std::string& imdb_id);
    std::vector<Movie> movies;
    std::vector<Movie> likedMovies;
    std::vector<Movie> watchLaterMovies;

    // Constructor privado
    MovieDatabase() {}

public:
    // Obtener la instancia de la base de datos
    static MovieDatabase* getInstance() {
        if (instance == nullptr) {
            instance = new MovieDatabase();
        }
        return instance;
    }

    // Cargar películas desde un archivo CSV
    void loadMovies(const std::string& filename);

    // Obtener las películas
    std::vector<Movie> getMovies();

    // Buscar películas
    std::vector<Movie> search(const std::string& keyword);

    // Marcar una película como 'liked'
    void markAsLiked(const std::string& imdb_id);

    // Marcar una película como 'watch later'
    void markAsWatchLater(const std::string& imdb_id);

    // Obtener todas las películas marcadas como 'liked'
    std::vector<Movie> getLikedMovies();

    // Obtener todas las películas marcadas como 'watch later'
    std::vector<Movie> getWatchLaterMovies();
};

#endif //UTECFLIX_MOVIESDATABSE_H
