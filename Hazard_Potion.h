//
// Created by Utilizator on 29/04/2023.
//

#ifndef OOP_HAZARD_POTION_H
#define OOP_HAZARD_POTION_H
#include "Potion.h"

class Hazard_Potion: virtual public Potion{
    float damage_to_deal;
    void display(std::ostream &os) const override;
protected:
    [[nodiscard]] virtual float get_damage_to_deal() const;
public:
    Hazard_Potion(const std::string& potion_name_, int potion_cost_,int turns_until_old, float dmg);
    void apply_effect (Pokemon& poke) const override;
    [[nodiscard]] std::shared_ptr<Potion> clone() const override;
    void turn_old() override;
};


#endif //OOP_HAZARD_POTION_H
