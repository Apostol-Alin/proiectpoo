//
// Created by Utilizator on 06/05/2023.
//

#ifndef OOP_DEFENCE_POTION_H
#define OOP_DEFENCE_POTION_H

#include "Potion.h"

class Defence_Potion: public Potion {
    float defence_boost;
    void display(std::ostream &os) const override;
public:
    Defence_Potion(const std::string& potion_name_, int potion_cost_,int turns_until_old, float defence_boost_);
    void apply_effect (Pokemon& poke) const override;
    [[nodiscard]] std::shared_ptr<Potion> clone() const override;
    void turn_old() override;
};


#endif //OOP_DEFENCE_POTION_H
