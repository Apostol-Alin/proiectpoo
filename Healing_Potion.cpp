//
// Created by Utilizator on 27/04/2023.
//

#include "Healing_Potion.h"
#include <memory>
void Healing_Potion::display(std::ostream &os) const {
    os << "Healing Value: " << healing_value << "\n";
    if(this->old_enough()){
        os << "This potion is old";
    }
}
Healing_Potion::Healing_Potion(const std::string& potion_name_, int potion_cost_, int turns_until_old, float healing_value) : Potion(potion_name_,potion_cost_,turns_until_old), healing_value(healing_value){}
void Healing_Potion::apply_effect (Pokemon& poke) const {
    poke.heal(healing_value);
}
void Healing_Potion::turn_old(){
    if(this->old_enough()){
        healing_value /= 2.f;
    }
}
[[nodiscard]] std::shared_ptr<Potion> Healing_Potion::clone() const  { return std::make_shared<Healing_Potion>(*this); }