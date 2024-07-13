//
// Created by sergi on 7/12/2024.
//

#ifndef UTECFLIX_SEARCHINGALGORITHM_H
#define UTECFLIX_SEARCHINGALGORITHM_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
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

// Función auxiliar para dividir una cadena por un delimitador
std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Funcion para quitar espacios antes o despues
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

// Funcion para dividir el CSV
std::vector<std::string> splitCSVLine(const std::string& line) {
    std::vector<std::string> result;
    std::stringstream ss(line);
    std::string field;
    bool in_quotes = false;
    char c;
    std::string current_field;

    while (ss.get(c)) {
        if (c == '"' && (current_field.empty() || current_field.back() != '\\')) {
            in_quotes = !in_quotes;
        } else if (c == ',' && !in_quotes) {
            result.push_back(trim(current_field));
            current_field.clear();
        } else {
            current_field += c;
        }
    }
    result.push_back(trim(current_field));

    return result;
}

// Funcion para parsear una observacion del CSV
Movie parseLine(const std::string& line) {
    std::vector<std::string> fields = splitCSVLine(line);
    Movie movie;

    if (fields.size() >= 6) {
        movie.imdb_id = fields[0];
        movie.title = fields[1];
        movie.plot_synopsis = fields[2];
        movie.tags = fields[3];
        movie.split = fields[4];
        movie.synopsis_source = fields[5];
        movie.liked = false;
        movie.watchLater = false;
    }

    return movie;
}

// Funcion para leer el CSV y guardar la data en un vector con la estructura Movie
std::vector<Movie> readCSV(const std::string& filename) {
    std::vector<Movie> movies;
    std::ifstream file(filename);
    std::string line;
    std::string combined_line;
    std::regex imdb_id_pattern(R"(^tt\d{7})");

    // Saltarse el encabezado
    std::getline(file, line);

    while (std::getline(file, line)) {
        if (std::regex_search(line, imdb_id_pattern)) {
            if (!combined_line.empty()) {
                movies.push_back(parseLine(combined_line));
                combined_line.clear();
            }
        }

        // Acumular lineas de una misma observacion en combined_line
        if (!combined_line.empty()) {
            combined_line += "\n";
        }
        combined_line += line;
    }

    if (!combined_line.empty()) {
        movies.push_back(parseLine(combined_line));
    }

    file.close();
    return movies;
}

// Función de búsqueda considerando tags enumerados por comas
bool containsTag(const std::string& tags, const std::string& keyword) {
    std::vector<std::string> tagList = split(tags, ',');
    for (auto& tag : tagList) {
        std::string tag_lower = tag;
        std::string keyword_lower = keyword;
        std::transform(tag_lower.begin(), tag_lower.end(), tag_lower.begin(), ::tolower);
        std::transform(keyword_lower.begin(), keyword_lower.end(), keyword_lower.begin(), ::tolower);
        // Trim leading and trailing spaces from each tag before comparison
        tag_lower.erase(0, tag_lower.find_first_not_of(" \n\r\t"));
        tag_lower.erase(tag_lower.find_last_not_of(" \n\r\t") + 1);
        if (tag_lower == keyword_lower) {
            return true;
        }
    }
    return false;
}


// Funcion para la busqueda
bool containsCaseInsensitive(const std::string& text, const std::string& keyword) {
    std::string text_lower = text;
    std::string keyword_lower = keyword;
    std::transform(text_lower.begin(), text_lower.end(), text_lower.begin(), ::tolower);
    std::transform(keyword_lower.begin(), keyword_lower.end(), keyword_lower.begin(), ::tolower);
    return text_lower.find(keyword_lower) != std::string::npos;
}

// Funcion para buscar peliculas en las variables title, plot synopsis y tags
std::vector<Movie> searchMovies(const std::vector<Movie>& movies, const std::string& keyword) {
    std::vector<std::string> keywordParts = split(keyword, ' ');
    std::vector<Movie> results;

    for (const auto& movie : movies) {
        bool found = false;
        for (const auto& part : keywordParts) {
            if (containsCaseInsensitive(movie.title, part) ||
                containsCaseInsensitive(movie.plot_synopsis, part) ||
                containsTag(movie.tags, part)) {
                found = true;
                break; // Si se encuentra alguna coincidencia, detener la búsqueda para esta película
            }
        }
        if (found) {
            results.push_back(movie);
        }
    }
    return results;
}


#endif //UTECFLIX_SEARCHINGALGORITHM_H
