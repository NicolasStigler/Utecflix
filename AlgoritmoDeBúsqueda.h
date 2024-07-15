#ifndef UTECFLIX_ALGORITMODEBÚSQUEDA_H
#define UTECFLIX_ALGORITMODEBÚSQUEDA_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>
#include <algorithm>

struct Movie {
    std::string imdb_id;
    std::string title;
    std::string plot_synopsis;
    std::string tags;
    std::string split;
    std::string synopsis_source;
    bool liked;
    bool watchLater;

    Movie() : liked(false), watchLater(false) {}

    Movie(const std::string& id, const std::string& t, const std::string& ps, const std::string& tg, const std::string& sp, const std::string& ss)
        : imdb_id(id), title(t), plot_synopsis(ps), tags(tg), split(sp), synopsis_source(ss), liked(false), watchLater(false) {}
};

// Declaracion de funciones

std::string trim(const std::string& str);
std::vector<std::string> splitCSVLine(const std::string& line);
Movie parseLine(const std::string& line);
std::vector<Movie> readCSV(const std::string& filename);
bool containsCaseInsensitive(const std::string& text, const std::string& keyword);
std::vector<Movie> searchMovies(const std::vector<Movie>& movies, const std::string& keyword);

#endif //UTECFLIX_ALGORITMODEBÚSQUEDA_H
