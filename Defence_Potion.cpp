//
// Created by Utilizator on 06/05/2023.
//

#include "Defence_Potion.h"
#include <rlutil.h>
void Defence_Potion::display(std::ostream &os) const {
    rlutil::setColor(1);
    os << "This potion will boost your Pokemon's defence by: " << defence_boost << "\n";
    rlutil::setColor(15);
}

Defence_Potion::Defence_Potion(const std::string &potion_name_, int potion_cost_, int turns_until_old,
                               float defence_boost_) : Potion(potion_name_,potion_cost_,turns_until_old), defence_boost(defence_boost_){}

void Defence_Potion::apply_effect(Pokemon &poke) const {
    poke.update_damage_taken_modifier(defence_boost);
}

void Defence_Potion::turn_old() {
    if(this->old_enough())
        defence_boost /= 1.f;
}

std::shared_ptr<Potion> Defence_Potion::clone() const {return std::make_shared<Defence_Potion>(*this);}