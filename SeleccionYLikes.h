#ifndef UTECFLIX_SELECCIONYLIKES_H
#define UTECFLIX_SELECCIONYLIKES_H

#include <iostream>
#include "AlgoritmoDeBúsqueda.h"
#include "MovieDatabase.h"

void saveToFile(const std::string& imdb_id, const std::string& filename);

void displayMovieDetails(Movie& movie);

#endif //UTECFLIX_SELECCIONYLIKES_H
