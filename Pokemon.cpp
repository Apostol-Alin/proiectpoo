//
// Created by Utilizator on 22/04/2023.
//

#include "Pokemon.h"

#include <utility>
#include <rlutil.h>
#include "exceptii.h"

[[nodiscard]] Power Pokemon::get_power(unsigned int i) const{
    if(i < 1 or i > attack.size())
        throw invalid_option("Invalid index...\n");
    return attack[i-1];
}
[[nodiscard]] Carte Pokemon::get_card() const{ return pokemon_card;}

[[nodiscard]] float Pokemon::get_HP() const{ return HP;}

[[nodiscard]] float Pokemon::get_max_HP() const { return max_HP;}

[[nodiscard]] bool Pokemon::is_alive() const{ return HP > 0.f;}

[[nodiscard]] int Pokemon::get_energy() const{ return total_energy;}

std::string Pokemon::get_name() const{
    return name;
}
bool Pokemon::can_attack() {
    for(const auto& pow: attack)
        if(pow.get_energy_cost() <= energy)
            return true;
    return false;
}
void Pokemon::check_weakness_resistance(const Power& p){
    if(this->weakness == p.get_power_type())
        update_damage_taken_modifier(0.9f);
    if(this->resistance ==  p.get_power_type())
        update_damage_taken_modifier(1.1f);
}

void Pokemon::take_damage(float damage_){
    HP -= damage_ * damage_taken_modifier;
    if(HP < 0.f){
        HP = 0;
    }
}

void Pokemon::restore_energy(int value_){
    energy += value_;
    if(energy > total_energy)
        energy = total_energy;
}

[[maybe_unused]] Power Pokemon::choose_attack(){
    do {
        try {
            std::cout << "Current energy: " << energy << "\n";
            std::cout << "Please choose an attack:\n";
            unsigned int i = 1;
            for (const auto &a: attack) {
                std::cout << i << ". " << a.get_name() << "\t" << "Energy cost: " << a.get_energy_cost() << "\n";
                i++;
            }
            std::cin >> i;
            const Power temp = get_power(i);
            if (temp.get_energy_cost() <= energy) {
                energy -= temp.get_energy_cost();
                return temp;
            } else
                throw std::logic_error("Not enough energy\n");
        }
        catch(invalid_option &exc){
            std::cout << exc.what() << "\n";
        }
    }while(true);
}

[[maybe_unused]] float Pokemon::choose_combo(){
    std::vector <Power> combos;
    Power chosen_power;
    float total_damage = 0.f;
    unsigned int i;
    do{
//          combo_attack:
//          1st step -> choose an atack and create the vector of attacks
        std::cout << "Current energy:" << energy << "\n";
        std::cout << "Choose an action:\n";
        std::cout << "1. Add attack to combo\n";
        std::cout << "2. Remove attack from combo\n";
        std::cout << "3. Finish combo\n";
        std::cout << "4. Exit combo menu\n";
        std::cin >> i;
        try {
            switch (i) {
                case 1: {
                    chosen_power = choose_attack();
                    total_damage += chosen_power.get_dmg();
                    combos.emplace_back(chosen_power);
                    break;
                }
                case 2: {
                    unsigned int k = 0;
                    std::cout<<"Choose an attack to remove from your combo:\n";
                    for(const auto & a : combos){
                        std::cout<<k+1<<"."<<a.get_name()<<"\n";
                        k++;
                    }
                    std::cin >> k;
                    energy += combos.at(k-1).get_energy_cost();
                    total_damage -= combos.at(k-1).get_dmg();
                    combos.erase(combos.begin()+k-1);
                    break;
                }
                case 3: {
                    if(!combos.empty())
                        return total_damage;
                    else
                        std::cout<<"The combo is empty\n Please choose at least one attack!\n";
                    break;
                }
                case 4:{
                    return 0.f;
                }
                default: {
                    std::cout << "Invalid option\n";
                    break;
                }
            }
        }
        catch(std::out_of_range &exc){
            std::cout<<exc.what();
        }
        catch(std::logic_error &exc){
            std::cout<<exc.what();
        }
//            2nd step -> ask user for action : add attack to combo, remove attack from combo, finish combo
//            3rd step  -> if add attack -> call choose_attack -> go to step 2
//                    -> if remove attack -> display vector of attacks chosen so far -> get index for removal -> go to step 2
//                    -> else return the vector
//            catch error -> repeat from step 2
    }while(true);
}

void Pokemon::heal(float healing_value){
    HP += healing_value;
    if(HP > max_HP)
        HP = max_HP;
}

void Pokemon::update_damage_taken_modifier(float modifier){
    damage_taken_modifier *= modifier;
}

void Pokemon::update_damage_dealt_modifier(float modifier){
    damage_dealt_modifier *= modifier;
}

void Pokemon::reset_damage_taken_modifier(){
    damage_taken_modifier = 1.f;
}

void Pokemon::reset_damage_dealt_modifier(){
    damage_dealt_modifier = 1.f;
}

Pokemon::Pokemon(std::string  name_, std::string  type_, std::vector <Power>& attack_, std::string  weakness_,std::string  resistance_, float max_HP_,const Carte& pokemon_card_, float damage_taken_modifier_, float damage_dealt_modifier_ , int total_energy_ ):
        name(std::move(name_)),type(std::move(type_)), attack(attack_), weakness(std::move(weakness_)), resistance(std::move(resistance_)), HP(max_HP_),
        max_HP(max_HP_),damage_taken_modifier(damage_taken_modifier_), damage_dealt_modifier(damage_dealt_modifier_), energy(total_energy_), total_energy(total_energy_), pokemon_card(pokemon_card_){
        if(max_HP_ <= 0)
            throw pokemon_error("Pokemon needs to have HP > 0 ...\n");
        if(attack_.empty())
            throw pokemon_error("Pokemon needs to have at least 1 attack..\n");
}

Pokemon::Pokemon(const Pokemon& other): name(other.name), type(other.type), attack(other.attack), weakness(other.weakness), resistance(other.resistance), HP(other.HP), max_HP(other.max_HP), damage_taken_modifier(other.damage_taken_modifier), damage_dealt_modifier(other.damage_dealt_modifier), energy(other.energy), total_energy(other.total_energy),
                                        pokemon_card(other.pokemon_card){}
Pokemon& Pokemon::operator=(const Pokemon& other){
    name = other.name;
    type = other.type;
    attack = other.attack;
    weakness = other.weakness;
    resistance = other.resistance;
    HP = other.HP;
    max_HP = other.max_HP;
    damage_dealt_modifier = other.damage_dealt_modifier;
    damage_taken_modifier = other.damage_taken_modifier;
    energy = other.energy;
    total_energy = other.total_energy;
    pokemon_card = other.pokemon_card;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Pokemon& p){
    os<<"Name: "<<p.name<<"\n"<<"Pokemon type: "<<p.type<<"\n";
    rlutil::setColor(12);
    os<<"HP: "<<p.HP;
    rlutil::setColor(14);
    os<<"\tEnergy: "<<p.energy<<"\n";
    rlutil::setColor(15);
    os << p.pokemon_card;
    os<<"Attacks:\n";
    for(const auto & k: p.attack){
        os<<"\t"<<k<<"\n";
    }
    os<<"Weakness: "<<p.weakness<<"\n"<<"Resistance: "<<p.resistance<<"\n";
    return os;
}

Pokemon::~Pokemon(){
    //destructor pokemon;
};