//
// Created by Utilizator on 27/04/2023.
//

#include "Potion.h"
#include "exceptii.h"
void Potion::display(std::ostream &) const {}

Potion::Potion(const Potion &other) = default;

Potion& Potion::operator=(const Potion &other) = default;

Potion::Potion(std::string  potion_name_, int potion_cost_, int turns_until_old_) :
potion_name(std::move(potion_name_)), potion_cost(potion_cost_), turns_until_old(turns_until_old_) {
    if(potion_cost_ <= 0)
        throw potion_error("Potion cost needs to be greater that 0...\n");
}

std::ostream &operator<<(std::ostream &os, const Potion &potion_) {
    os << potion_.potion_name << "\n" << "Cost: " << potion_.potion_cost << "\n";
    os << "Turns until potions gets old: " << potion_.turns_until_old << "\n";
    os << "Current age of potion: " << potion_.current_turns << "\n";
    potion_.display(os);
    os << "\n";
    return os;
}
void Potion::turn_old() {}
void Potion::increase_turn_counter() { current_turns++;}
//void Potion::apply_effect(Pokemon& ) const {};
bool Potion::old_enough() const {return current_turns == turns_until_old;}
Potion::~Potion() = default;