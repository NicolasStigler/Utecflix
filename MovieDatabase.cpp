#include "MovieDatabase.h"

// Inicializar la instancia estática
MovieDatabase* MovieDatabase::instance = nullptr;

void MovieDatabase::loadMovies(const std::string& filename) {
    movies = readCSV(filename);
}

std::vector<Movie> MovieDatabase::getMovies() {
    return movies;
}

std::vector<Movie> MovieDatabase::search(const std::string& keyword) {
    return searchMovies(movies, keyword);
}

void MovieDatabase::markAsLiked(const std::string& imdb_id) {
    for (auto& movie : movies) {
        if (movie.imdb_id == imdb_id) {
            movie.liked = true;
            likedMovies.push_back(movie);
            return;
        }
    }
}

void MovieDatabase::markAsWatchLater(const std::string& imdb_id) {
    for (auto& movie : movies) {
        if (movie.imdb_id == imdb_id) {
            movie.watchLater = true;
            watchLaterMovies.push_back(movie);
            return;
        }
    }
}

std::vector<Movie> MovieDatabase::getLikedMovies() {
    return getMoviesFromFile("like.txt");
}

std::vector<Movie> MovieDatabase::getWatchLaterMovies() {
    return getMoviesFromFile("watchLater.txt");
}

std::vector<Movie> MovieDatabase::getMoviesFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << filename << std::endl;
        return {};
    }

    std::vector<Movie> movies;
    std::string imdb_id;
    while (std::getline(file, imdb_id)) {
        auto movie = getMovieById(imdb_id);
        if (movie) {
            movies.push_back(*movie);
        }
    }

    file.close();
    return movies;
}

std::optional<Movie> MovieDatabase::getMovieById(const std::string& imdb_id) {
    auto it = std::find_if(movies.begin(), movies.end(), [&imdb_id](const Movie& movie) {
        return movie.imdb_id == imdb_id;
    });
    if (it != movies.end()) {
        return *it;
    }
    return std::nullopt;
}

