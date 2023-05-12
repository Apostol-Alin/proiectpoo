//
// Created by Utilizator on 22/04/2023.
//

#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include "Pokemon.h"
#include "Potion.h"
class Player {
    std::string player_name;
    std::vector <Pokemon> pokemoni;
    std::vector <std::shared_ptr<Potion>> potions;
    int money;
    int score;
    static const int carrying_capacity;
    static int bonus_score(const Pokemon& poke);
public:
    void increase_age_to_potions();
    void choose_potion(Pokemon& , Pokemon&);
    unsigned int get_inventory_size();
    Pokemon& choose_pokemon(unsigned int i);
    unsigned int get_pokemoni_size();
    void heal_pokemoni();
    void add_potion(const std::shared_ptr<Potion>& new_pot);
    void add_pokemon(Pokemon poke);
    void display_pokemoni() const;
    void display_potions() const;
    [[nodiscard]] int get_money() const;
    void update_money(int value);
    [[nodiscard]] int get_score() const;
    void update_score();
    explicit Player(std::string& player_name, std::vector <Pokemon>& pokemoni_,std::vector<std::shared_ptr<Potion>> potions_, int money_ = 200, int score = 0);
    Player(const Player& other);
    Player& operator=(Player other);
    friend void swap(Player&, Player&);
    friend std::ostream& operator<<(std::ostream& os, const Player& p);
    ~Player();
};


#endif //OOP_PLAYER_H
