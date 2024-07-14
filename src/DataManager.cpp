#include "DataManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

void DataManager::cargarDatos(const string& rutaArchivo) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cerr << "Error abriendo el archivo: " << rutaArchivo << endl;
        return;
    }
    string linea;

    // Saltar la primera línea (cabecera)
    getline(archivo, linea);

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string imdb_id, titulo, sinopsis, tags_str, split, synopsis_source;

        getline(ss, imdb_id, ',');
        getline(ss, titulo, ',');
        getline(ss, sinopsis, ',');
        getline(ss, tags_str, ',');
        getline(ss, split, ',');
        getline(ss, synopsis_source, ',');

        // Eliminar comillas de los campos de texto
        titulo = titulo.substr(1, titulo.size() - 2);
        sinopsis = sinopsis.substr(1, sinopsis.size() - 2);
        tags_str = tags_str.substr(1, tags_str.size() - 2);

        vector<string> tags;
        stringstream ss_tags(tags_str);
        string tag;
        while (getline(ss_tags, tag, ',')) {
            tags.push_back(tag);
        }

        peliculas.emplace_back(imdb_id, titulo, sinopsis, tags);
        peliculasIndexadas[titulo] = &peliculas.back();
    }
}

void DataManager::guardarPreferencias() {
    ofstream verMasTardeFile("ver_mas_tarde.txt");
    for (const auto& pelicula : verMasTarde) {
        verMasTardeFile << pelicula->getTitulo() << "\n";
    }
    verMasTardeFile.close();

    ofstream likesFile("likes.txt");
    for (const auto& pelicula : likes) {
        likesFile << pelicula->getTitulo() << "\n";
    }
    likesFile.close();
}

void DataManager::cargarPreferencias() {
    ifstream verMasTardeFile("ver_mas_tarde.txt");
    string titulo;
    while (getline(verMasTardeFile, titulo)) {
        verMasTarde.push_back(peliculasIndexadas[titulo]);
    }
    verMasTardeFile.close();

    ifstream likesFile("likes.txt");
    while (getline(likesFile, titulo)) {
        likes.push_back(peliculasIndexadas[titulo]);
    }
    likesFile.close();
}

vector<Pelicula*> DataManager::getVerMasTarde() const {
    return verMasTarde;
}

vector<Pelicula*> DataManager::getLikes() const {
    return likes;
}

vector<Pelicula>::iterator DataManager::begin() {
    return peliculas.begin();
}

vector<Pelicula>::iterator DataManager::end() {
    return peliculas.end();
}
