//
// Created by sergi on 7/12/2024.
//
// Definicion de la estructura para guardar la data de la pelicula

#ifndef UTECFLIX_MOVIESDATABSE_H
#define UTECFLIX_MOVIESDATABSE_H

#include "AlgoritmoDeBúsqueda.h"


class MovieDatabase {
private:
    static MovieDatabase* instance;
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
    void loadMovies(const std::string& filename) {
        movies = readCSV(filename);
    }

    // Obtener las películas
    std::vector<Movie> getMovies() {
        return movies;
    }

    // Buscar películas
    std::vector<Movie> search(const std::string& keyword) {
        return searchMovies(movies, keyword);
    }

    // Marcar una película como 'liked'
    void markAsLiked(const std::string& imdb_id) {
        for (auto& movie : movies) {
            if (movie.imdb_id == imdb_id) {
                movie.liked = true;
                likedMovies.push_back(movie);
                return;
            }
        }
    }

    // Marcar una película como 'watch later'
    void markAsWatchLater(const std::string& imdb_id) {
        for (auto& movie : movies) {
            if (movie.imdb_id == imdb_id) {
                movie.watchLater = true;
                watchLaterMovies.push_back(movie);
                return;
            }
        }
    }

    // Obtener todas las películas marcadas como 'liked'
    std::vector<Movie> getLikedMovies() {
        return likedMovies;
    }

    // Obtener todas las películas marcadas como 'watch later'
    std::vector<Movie> getWatchLaterMovies() {
        return watchLaterMovies;
    }

};

MovieDatabase* MovieDatabase::instance = nullptr;

#endif //UTECFLIX_MOVIESDATABSE_H
