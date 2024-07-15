#include "SeleccionYLikes.h"

// Definiciones de funciones

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

void displayMovieDetails(Movie& movie) {
    std::cout << "IMDB ID: " << movie.imdb_id << std::endl;
    std::cout << "Title: " << movie.title << std::endl;
    std::cout << "Plot Synopsis: " << movie.plot_synopsis << std::endl;
    std::cout << "Tags: " << movie.tags << std::endl;
    std::cout << "Split: " << movie.split << std::endl;
    std::cout << "Synopsis Source: " << movie.synopsis_source << std::endl;
}
