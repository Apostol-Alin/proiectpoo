//
// Created by Utilizator on 22/04/2023.
//

#ifndef OOP_POKEMON_H
#define OOP_POKEMON_H
#include "Power.h"
#include "Carte.h"
#include <vector>

class Pokemon {
    std::string name;
    std::string type;
    std::vector <Power> attack;
    std::string weakness;
    std::string resistance;
    float HP;
    float max_HP;
    float damage_taken_modifier;
    float damage_dealt_modifier;
    int energy;
    int total_energy;
    Carte pokemon_card;
    [[nodiscard]] Power get_power(unsigned int i) const;
public:
    bool can_attack();
    [[nodiscard]] float get_HP() const;
    [[nodiscard]] float get_max_HP() const;
    [[nodiscard]] bool is_alive() const;
    [[nodiscard]] int get_energy() const;
    [[nodiscard]] Carte get_card() const;
    [[nodiscard]]std::string get_name() const;
//    [[maybe_unused]] void check_weakness_resistance(const Power& p);
    void take_damage(float damage_);
    void restore_energy(int value = 20);
    [[maybe_unused]] Power choose_attack();
    [[maybe_unused]] float choose_combo();
    void heal(float healing_value);
    void update_damage_taken_modifier(float modifier);
    void update_damage_dealt_modifier(float modifier);
    void reset_damage_taken_modifier();
    void reset_damage_dealt_modifier();
    Pokemon(std::string  name_, std::string  type_, std::vector <Power>& attack_, std::string  weakness_,std::string  resistance_,float max_HP_,const Carte& pokemon_card_, float damage_taken_modifier_ = 1.f, float damage_dealt_modifier_ = 1.f, int total_energy_ = 0);
    Pokemon(const Pokemon& other);
    Pokemon& operator=(const Pokemon& other);
    friend std::ostream& operator<<(std::ostream& os, const Pokemon& p);
    ~Pokemon();
};


#endif //OOP_POKEMON_H
