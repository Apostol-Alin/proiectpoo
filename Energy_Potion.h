//
// Created by Utilizator on 29/04/2023.
//

#ifndef OOP_ENERGY_POTION_H
#define OOP_ENERGY_POTION_H
#include "Potion.h"

class Energy_Potion: public Potion{
    int recover_value;
    void display(std::ostream &os) const override;
public:
    Energy_Potion(const std::string& potion_name_, int potion_cost_,int turns_until_old, int recover_value);
    void apply_effect (Pokemon& poke) const override;
    [[nodiscard]] std::shared_ptr<Potion> clone() const override;
    void turn_old() override;
};


#endif //OOP_ENERGY_POTION_H
