#include <iostream>
#include <string>
#include <utility>
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
void entry_message(){
    rlutil::setColor(14);
    std::cout << "Welcome to:\n";
    rlutil::msleep(2000);
    rlutil::setColor(11);
    std::cout <<"              _                              \n"
                "  _ __   ___ | | _____ _ __ ___   ___  _ __  \n"
                " | '_ \\ / _ \\| |/ / _ \\ '_ ` _ \\ / _ \\| '_ \\ \n"
                " | |_) | (_) |   <  __/ | | | | | (_) | | | |\n"
                " | .__/ \\___/|_|\\_\\___|_| |_| |_|\\___/|_| |_|\n"
                " |_|                                         ";
    std::cout << "\n";
    rlutil::msleep(2000);
}

class map{
    static const int map_size = 10;
    std::vector<std::vector<std::string>> layout;
    std::vector<Pokemon> pokemoni;
    Player player;
    int x_player;
    int y_player;
    void gen() {
        layout.resize(map_size);
        for(auto& v: layout)
            v.resize(map_size);
        unsigned int i, j;
        for (j = 0; j < map_size; j++) {
            for (i = 0; i < map_size; i++) {
                if (i == 0 or i == map_size - 1 or j == 0 or j == map_size - 1)
                    layout[i][j] = "%";
                else{
                    if(rand() % 6 == 0 and i != 1 and j != 1)
                        layout[i][j] = "P";
                    else
                        layout[i][j] = ".";
                }
            }
        }
    }
//    void pokemon_encounter(){
//
//    }d
public:

    void draw(){
        rlutil::cls();
        //rlutil::locate(1, map_size + 1);
        rlutil::setColor(2);
        std::cout << "Score: " << player.get_score() << "\n";
        rlutil::setColor(14);
        std::cout << "Money: " << player.get_money() << "\n";
        rlutil::setColor(15);
        //rlutil::locate(1, 1);
        int i, j;
        for (j = 0; j < map_size; j++) {
            for (i = 0; i < map_size; i++) {
                if(i == x_player and j == y_player)
                    {rlutil::setColor(11); std::cout << " @ "; rlutil::setColor(15);}
                else if (layout[i][j] == ".") std::cout << " . ";
                else if (layout[i][j] == "P") {rlutil::setColor(12); std::cout << " P "; rlutil::setColor(15);}
                else if (layout[i][j] == "%"){rlutil::setColor(2); std::cout << " % "; rlutil::setColor(15);}
                else {rlutil::setColor(12); rlutil::setBackgroundColor(7); std::cout << " D "; rlutil::setBackgroundColor(0); rlutil::setColor(15);}
            }
            std::cout << "\n";
        }
    }
    void start_game(){
        gen();
        rlutil::setColor(2);
        std::cout << "Use WSAD keys to move and 0 to exit the game\n";
        rlutil::setColor(6);
        rlutil::anykey("Hit any key to start.\n");
        draw();
        while (true) {
            // Input
            if (kbhit()) {
                char k = rlutil::getkey();
                int oldx = x_player, oldy = y_player;
                if (k == 'a') { x_player--; }
                else if (k == 'd') { x_player++; }
                else if (k == 'w') { y_player--; }
                else if (k == 's') { y_player++; }
                else if (k == '0') break;
                // Collisions
                if (layout[x_player][y_player] == "%") { x_player = oldx; y_player = oldy; }
                if (layout[x_player][y_player] == "P") {
                    //pokemon_encounter();
                    layout[x_player][y_player] = "D";
                }
                // Drawing
                draw();
            }
        }
    }
    map(const Player& player_, int x, int y, std::vector<Pokemon> pokemoni_) : pokemoni(std::move(pokemoni_)), player(player_), x_player(x), y_player(y) {}
};

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
    Pokemon pika("Pikachu","Lightning",puteri_pikachu,"Earth","-",50.f,c1,1.f,1.f,100);
    Pokemon bulb("Bulbasaur","Earth",puteri_bulb,"Fire","-",60.f,c2,1.f,1.f,100);
    Pokemon charm("Charmander","Fire",puteri_charm,"Water","-",50.f,c3,1.f,1.f,100);
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
    Potion *p = &Potionheal1;
    std::cout << *p;
    pika.take_damage(40.f);
    p->apply_effect(pika);
    std::cout << "\n"<< pika.get_HP() << "\n";
    std::cout << Potionheal1;
    rlutil::hidecursor();
    entry_message();
    rlutil::setColor(14);
    std::cout << "Arcade Fighting simulator\n";
    rlutil::msleep(2000);
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
    p1.update_score(v_poke[0]);
    std::cout << p1;
    std::cout << p2;
    std::cout << pika.get_card().get_stage() << "\n";
    pika.get_card().increase_stage();
    m1.start_game();
    return 0;
}

