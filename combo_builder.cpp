//
// Created by Utilizator on 06/06/2023.
//

#include "combo_builder.h"

combo_builder::combo_builder(Pokemon& poke) : total_damage(0.f), pokemon(poke){}

combo_builder& combo_builder::addAttack(){
    if (pokemon.can_attack()) {
        Power chosen_power = pokemon.choose_attack();
        total_damage += chosen_power.get_dmg();
        combos.emplace_back(chosen_power);
    }
    else {
        std::cout << "Not enough energy\n";
    }
    return *this;
}

combo_builder& combo_builder::removeAttack(){
    unsigned int k = 0;
    std::cout << "Choose an attack to remove from your combo:\n";
    for (const auto& a : combos) {
        std::cout << k + 1 << "." << a.get_name() << "\n";
        k++;
    }
    std::cin >> k;
    pokemon.reduce_energy(combos.at(k - 1).get_energy_cost());
    total_damage -= combos.at(k - 1).get_dmg();
    combos.erase(combos.begin() + k - 1);
    return *this;
}

float combo_builder::finish_combo(){
    if (!combos.empty())
        return total_damage;
    else {
        std::cout << "The combo is empty\n Please choose at least one attack!\n";
        return 0.f;
    }
}