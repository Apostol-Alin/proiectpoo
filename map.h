//
// Created by Utilizator on 30/04/2023.
//

#ifndef OOP_MAP_H
#define OOP_MAP_H
#include "Player.h"
#include "Pokemon.h"

class map {
    static const int map_size = 10;
    std::vector<std::vector<std::string>> layout;
    std::vector<Pokemon> pokemoni;
    Player player;
    int x_player;
    int y_player;
    void draw();
    static void entry_message();
    void gen();
//    void pokemon_encounter(){
//
//    }d
public:
    void start_game();
    map(const Player& player_, int x, int y, std::vector<Pokemon> pokemoni_);
};


#endif //OOP_MAP_H
