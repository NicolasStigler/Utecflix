#include <iostream>
#include <fstream>
#include <vector>
#include "AlgoritmoDeBúsqueda.h"
#include "seleccion_y_likes.h"

using namespace std;

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


int main(int argc, char* argv[]) {
    std::string filename = "mpst_full_data.csv";
    std::string keyword;

    std::cout << "Ingrese la palabra a buscar: ";
    std::cin >> keyword;

    std::vector<Movie> movies = readCSV(filename);

    std::vector<Movie> results = searchMovies(movies, keyword);

    std::ofstream outfile("output.txt");


    if (results.empty()) {
        outfile << "No se encontraron resultados." << endl;
    } else {
        outfile << "Resultados de \"" << keyword << "\":" << endl;
        for (size_t i = 0; i < results.size(); ++i) {
            outfile << "Opción " << i + 1 << ":" << endl;
            outfile << "IMDB ID: " << results[i].imdb_id << endl;
            outfile << "Title: " << results[i].title << endl;
            outfile << "Tags: " << results[i].tags << endl;
            outfile << "-----------------------------" << endl;
        }

        int choice;
        cout << "Selecciona una pelicula (1-" << results.size() << "): ";
        cin >> choice;

        if (choice > 0 && choice <= results.size()) {
            displayMovieDetails(results[choice - 1]);
        } else {
            cout << "Opcion invalida." << endl;
        }
    }

    std::cout << "Deseas ver tus peliculas marcadas como 'liked'? (y/n)" ;
    char showLikedChoice;
    std::cin >> showLikedChoice;
    if (showLikedChoice == 'y' || showLikedChoice == 'Y') {
        showLikedMovies("like.txt");
    }

    std::cout << "Deseas ver tus películas marcadas para 'ver más tarde'? (y/n)";
    char showWatchLaterChoice;
    std::cin >> showWatchLaterChoice;
    if (showWatchLaterChoice == 'y' || showWatchLaterChoice == 'Y') {
        showWatchLaterMovies("wachLater.txt");
    }

    outfile.close();

    return 0;
}
