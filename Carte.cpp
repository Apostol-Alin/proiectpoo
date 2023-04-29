//
// Created by Utilizator on 22/04/2023.
//

#include "Carte.h"

std::string Carte::generate_random_rarity(){
    int k = rand() % 1000;
    if(k >= 990)
        return "Holographic";
    if(k >= 800)
        return "Golden";
    return "Basic";
}
[[nodiscard]] std::string& Carte::get_rarity()  { return rarity;}
[[nodiscard]] int Carte::get_stage() const { return stage;}
void Carte::increase_stage() { stage++;}
Carte::Carte( int stage_) : rarity(generate_random_rarity()), stage(stage_){}
Carte::Carte(const Carte& other) = default;
Carte& Carte::operator=(const Carte& other)= default;
std::ostream& operator<<(std::ostream& os, const Carte& c){
    os<<c.rarity<<"     "<<"Stage: "<<c.stage<<"\n";
    return os;
}
Carte::~Carte()= default;