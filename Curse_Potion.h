//
// Created by Utilizator on 29/04/2023.
//

#ifndef OOP_CURSE_POTION_H
#define OOP_CURSE_POTION_H
#include "Healing_Potion.h"
#include "Hazard_Potion.h"

class Curse_Potion: public Healing_Potion, public Hazard_Potion {
    int randomness = rand() % 3;
public:
    void display(std::ostream &os) const override;
public:
    Curse_Potion(const std::string& potion_name_, int potion_cost_,int turns_until_old, float healing_value, float dmg);
    void apply_effect (Pokemon& poke) const override;
    [[nodiscard]] std::shared_ptr<Potion> clone() const override;
    void turn_old() override;
};


#endif //OOP_CURSE_POTION_H
