//
// Created by tamyk on 7/12/2024.
//

#ifndef UTECFLIX_SELECCION_Y_LIKES_H
#define UTECFLIX_SELECCION_Y_LIKES_H

#include <iostream>
#include <vector>
#include "AlgoritmoDeBúsqueda.h"
#include "MovieDatabase.h"

using namespace std;
void saveToFile(const std::string& imdb_id, const std::string& filename) {
    std::ofstream file(filename, std::ios_base::app);
    if (file.is_open()) {
        file << imdb_id << std::endl;
        file.close();
        std::cout << "IMDB ID " << imdb_id << " guardado en " << filename << std::endl;
    } else {
        std::cerr << "No se pudo abrir el archivo " << filename << " para escritura." << std::endl;
    }
}
// Función para mostrar detalles de una película y permitir marcarla como 'liked' o 'watch later'
void displayMovieDetails(Movie& movie) {
    cout << "IMDB ID: " << movie.imdb_id << endl;
    cout << "Title: " << movie.title << endl;
    cout << "Synopsis: " << movie.plot_synopsis << endl;
    cout << "Tags: " << movie.tags << endl;
    cout << "Synopsis source:" << movie.synopsis_source << endl;

    char likeChoice;
    std::cout << "Te gusta esta pelicula? (y/n): ";
    std::cin >> likeChoice;
    if (likeChoice == 'y' || likeChoice == 'Y') {
        MovieDatabase::getInstance()->markAsLiked(movie.imdb_id);
        std::cout << "Has anadido esta pelicula a tus favoritos." << std::endl;
        saveToFile(movie.imdb_id, "like.txt");
    }

    // Marcar como 'watch later'
    char watchLaterChoice;
    std::cout << "Quieres anadir esta pelicula a 'Ver mas tarde'? (y/n): ";
    std::cin >> watchLaterChoice;
    if (watchLaterChoice == 'y' || watchLaterChoice == 'Y') {
        MovieDatabase::getInstance()->markAsWatchLater(movie.imdb_id);
        std::cout << "Pelicula anadida a Ver mas tarde." << std::endl;
        saveToFile(movie.imdb_id, "watchLater.txt");
    }

    std::cout << "-----------------------------" << std::endl;
}


#endif //UTECFLIX_SELECCION_Y_LIKES_H
