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
    static const int carrying_capacity = 7;
    static int bonus_score(const Pokemon& poke);
public:
    //void choose_potion(Pokemon& poke);
    void heal_pokemoni ();
    void add_potion(const std::shared_ptr<Potion>& new_pot);
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
