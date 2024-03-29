#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Power.h"
#include "Pokemon.h"
#include "Player.h"
#include "Potion.h"
#include "Healing_Potion.h"
#include <chrono>
#include "Energy_Potion.h"
#include "Hazard_Potion.h"
#include "Curse_Potion.h"
#include "map.h"
#include "exceptii.h"
#include "Defence_Potion.h"
#include "pokemon_factory.h"

int main() {
    try {
        Power slap{"Slap","just a slap","Physical",5.f,5};
        std::cout << slap.get_power_type();
        auto &factory = pokemon_factory::get_instance();
        Pokemon pika = factory.Pikachu();
        Pokemon bulb = factory.Bulbasaur();
        Pokemon charm = factory.Charmander();
        Healing_Potion Potionheal1{"Lesser Healing Potion", 20 , 3, 30.f};
        pika.update_damage_dealt_modifier(1.1f);
        pika.update_damage_taken_modifier(1.1f);
        pika.reset_damage_dealt_modifier();
        pika.reset_damage_taken_modifier();
        std::vector<Pokemon> v_poke;
        v_poke.emplace_back(pika);
        v_poke.emplace_back(bulb);
        std::string a = "Alin";
        std::vector<std::shared_ptr<Potion>> potions;
        potions.emplace_back(Potionheal1.clone());
        Potionheal1.increase_turn_counter();
        Potionheal1.turn_old();
        Player p1{a,v_poke,potions};
        Player p2{p1};
        p2.add_potion(Potionheal1.clone());
        p1.update_money(10);
        p1.update_score();
        p2.update_score();
        std::cout << p1;
        std::cout << p2;
        std::cout << pika.get_card().get_stage() << "\n";
        pika.get_card().increase_stage();
        Energy_Potion energ{"RedBull",20,5,50};
        Hazard_Potion haz{"Plague",25,4,20};
        Curse_Potion curse{"Mistery Potion", 10, 6, 70, 15};
        Defence_Potion def{"Shield's up!", 30, 2, 1.2f};
        std::vector<std::shared_ptr<Potion>> map_potions;
        map_potions.emplace_back(Potionheal1.clone());
        map_potions.emplace_back(energ.clone());
        map_potions.emplace_back(haz.clone());
        map_potions.emplace_back(curse.clone());
        map_potions.emplace_back(def.clone());
        std::vector<Pokemon> vect_pokemoni;
        std::vector<std::shared_ptr<Potion>> vect_potiuni;
        Player p3{a,vect_pokemoni,vect_potiuni};
        pika.heal(100.f);
        p3.add_pokemon(pika);
        p3.heal_pokemoni();
        std::vector<Pokemon> pokemon_pool;
        pokemon_pool.emplace_back(pika);
        pokemon_pool.emplace_back(bulb);
        pokemon_pool.emplace_back(charm);
        auto &m1 = map::get_instance(p3,1,1,pokemon_pool, map_potions);
        m1.start_game();
    }
    catch(game_error& err){
        std::cout << err.what();
    }
    return 0;
}

