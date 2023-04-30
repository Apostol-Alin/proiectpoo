//
// Created by Utilizator on 29/04/2023.
//

#include "Energy_Potion.h"
#include <memory>
void Energy_Potion::display(std::ostream &os) const {
    rlutil::setColor(14);
    os << "Energy Recover Value: " << recover_value << "\n";
    rlutil::setColor(15);
    if(this->old_enough()){
        rlutil::setBackgroundColor(7);
        os << "This potion is old";
        rlutil::setBackgroundColor(0);
    }
}
Energy_Potion::Energy_Potion(const std::string& potion_name_, int potion_cost_, int turns_until_old, int recover_value_) : Potion(potion_name_,potion_cost_,turns_until_old), recover_value(recover_value_){}
void Energy_Potion::apply_effect (Pokemon& poke) const {
    poke.restore_energy(recover_value);
}
void Energy_Potion::turn_old(){
    if(this->old_enough()){
        recover_value = -recover_value;
    }
}
[[nodiscard]] std::shared_ptr<Potion> Energy_Potion::clone() const  { return std::make_shared<Energy_Potion>(*this); }