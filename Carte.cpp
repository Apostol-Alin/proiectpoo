//
// Created by Utilizator on 22/04/2023.
//

#include "Carte.h"
#include <random>

std::string Carte::generate_random_rarity(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 1000);
    int k = dist(gen);
    if (k >= 990)
        return "Holographic";
    if (k >= 800)
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