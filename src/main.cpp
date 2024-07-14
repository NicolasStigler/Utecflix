#include <iostream>
#include <fstream>
#include <vector>
#include "AlgoritmoDeBúsqueda.h"
#include "seleccion_y_likes.h"

int main() {
    std::string filename = "mpst_full_data.csv";
    std::string keyword;

    std::cout << "Ingrese la palabra a buscar: ";
    std::cin >> keyword;

    std::vector<Movie> movies = readCSV(filename);

    std::vector<Movie> results = searchMovies(movies, keyword);

    std::ofstream outfile("output.txt");

    if (results.empty()) {
        outfile << "No se encontraron resultados." << std::endl;
    } else {
        outfile << "Resultados de \"" << keyword << "\":" << std::endl;
        for (size_t i = 0; i < results.size(); ++i) {
            outfile << "Opción " << i + 1 << ":" << std::endl;
            outfile << "IMDB ID: " << results[i].imdb_id << std::endl;
            outfile << "Title: " << results[i].title << std::endl;
            outfile << "Tags: " << results[i].tags << std::endl;
            outfile << "-----------------------------" << std::endl;
        }
        
        int choice;
        cout << "Selecciona una película (1-" << results.size() << "): ";
        cin >> choice;

        if (choice > 0 && choice <= results.size()) {
            displayMovieDetails(results[choice - 1]);
        } else {
            cout << "Opción inválida." << endl;
        }
    }

    // Guardar las películas marcadas como 'liked' y 'watch later' en un archivo? o donde los guardo xdd
    std::ofstream likedWatchLaterFile("liked_watch_later.txt");
    for (const auto& movie : movies) {
        if (movie.liked) {
            likedWatchLaterFile << "Liked: " << movie.title << std::endl;
        }
        if (movie.watchLater) {
            likedWatchLaterFile << "Watch Later: " << movie.title << std::endl;
        }
    }
    likedWatchLaterFile.close();

    outfile.close();

    return 0;
}
