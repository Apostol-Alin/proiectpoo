//
// Created by Utilizator on 29/04/2023.
//

#include "Curse_Potion.h"
void Curse_Potion::display(std::ostream &os) const {
    rlutil::setColor(12);
    os << "Damage you could receive: " << this->get_damage_to_deal() << "\n";
    rlutil::setColor(5);
    os << "Ammount you could heal: " << this->get_healing_value() << "\n";
    rlutil::setColor(15);
    if(this->old_enough()){
        rlutil::setBackgroundColor(7);
        os << "This potion is old";
        rlutil::setBackgroundColor(0);
    }
}
Curse_Potion::Curse_Potion(const std::string& potion_name_, int potion_cost_, int turns_until_old, float healing_value, float dmg) : Potion(potion_name_,potion_cost_,turns_until_old),
                                                                                                                                        Healing_Potion(potion_name_,potion_cost_,turns_until_old, healing_value),
                                                                                                                                        Hazard_Potion(potion_name_,potion_cost_,turns_until_old,dmg) {}
void Curse_Potion::apply_effect (Pokemon& poke) const {
    if(randomness)
        Healing_Potion::apply_effect(poke);
    else
        Hazard_Potion::apply_effect(poke);
}
void Curse_Potion::turn_old(){
    if(this->old_enough()){ randomness = rand() % 2; }
}
[[nodiscard]] std::shared_ptr<Potion> Curse_Potion::clone() const  { return std::make_shared<Curse_Potion>(*this); }