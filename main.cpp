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
int main() {

    Power power_bulbasaur("Seed Rain","Unleash a rain of seeds that deals magic damage to foes","Earth",30.f,35);
    Power power_pikachu("Tunder Bolt","Zap the enemy to deal damage","Lightning",36.f,25);
    Power power_charmander("Flame Thrower","BUUUUUURN!!!!!","Fire",35.f,30);
    std::vector <Power> puteri_pikachu;
    puteri_pikachu.emplace_back(power_pikachu);
    std::vector <Power> puteri_bulb;
    puteri_bulb.emplace_back(power_bulbasaur);
    std::vector <Power> puteri_charm;
    puteri_charm.emplace_back(power_charmander);
    Carte c1,c2,c3;
    try {
        Pokemon pika("Pikachu", "Lightning", puteri_pikachu, "Earth", "-", 50.f, c1, 1.f, 1.f, 100);
        Pokemon bulb("Bulbasaur", "Earth", puteri_bulb, "Fire", "-", 60.f, c2, 1.f, 1.f, 100);
        Pokemon charm("Charmander", "Fire", puteri_charm, "Water", "-", 50.f, c3, 1.f, 1.f, 100);
        std::cout<<power_bulbasaur<<"\n";
        std::cout<<charm<<"\n";
        std::cout<<pika.get_card()<<"\n";
        std::cout<<bulb<<"\n";
        power_bulbasaur = power_charmander;
        std::cout<<power_bulbasaur<<"\n";
        std::cout<<bulb<<"\n";
        std::cout << "\n";
        std::cout << "HP Pikachu inainte de a lua damage: " << pika.get_HP() << "\n";
        pika.take_damage(20.f);
        std::cout << "HP Pikachu dupa ce a luat damage: "<< pika.get_HP() << "\n";
        pika.heal(30.f);
        std::cout << "HP Pikachu dupa heal: "<< pika.get_HP() << "\n";
        std::cout << "Is Pikachu still alive after that?:  " << pika.is_alive() << "\n";
        std::cout << pika.get_energy() << '\n';
        bulb.update_damage_dealt_modifier(2.f);
        bulb.update_damage_taken_modifier(1.5f);
        bulb.reset_damage_dealt_modifier();
        bulb.reset_damage_taken_modifier();
        pika.check_weakness_resistance(power_bulbasaur);
//    //*********************
////    rulati pentru a creea un combo de attackuri pentru pikachu
        std::cout << pika.choose_combo();
        std::cout << ": Damage dealt from combo\n";
        pika.restore_energy();
        std::cout<<power_bulbasaur.get_dmg()<<'\n';

        Healing_Potion Potionheal1{"Lesser Healing Potion", 20 , 3, 30.f};
        pika.take_damage(40.f);
        std::cout << "\n"<< pika.get_HP() << "\n";
        std::cout << Potionheal1;
        for (int i = 0; i < 16; i++) {
            rlutil::setColor(i);
            std::cout << i << " ";
        }
        for (int i = 0; i < 8; i++) {
            rlutil::setBackgroundColor(i);
            std::cout << i;
            rlutil::setBackgroundColor(0);
            std::cout << ' ';
        }
        std::cout << "\n";
        std::vector<Pokemon> v_poke;
        v_poke.emplace_back(pika);
        v_poke.emplace_back(bulb);
        std::string a = "Alin";
        std::vector<std::shared_ptr<Potion>> potions;
        potions.emplace_back(Potionheal1.clone());
        Potionheal1.increase_turn_counter();
        Potionheal1.turn_old();
        Player p1{a,v_poke,potions};
        map m1{p1,1,1,v_poke};
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
        m1.start_game();
        std::cout << curse;
        std::cout << pika.get_HP() << "\n";
        curse.apply_effect(pika);
        std::cout << pika.get_HP();
        p1.add_potion(Potionheal1.clone());
        p1.add_potion(energ.clone());
        p1.add_potion(haz.clone());
        p1.add_potion(curse.clone());
        p1.add_potion(def.clone());
        def.apply_effect(pika);
        std::cout << p1;
        p1.heal_pokemoni();
        std::cout << p1;
        p1.increase_age_to_potions();
    }
    catch(game_error& err){
        std::cout << err.what();
    }
    return 0;
}

