//
// Created by Utilizator on 06/06/2023.
//

#ifndef OOP_POKEMON_FACTORY_H
#define OOP_POKEMON_FACTORY_H
#include "Pokemon.h"
#include "singleton.h"
class pokemon_factory : public singleton<pokemon_factory>{
    static std::vector<Power> puteri_pikachu;
    static std::vector<Power> puteri_bulbasaur;
    static std::vector<Power> puteri_charmander;
public:
    static Pokemon Pikachu();
    static Pokemon Bulbasaur();
    static Pokemon Charmander();
};


#endif //OOP_POKEMON_FACTORY_H
