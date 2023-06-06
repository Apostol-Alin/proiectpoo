#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <rlutil.h>
#include "Power.h"
#include "Pokemon.h"
#include "Carte.h"
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
        Pokemon pika = pokemon_factory::Pikachu();
        Pokemon bulb = pokemon_factory::Bulbasaur();
        Pokemon charm = pokemon_factory::Charmander();
        Healing_Potion Potionheal1{"Lesser Healing Potion", 20 , 3, 30.f};
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
        std::cout << energ;
        Hazard_Potion haz{"Plague",25,4,20};
        std::cout << haz;
        Curse_Potion curse{"Mistery Potion", 10, 6, 70, 15};
        Defence_Potion def{"Shield's up!", 30, 2, 1.2f};
        std::cout << def;
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
        auto &m1 = map::get_map(p3,1,1,pokemon_pool, map_potions);
        m1.start_game();
        std::cout << curse;
        std::cout << pika.get_HP() << "\n";
        curse.apply_effect(pika);
        std::cout << pika.get_HP();
        def.apply_effect(pika);
        std::cout << "\n";
        p1.add_potion(haz.clone());
    }
    catch(game_error& err){
        std::cout << err.what();
    }
    return 0;
}

