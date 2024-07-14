#ifndef PELICULA_H
#define PELICULA_H

#include <string>
#include <vector>

using namespace std;

class Pelicula {
public:
    Pelicula() = default;
    Pelicula(const string& imdb_id, const string& titulo, const string& sinopsis, const vector<string>& tags)
            : imdb_id(imdb_id), titulo(titulo), sinopsis(sinopsis), tags(tags) {}

    string getImdbId() const { return imdb_id; }
    string getTitulo() const { return titulo; }
    string getSinopsis() const { return sinopsis; }
    vector<string> getTags() const { return tags; }

private:
    string imdb_id;
    string titulo;
    string sinopsis;
    vector<string> tags;
};

#endif // PELICULA_H
