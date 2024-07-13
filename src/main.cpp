#include "MovieDatabase.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Como usar: " << argv[0] << " <csv_name> <keyword>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::string keyword = argv[2];

    // Obtener la instancia Singleton de MovieDatabase
    MovieDatabase* database = MovieDatabase::getInstance();

    // Cargar las películas desde el archivo CSV
    database->loadMovies(filename);

    // Buscar películas
    std::vector<Movie> results = database->search(keyword);

    std::ofstream outfile("output.txt");

    if (results.empty()) {
        outfile << "No se encontraron resultados." << std::endl;
    } else {
        outfile << "Resultados de \"" << keyword << "\":" << std::endl;
        for (const auto& movie : results) {
            outfile << "IMDB ID: " << movie.imdb_id << std::endl;
            outfile << "Title: " << movie.title << std::endl;
            outfile << "Plot Synopsis: " << movie.plot_synopsis << std::endl;
            outfile << "Tags: " << movie.tags << std::endl;
            outfile << "Split: " << movie.split << std::endl;
            outfile << "Synopsis Source: " << movie.synopsis_source << std::endl;
            outfile << "-----------------------------" << std::endl;
        }
    }

    outfile.close();

    return 0;
}
