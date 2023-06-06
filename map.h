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
    std::vector<std::shared_ptr<Potion>> potions;
    Player player;
    int x_player;
    int y_player;
    void draw();
    static void entry_message();
    void gen();
    void access_shop();
    bool pokemon_encounter();
    void player_turn(Pokemon&, Pokemon&);
    static void enemy_turn(Pokemon&, Pokemon&);
    map(const Player& player_, int x, int y, std::vector<Pokemon> pokemoni_, std::vector<std::shared_ptr<Potion>> potions_);
public:
    static map& get_map(const Player& player_, int x, int y, std::vector<Pokemon> pokemoni_, std::vector<std::shared_ptr<Potion>> potions_);
    void start_game();
    map(const map& other) = delete;
    map& operator=(map other) = delete;
    friend std::ostream& operator<<(std::ostream& os, const map& map);
    ~map();
};


#endif //OOP_MAP_H
