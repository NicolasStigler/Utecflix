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

