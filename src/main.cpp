#include <iostream>
#include "SearchingAlgorithm.h"
#include "MovieDatabase.h"
#include "LikesNWatchLater.h"

using namespace std;

int main(int argc, char* argv[]) {
    cout << "Iniciando el programa..." << endl;

    string filename = "mpst_full_data.csv";
    string keyword;

    if (argc == 2) {
        keyword = argv[1];
    } else if (argc == 3) {
        filename = argv[1];
        keyword = argv[2];
    } else {
        cerr << "Uso incorrecto. Formato correcto: " << argv[0] << " [<nombre_archivo_csv>] <palabra_clave>" << endl;
        return 1;
    }

    MovieDatabase* db = MovieDatabase::getInstance();
    db->loadMovies(filename);

    auto results = db->search(keyword);

    if (results.empty()) {
        cout << "No se encontraron resultados para la palabra clave: " << keyword << endl;
    } else {
        cout << "Resultados encontrados:" << endl;
        for (size_t i = 0; i < results.size(); ++i) {
            cout << i + 1 << ". " << results[i].title << " | Tags: " << results[i].tags << endl;
        }

        int choice;
        cout << "Selecciona una película (1-" << results.size() << "): ";
        cin >> choice;

        if (choice > 0 && choice <= results.size()) {
            Movie& selectedMovie = results[choice - 1];
            displayMovieDetails(selectedMovie); // Paso 2: Llamar a displayMovieDetails

            // Paso 3: Actualizar MovieDatabase si es necesario
            if (selectedMovie.liked) {
                db->markAsLiked(selectedMovie.imdb_id);
            }
            if (selectedMovie.watchLater) {
                db->markAsWatchLater(selectedMovie.imdb_id);
            }
        } else {
            cout << "Opción inválida." << endl;
        }
    }

    cout << "Programa finalizado." << endl;

    return 0;
}