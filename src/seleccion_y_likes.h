//
// Created by tamyk on 7/12/2024.
//

#ifndef UTECFLIX_SELECCION_Y_LIKES_H
#define UTECFLIX_SELECCION_Y_LIKES_H

#include <iostream>
#include <vector>
#include "AlgoritmoDeBúsqueda.h"

using namespace std;

// Función para mostrar detalles de una película y permitir marcarla como 'liked' o 'watch later'
void displayMovieDetails(Movie& movie) {
    cout << "IMDB ID: " << movie.imdb_id << endl;
    cout << "Title: " << movie.title << endl;
    cout << "Synopsis: " << movie.plot_synopsis << endl;
    cout << "Tags: " << movie.tags << endl;
    cout << "Synopsis source:" << movie.synopsis_source << endl;


    char choice;
    cout << "¿Te gusta esta película? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        movie.liked = true;
        cout << "Has añadido esta película a tus favoritos." << endl;
    }

    cout << "¿Quieres añadir esta película a 'Ver más tarde'? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        movie.watchLater = true;
        cout << "Película añadida a Ver más tarde." << endl;
    }
    cout << "-----------------------------" << endl;
}

#endif //UTECFLIX_SELECCION_Y_LIKES_H
