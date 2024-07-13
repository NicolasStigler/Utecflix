//
// Created by sergi on 7/13/2024.
//

#ifndef UTECFLIX_ALIKEMOVIES_H
#define UTECFLIX_ALIKEMOVIES_H

#include "MovieDatabase.h"
#include <map>
#include <set>



class AlikeMovies {
public:
    static std::vector<Movie> findSimilarMovies() {
        auto likedMovies = MovieDatabase::getInstance()->getLikedMovies();
        std::map<std::string, int> tagFrequency;
        std::set<std::string> uniqueLikedMovieIDs;

        // Contar la frecuencia de cada tag en las películas que le gustaron al usuario
        for (const auto& movie : likedMovies) {
            uniqueLikedMovieIDs.insert(movie.imdb_id);
            std::vector<std::string> tags = split(movie.tags, ',');
            for (const auto& tag : tags) {
                tagFrequency[tag]++;
            }
        }

        std::vector<Movie> allMovies = MovieDatabase::getInstance()->getMovies();
        std::vector<Movie> similarMovies;

        // Encontrar películas similares basadas en los tags
        for (const auto& movie : allMovies) {
            if (uniqueLikedMovieIDs.find(movie.imdb_id) != uniqueLikedMovieIDs.end()) continue; // Ignorar si ya le gustó al usuario

            std::vector<std::string> movieTags = split(movie.tags, ',');
            int commonTags = 0;
            for (const auto& tag : movieTags) {
                if (tagFrequency.find(tag) != tagFrequency.end()) {
                    commonTags++;
                }
            }

            // Considerar la película similar si tiene al menos la mitad de los tags más frecuentes
            if (commonTags >= tagFrequency.size() / 2) {
                similarMovies.push_back(movie);
            }
        }

        return similarMovies;
    }
};

void showWatchLaterMovies() {
    auto watchLaterMovies = MovieDatabase::getInstance()->getWatchLaterMovies();
    std::cout << "Peliculas para Ver Mas Tarde:" << std::endl;
    for (const auto& movie : watchLaterMovies) {
        std::cout << movie.title << std::endl;
    }
}

void showSimilarToLikedMovies() {
    auto similarMovies = AlikeMovies::findSimilarMovies();
    std::cout << "Peliculas Similares a tus Likes:" << std::endl;
    for (const auto& movie : similarMovies) {
        std::cout << movie.title << std::endl;
    }
}

#endif //UTECFLIX_ALIKEMOVIES_H