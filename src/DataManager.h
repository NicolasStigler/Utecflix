#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Pelicula.h"

using namespace std;

class DataManager {
public:
    static DataManager& getInstance() {
        static DataManager instance;
        return instance;
    }

    void cargarDatos(const string& rutaArchivo);
    void guardarPreferencias();
    void cargarPreferencias();

    vector<Pelicula*> getVerMasTarde() const;
    vector<Pelicula*> getLikes() const;

    vector<Pelicula>::iterator begin();
    vector<Pelicula>::iterator end();

private:
    DataManager() = default;
    vector<Pelicula> peliculas;
    unordered_map<string, Pelicula*> peliculasIndexadas;
    vector<Pelicula*> verMasTarde;
    vector<Pelicula*> likes;
};

#endif // DATAMANAGER_H
