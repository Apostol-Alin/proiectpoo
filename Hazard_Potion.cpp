//
// Created by Utilizator on 29/04/2023.
//

#include "Hazard_Potion.h"
#include <memory>

void Hazard_Potion::display(std::ostream &os) const {
    rlutil::setColor(5);
    os << "Damage to deal: " << damage_to_deal << "\n";
    rlutil::setColor(15);
    if(this->old_enough()){
        rlutil::setBackgroundColor(7);
        os << "This potion is old";
        rlutil::setBackgroundColor(0);
    }
}
float Hazard_Potion::get_damage_to_deal() const {return damage_to_deal; }

Hazard_Potion::Hazard_Potion(const std::string& potion_name_, int potion_cost_, int turns_until_old, float dmg) :
Potion(potion_name_,potion_cost_,turns_until_old), damage_to_deal(dmg){}

void Hazard_Potion::apply_effect (Pokemon& poke) const {
    poke.take_damage(damage_to_deal);
}

void Hazard_Potion::turn_old(){
    if(this->old_enough()){ damage_to_deal = 0.f; }
}

[[nodiscard]] std::shared_ptr<Potion> Hazard_Potion::clone() const  { return std::make_shared<Hazard_Potion>(*this); }
