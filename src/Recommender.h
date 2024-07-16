#ifndef RECOMMENDER_H
#define RECOMMENDER_H

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include "AlgoritmoDeBúsqueda.h"
#include "MovieDatabase.h"

class Recommender {
public:
    std::vector<Movie> recommendMovies(const std::vector<Movie>& likedMovies) {
        std::unordered_map<std::string, int> tagCount;

        for (const auto& movie : likedMovies) {
            std::vector<std::string> tags = splitTags(movie.tags);
            for (const auto& tag : tags) {
                tagCount[tag]++;
            }
        }

        std::vector<Movie> recommendations;
        MovieDatabase* db = MovieDatabase::getInstance();
        for (const auto& movie : db->getMovies()) {
            if (std::find(likedMovies.begin(), likedMovies.end(), movie) != likedMovies.end()) {
                continue; // Skip liked movies
            }

            std::vector<std::string> tags = splitTags(movie.tags);
            bool hasCommonTag = false;
            for (const auto& tag : tags) {
                if (tagCount[tag] > 0) {
                    hasCommonTag = true;
                    break;
                }
            }

            if (hasCommonTag) {
                recommendations.push_back(movie);
            }
        }

        return recommendations;
    }

private:
    std::vector<std::string> splitTags(const std::string& tags) {
        std::vector<std::string> result;
        std::istringstream stream(tags);
        std::string tag;
        while (std::getline(stream, tag, ',')) {
            // Remove leading and trailing spaces
            tag.erase(0, tag.find_first_not_of(" "));
            tag.erase(tag.find_last_not_of(" ") + 1);
            result.push_back(tag);
        }
        return result;
    }
};

#endif // RECOMMENDER_H
