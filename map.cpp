//
// Created by Utilizator on 30/04/2023.
//

#include "map.h"

void map::draw(){
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

void map::entry_message(){
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
    rlutil::hidecursor();
    rlutil::setColor(14);
    std::cout << "Arcade Fighting simulator\n";
    rlutil::msleep(2000);
}

void map::gen() {
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
void map::access_shop(){
    rlutil::setColor(13);
    std::cout << "Welcome to the shop!\n";
    std::cout << "Please choose a potion to buy or press 0 if you wish to exit\n";
    unsigned int i = 1;
    for(const auto & pot: potions){
        std::cout << i << "." << pot->get_name() << " cost: " << pot->get_cost() << " turns until old: " << pot->get_turns_until_old() << "\n";
        i++;
    }
    while(true){
        std::cin >> i;
        if(i >= 1 and i <= potions.size()) {
            int potion_cost = potions[i-1]->get_cost();
            if(potion_cost > player.get_money()){
                std::cout << "You don't have enough money!\n";
            }
            else{
                player.update_money(-potion_cost);
                player.add_potion(potions[i-1]);
                break;
            }
        }
        else if(i == 0) { break;}
        else std::cout << "Invalid option!\n";
    }
}
//    void pokemon_encounter(){
//
//    }d

void map::start_game(){
    gen();
    entry_message();
    rlutil::setColor(2);
    std::cout << "Use WSAD keys to move and 0 to exit the game\n";
    std::cout << "Press 1 to access the shop\n";
    std::cout << "Press 2 to see your potion inventory\n";
    std::cout << "Press 3 to see your pokemon inventory\n";
    std::cout << "Note: every move you make on the board ages your current potions by 1\n";
    rlutil::setColor(6);
    rlutil::anykey("Hit any key to start.\n");
    draw();
    while (true) {
        // Input
        if (kbhit()) {
            char k = rlutil::getkey();
            int oldx = x_player, oldy = y_player;
            if (k == 'a') { x_player--; player.increase_age_to_potions();}
            else if (k == 'd') { x_player++; player.increase_age_to_potions();}
            else if (k == 'w') { y_player--; player.increase_age_to_potions();}
            else if (k == 's') { y_player++; player.increase_age_to_potions();}
            else if (k == '1') { access_shop();}
            else if (k == '2') { player.display_potions(); rlutil::anykey("Hit any key to continue\n");}
            else if (k == '3') { player.display_pokemoni(); rlutil::anykey("Hit any key to continue\n");}
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

map::map(const Player& player_, int x, int y, std::vector<Pokemon> pokemoni_, std::vector<std::shared_ptr<Potion>> potions_) :
pokemoni(std::move(pokemoni_)), potions(std::move(potions_)), player(player_), x_player(x), y_player(y){}

map::map(const map& other): pokemoni(other.pokemoni), player(other.player), x_player(other.x_player), y_player(other.y_player){
    for(const auto& pot: other.potions)
        this->potions.emplace_back(pot->clone());
}

map& map::operator=(map other){
    swap(*this, other);
    return *this;
}

void swap(map&map1, map& map2){
    std::swap(map1.pokemoni, map2.pokemoni);
    std::swap(map1.potions, map2.potions);
    swap(map1.player, map2.player);
    std::swap(map1.x_player, map2.x_player);
    std::swap(map1.y_player, map2.y_player);
}
std::ostream& operator<<(std::ostream& os, const map& other){
    os << other.player;
    os << "X_player: " << other.x_player << " Y_player: " << other.y_player << "\n";
    for(const auto & k : other.pokemoni){
        os << k.get_name() << " HP:" << k.get_HP() << "\n";
    }
    os << "\nPotions:\n";
    for(const auto & pot: other.potions){
        os << *pot << "\n";
    }
    return os;
}
map::~map() = default;