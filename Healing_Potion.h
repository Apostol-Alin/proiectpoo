//
// Created by Utilizator on 27/04/2023.
//

#ifndef OOP_HEALING_POTION_H
#define OOP_HEALING_POTION_H
#include "Potion.h"

class Healing_Potion : public Potion{
    float healing_value;
    void display(std::ostream &os) const override;
public:
    Healing_Potion(const std::string& potion_name_, int potion_cost_,int turns_until_old, float healing_value);
    void apply_effect (Pokemon& poke) const override;
    [[nodiscard]] std::shared_ptr<Potion> clone() const override;
    void turn_old() override;
};


#endif //OOP_HEALING_POTION_H
