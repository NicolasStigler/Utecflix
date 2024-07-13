#include <iostream>
#include <fstream>
#include <vector>
#include "AlgoritmoDeBúsqueda.h"
#include "seleccion_y_likes.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Como usar: " << argv[0] << " <csv_name> <keyword>" << endl;
        return 1;
    }

    string filename = argv[1];
    string keyword = argv[2];

    vector<Movie> movies = readCSV(filename);

    vector<Movie> results = searchMovies(movies, keyword);

    ofstream outfile("output.txt");

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
        cout << "Selecciona una película (1-" << results.size() << "): ";
        cin >> choice;

        if (choice > 0 && choice <= results.size()) {
            displayMovieDetails(results[choice - 1]);
        } else {
            cout << "Opción inválida." << endl;
        }
    }

    // Guardar las películas marcadas como 'liked' y 'watch later' en un archivo? o donde los guardo xdd
    ofstream likedWatchLaterFile("liked_watch_later.txt");
    for (const auto& movie : movies) {
        if (movie.liked) {
            likedWatchLaterFile << "Liked: " << movie.title << endl;
        }
        if (movie.watchLater) {
            likedWatchLaterFile << "Watch Later: " << movie.title << endl;
        }
    }
    likedWatchLaterFile.close();

    outfile.close();

    return 0;
}
