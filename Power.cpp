//
// Created by Utilizator on 22/04/2023.
//

#include "Power.h"

[[nodiscard]] float Power::get_dmg() const{ return damage;}
[[nodiscard]] int Power::get_energy_cost() const{ return energy_cost;}
[[nodiscard]] std::string Power::get_power_type() const{ return power_type;}
[[nodiscard]] std::string Power::get_name() const{ return name;}
Power::Power() = default;
Power::Power(const std::string& name_, const std::string& description_, const std::string& power_type_, float damage_, int energy_cost_){
    this->name = name_;
    this->description = description_;
    this->power_type = power_type_;
    this->damage = damage_;
    this->energy_cost = energy_cost_;
}
Power::Power(const Power& other) = default;
Power& Power::operator=(const Power& other)= default;
std::ostream& operator<<(std::ostream& os, const Power& p){
    os<<"Name of power: "<<p.name<<"\n"<<"Description: "<<p.description<<"\n"<<"Power type: "<<p.power_type<<"\n"<<"Damage: "<<p.damage<<"\n"<<"Energy cost:"<<p.energy_cost<<"\n";
    return os;
}
Power::~Power(){// std::cout<<"Destructor Power\n";
}