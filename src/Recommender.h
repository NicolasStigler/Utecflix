#ifndef RECOMMENDER_H
#define RECOMMENDER_H

#include <vector>
#include <unordered_map>
#include <algorithm>
#include "Pelicula.h"
#include "DataManager.h"

using namespace std;

class Recommender {
public:
    vector<Pelicula*> recomendarPeliculas(const vector<Pelicula*>& likes) {
        unordered_map<string, int> tagCount;
        for (const auto& pelicula : likes) {
            for (const auto& tag : pelicula->getTags()) {
                tagCount[tag]++;
            }
        }

        vector<Pelicula*> recomendaciones;
        DataManager& dm = DataManager::getInstance();
        for (auto it = dm.begin(); it != dm.end(); ++it) {
            bool found = false;
            for (const auto& tag : it->getTags()) {
                if (tagCount[tag] > 0) {
                    found = any_of(likes.begin(), likes.end(), [&](const Pelicula* p) { return p->getImdbId() == it->getImdbId(); });
                    if (!found) {
                        recomendaciones.push_back(&*it);
                        break;
                    }
                }
            }
        }

        return recomendaciones;
    }
};

#endif // RECOMMENDER_H
