#include <iostream>
#include <fstream>
#include "MovieDatabase.h"
#include "SeleccionYLikes.h"

// Función para mostrar películas marcadas como 'liked' desde el archivo
void showLikedMovies(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << filename << std::endl;
        return;
    }

    std::string imdb_id;
    std::cout << "Peliculas marcadas como 'liked':" << std::endl;
    while (std::getline(file, imdb_id)) {
        std::cout << "IMDB ID: " << imdb_id << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }

    file.close();
}

// Función para mostrar películas marcadas como 'watch later' desde el archivo
void showWatchLaterMovies(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << filename << std::endl;
        return;
    }

    std::string imdb_id;
    std::cout << "Peliculas marcadas para 'ver mas tarde':" << std::endl;
    while (std::getline(file, imdb_id)) {

        std::cout << "IMDB ID: " << imdb_id << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }

    file.close();
}

int main() {
    std::string filename = "mpst_full_data.csv";
    std::string keyword;

    // Obtener la instancia Singleton de MovieDatabase
    MovieDatabase* database = MovieDatabase::getInstance();

    // Cargar las películas desde el archivo CSV
    database->loadMovies(filename);

    std::cout << "Ingrese la palabra a buscar: ";
    std::cin >> keyword;

    // Buscar películas
    std::vector<Movie> results = database->search(keyword);

    std::ofstream outfile("output.txt");

    if (results.empty()) {
        outfile << "No se encontraron resultados." << std::endl;
    } else {
        outfile << "Resultados de \"" << keyword << "\":" << std::endl;
        for (size_t i = 0; i < results.size(); i++) {
            outfile << "Opción " << i + 1 << ":" << std::endl;
            outfile << "IMDB ID: " << results[i].imdb_id << std::endl;
            outfile << "Title: " << results[i].title << std::endl;
            outfile << "Tags: " << results[i].tags << std::endl;
            outfile << "-----------------------------" << std::endl;
        }

        int choice;
        std::cout << "Selecciona una pelicula (1-" << results.size() << "): ";
        std::cin >> choice;

        if (choice > 0 && choice <= results.size()) {
            displayMovieDetails(results[choice - 1]);
        } else {
            std::cout << "Opcion invalida." << std::endl;
        }
    }

    std::cout << "Deseas ver tus peliculas marcadas como 'liked'? (y/n):" ;
    char showLikedChoice;
    std::cin >> showLikedChoice;
    if (showLikedChoice == 'y' || showLikedChoice == 'Y') {
        showLikedMovies("like.txt");
    }

    std::cout << "Deseas ver tus peliculas marcadas para 'ver mas tarde'? (y/n):";
    char showWatchLaterChoice;
    std::cin >> showWatchLaterChoice;
    if (showWatchLaterChoice == 'y' || showWatchLaterChoice == 'Y') {
        showWatchLaterMovies("watchLater.txt");
    }

    outfile.close();

    return 0;
}
