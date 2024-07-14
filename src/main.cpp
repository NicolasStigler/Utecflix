#include <iostream>
#include "DataManager.h"
#include "Recommender.h"

using namespace std;

void mostrarVerMasTarde() {
    const auto& verMasTarde = DataManager::getInstance().getVerMasTarde();
    cout << "Peliculas en Ver Mas Tarde:\n";
    for (const auto& pelicula : verMasTarde) {
        cout << "Titulo: " << pelicula->getTitulo() << "\n";
        cout << "Sinopsis: " << pelicula->getSinopsis() << "\n\n";
    }
}

void mostrarRecomendaciones() {
    Recommender recommender;
    const auto& likes = DataManager::getInstance().getLikes();
    auto recomendaciones = recommender.recomendarPeliculas(likes);
    cout << "Recomendaciones basadas en tus gustos:\n";
    for (const auto& pelicula : recomendaciones) {
        cout << "Titulo: " << pelicula->getTitulo() << "\n";
        cout << "Sinopsis: " << pelicula->getSinopsis() << "\n\n";
    }
}

int main() {
    // Cargar las películas desde el archivo CSV
    string rutaArchivo = "mpst_full_data.csv" ;
    cout << "Intentando abrir el archivo: " << rutaArchivo << endl;
    DataManager::getInstance().cargarDatos(rutaArchivo);

    // Cargar preferencias del usuario
    DataManager::getInstance().cargarPreferencias();

    // Mostrar películas en "Ver Más Tarde"
    mostrarVerMasTarde();

    // Mostrar recomendaciones
    mostrarRecomendaciones();

    // Guardar preferencias al finalizar el programa
    DataManager::getInstance().guardarPreferencias();

    return 0;
}
