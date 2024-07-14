#include "DataManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

void DataManager::cargarDatos(const std::string& rutaArchivo) {
    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error abriendo el archivo: " << rutaArchivo << std::endl;
        return;
    }
    std::string linea;

    // Saltar la primera línea (cabecera)
    std::getline(archivo, linea);

    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string imdb_id, titulo, sinopsis, tags_str, split, synopsis_source;

        // Usar getline para separar los campos
        std::getline(ss, imdb_id, ',');
        std::getline(ss, titulo, ',');
        std::getline(ss, sinopsis, ',');
        std::getline(ss, tags_str, ',');
        std::getline(ss, split, ',');
        std::getline(ss, synopsis_source, ',');

        // Verificar que los campos no estén vacíos antes de usar substr
        if (!titulo.empty() && titulo.size() > 1) {
            titulo = titulo.substr(1, titulo.size() - 2); // Eliminar comillas
        } else {
            titulo = "";
        }

        if (!sinopsis.empty() && sinopsis.size() > 1) {
            sinopsis = sinopsis.substr(1, sinopsis.size() - 2); // Eliminar comillas
        } else {
            sinopsis = "";
        }

        if (!tags_str.empty() && tags_str.size() > 1) {
            tags_str = tags_str.substr(1, tags_str.size() - 2); // Eliminar comillas
        } else {
            tags_str = "";
        }

        std::vector<std::string> tags;
        std::stringstream ss_tags(tags_str);
        std::string tag;
        while (std::getline(ss_tags, tag, ',')) {
            tags.push_back(tag);
        }

        peliculas.emplace_back(imdb_id, titulo, sinopsis, tags);
        peliculasIndexadas[titulo] = &peliculas.back();
    }
}

void DataManager::guardarPreferencias() {
    std::ofstream verMasTardeFile("ver_mas_tarde.txt");
    for (const auto& pelicula : verMasTarde) {
        verMasTardeFile << pelicula->getTitulo() << "\n";
    }
    verMasTardeFile.close();

    std::ofstream likesFile("likes.txt");
    for (const auto& pelicula : likes) {
        likesFile << pelicula->getTitulo() << "\n";
    }
    likesFile.close();
}

void DataManager::cargarPreferencias() {
    std::ifstream verMasTardeFile("ver_mas_tarde.txt");
    std::string titulo;
    while (std::getline(verMasTardeFile, titulo)) {
        verMasTarde.push_back(peliculasIndexadas[titulo]);
    }
    verMasTardeFile.close();

    std::ifstream likesFile("likes.txt");
    while (std::getline(likesFile, titulo)) {
        likes.push_back(peliculasIndexadas[titulo]);
    }
    likesFile.close();
}

std::vector<Pelicula*> DataManager::getVerMasTarde() const {
    return verMasTarde;
}

std::vector<Pelicula*> DataManager::getLikes() const {
    return likes;
}

std::vector<Pelicula>::iterator DataManager::begin() {
    return peliculas.begin();
}

std::vector<Pelicula>::iterator DataManager::end() {
    return peliculas.end();
}
