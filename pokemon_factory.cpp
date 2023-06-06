//
// Created by Utilizator on 06/06/2023.
//

#include "pokemon_factory.h"

std::vector <Power> pokemon_factory::puteri_pikachu = {Power{"Tunder Bolt","Zap the enemy to deal damage","Lightning",36.f,25}};
std::vector <Power> pokemon_factory::puteri_bulbasaur = {Power{"Seed Rain","Unleash a rain of seeds that deals magic damage to foes","Earth",30.f,35}};
std::vector <Power> pokemon_factory::puteri_charmander = {Power{"Flame Thrower","BUUUUUURN!!!!!","Fire",35.f,30}};
Pokemon pokemon_factory::Pikachu(){
    return Pokemon{"Pikachu", "Lightning", puteri_pikachu, "Earth", "-", 50.f, Carte{}, 1.f, 1.f, 100};
}
Pokemon pokemon_factory::Bulbasaur(){
    return Pokemon{"Bulbasaur", "Earth", puteri_bulbasaur, "Fire", "-", 60.f, Carte{}, 1.f, 1.f, 100};
}
Pokemon pokemon_factory::Charmander(){
    return Pokemon{"Charmander", "Fire", puteri_charmander, "Water", "-", 50.f, Carte{}, 1.f, 1.f, 100};
}