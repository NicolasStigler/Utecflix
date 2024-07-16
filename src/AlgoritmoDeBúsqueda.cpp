#include "AlgoritmoDeBúsqueda.h"

// Definiciones de funciones

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

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

bool containsCaseInsensitive(const std::string& text, const std::string& keyword) {
    auto it = std::search(
        text.begin(), text.end(),
        keyword.begin(), keyword.end(),
        [](char ch1, char ch2) { return std::tolower(ch1) == std::tolower(ch2); }
        );
    return it != text.end();
}

std::vector<Movie> searchMovies(const std::vector<Movie>& movies, const std::string& keyword) {
    std::vector<Movie> results;
    for (const auto& movie : movies) {
        if (containsCaseInsensitive(movie.title, keyword) ||
            containsCaseInsensitive(movie.plot_synopsis, keyword) ||
            containsCaseInsensitive(movie.tags, keyword)) {
            results.push_back(movie);
        }
    }
    return results;
}
