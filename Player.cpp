//
// Created by Utilizator on 22/04/2023.
//

#include "Player.h"
#include "Healing_Potion.h"
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

//void Player::choose_potion(Pokemon &poke){
//
//}

[[nodiscard]] int Player::get_money() const{ return money;}

[[nodiscard]] int Player::get_score() const { return score;}

void Player::update_money(int value){ money += value; }

void Player::update_score(const Pokemon& poke) {score += Player::bonus_score(poke); }

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
    for(const auto & k : p.pokemoni){
        os << k.get_name() << '\n';
    }
    for(const auto & pot: p.potions){
        os << *pot << "\n";
    }
    return os;
}

Player::~Player() = default;