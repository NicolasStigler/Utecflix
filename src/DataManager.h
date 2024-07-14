#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <vector>
#include <unordered_map>
#include "Pelicula.h"

class DataManager {
public:
    static DataManager& getInstance() {
        static DataManager instance;
        return instance;
    }

    void cargarDatos(const std::string& rutaArchivo);
    void guardarPreferencias();
    void cargarPreferencias();

    std::vector<Pelicula*> getVerMasTarde() const;
    std::vector<Pelicula*> getLikes() const;

    std::vector<Pelicula>::iterator begin();
    std::vector<Pelicula>::iterator end();

private:
    DataManager() = default;
    std::vector<Pelicula> peliculas;
    std::unordered_map<std::string, Pelicula*> peliculasIndexadas;
    std::vector<Pelicula*> verMasTarde;
    std::vector<Pelicula*> likes;
};

#endif // DATAMANAGER_H
