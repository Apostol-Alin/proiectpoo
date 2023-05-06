//
// Created by Utilizator on 22/04/2023.
//

#include "Player.h"
#include "Healing_Potion.h"

const int Player::carrying_capacity = 7;

int Player::bonus_score(const Pokemon& poke){
    int bonus = 0;
    std::string tmp = poke.get_card().get_rarity();
    if(tmp == "Basic")
        bonus += 50;
    else
        if (tmp == "Golden")
            bonus += 150;
        else
            bonus += 400;
    return bonus;
}

void Player::add_potion(const std::shared_ptr<Potion>& new_pot){
    if(potions.size() < carrying_capacity)
        potions.emplace_back(new_pot);
}

void Player::heal_pokemoni() {
    for(auto &pokemon : pokemoni){
        unsigned int k;
        for(k = 0; k < potions.size(); k++){
            if (auto current = std::dynamic_pointer_cast<Healing_Potion>(potions[k])){
                if(pokemon.get_HP() != pokemon.get_max_HP()){
                    current->apply_effect(pokemon);
                    unsigned int i = k;
                    while(i < potions.size() - 1) {
                        potions[i] = potions[i + 1];
                        i++;
                    }
                    potions.resize(potions.size()-1);
                    k--;
                }
            }
        }
    }
}
void Player::increase_age_to_potions() {
    for(auto& pot : potions){
        pot->increase_turn_counter();
        pot->turn_old();
    }
}
//void Player::choose_potion(Pokemon &poke){
//
//}

[[nodiscard]] int Player::get_money() const{ return money;}

[[nodiscard]] int Player::get_score() const { return score;}

void Player::update_money(int value){ money += value; }

void Player::update_score() {
    score = 0;
    for(const auto& pokemon: pokemoni)
        score += bonus_score(pokemon);
}

Player::Player(std::string& player_name_, std::vector <Pokemon>& pokemoni_,std::vector<std::shared_ptr<Potion>> potions_, int money_ , int score_) : player_name(player_name_),pokemoni(pokemoni_),potions(std::move(potions_)), money(money_), score(score_){}
Player::Player(const Player& other) : player_name(other.player_name), pokemoni(other.pokemoni), money(other.money), score(other.score){
    for(const auto& pot: other.potions)
        this->potions.emplace_back(pot->clone());
}

Player& Player::operator=(Player other){
    swap(*this, other);
    return *this;
}
void swap(Player& p1, Player& p2){
    std::swap(p1.player_name,p2.player_name);
    std::swap(p1.money,p2.money);
    std::swap(p1.score,p2.score);
    std::swap(p1.potions,p2.potions);
    std::swap(p1.pokemoni,p2.pokemoni);
}
std::ostream& operator<<(std::ostream& os, const Player& p){
    os << "Player: " << p.player_name << "\n";
    os << "Money: "<< p.money << " Score: " << p.score << "\n";
    os << "\nPokemons:\n";
    for(const auto & k : p.pokemoni){
        os << k.get_name() << " HP:" << k.get_HP() << "\n";
    }
    os << "\nPotions:\n";
    for(const auto & pot: p.potions){
        os << *pot << "\n";
    }
    return os;
}

Player::~Player() = default;