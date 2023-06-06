//
// Created by Utilizator on 06/06/2023.
//

#ifndef OOP_COMBO_BUILDER_H
#define OOP_COMBO_BUILDER_H
#include "Pokemon.h"

class combo_builder {
    std::vector<Power> combos;
    float total_damage;
    Pokemon& pokemon;
public:
    explicit combo_builder(Pokemon&);
    combo_builder& addAttack();
    combo_builder& removeAttack();
    float finish_combo();
};


#endif //OOP_COMBO_BUILDER_H
