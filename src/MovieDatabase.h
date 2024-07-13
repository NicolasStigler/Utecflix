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


};

MovieDatabase* MovieDatabase::instance = nullptr;

#endif //UTECFLIX_MOVIESDATABSE_H
