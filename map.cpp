//
// Created by Utilizator on 30/04/2023.
//

#include "map.h"
#include "exceptii.h"
#include <random>
#include <utility>
void map::draw(){
    rlutil::cls();
    //rlutil::locate(1, map_size + 1);
    rlutil::setColor(2);
    std::cout << "Score: " << player.get_score() << "\n";
    rlutil::setColor(14);
    std::cout << "Money: " << player.get_money() << "\n";
    rlutil::setColor(15);
    std::cout << "Press 1 to access shop, 2 for potion inventory, 3 for pokemon inventory, 4 to heal your Pokemon...\n";
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
    // Create a random number generator engine
    std::random_device rd;
    std::mt19937 gen(rd());

// Define the distribution for generating random numbers
    std::uniform_int_distribution<int> dist(0, 5);

// Resize and initialize the layout
    layout.resize(map_size, std::vector<std::string>(map_size));
    for (unsigned int j = 0; j < map_size; j++) {
        for (unsigned int i = 0; i < map_size; i++) {
            if (i == 0 || i == map_size - 1 || j == 0 || j == map_size - 1)
                layout[i][j] = "%";
            else {
                if (dist(gen) == 0 && i != 1 && j != 1)
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
    rlutil::setColor(15);
    unsigned int i = 1;
    for(const auto & pot: potions){
        std::cout << i << "." << pot->get_name() << " | cost: " << pot->get_cost() << " | turns until old: " << pot->get_turns_until_old() << "\n";
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
                try {
                    player.add_potion(potions[i - 1]);
                    player.update_money(-potion_cost);
                    break;
                }
                catch(overflow_capacity& err){
                    std::cout << err.what() << "\n";
                }
            }
        }
        else if(i == 0) { break;}
        else {std::cout << "Invalid option!\n";}
    }
}
void map::player_turn(Pokemon& player_pokemon, Pokemon& enemy_pokemon){
    unsigned int input;
    std::cout << "It's the Player's turn!\n";
    std::cout << "Press 0 if you wish to skip turn\n";
    std::cout << "Press 1 to choose an attack\n";
    std::cout << "Press 2 to choose a combo\n";
    std::cout << "Press 3 to choose a potion to apply\n\n";
    while(true){
        std::cout << "Player's pokemon:" << player_pokemon.get_name();
        rlutil::setColor(12);
        std::cout << " | HP: " << player_pokemon.get_HP();
        rlutil::setColor(14);
        std::cout << " | Energy: " << player_pokemon.get_energy() << "\n";
        rlutil::setColor(15);
        std::cout << "Enemy's pokemon:" << enemy_pokemon.get_name();
        rlutil::setColor(12);
        std::cout << " | HP: " << enemy_pokemon.get_HP();
        rlutil::setColor(14);
        std::cout << " | Energy: " << enemy_pokemon.get_energy() << "\n";
        rlutil::setColor(15);
        std::cin >> input;
        if(input == 0)
            break;
        else if(input == 1){
            if(player_pokemon.can_attack()){
                enemy_pokemon.take_damage(player_pokemon.choose_attack().get_dmg());
                break;
            }
            else std::cout << "You don't have enough energy to perform an attack\n";
        }
        else if(input == 2){
            if(player_pokemon.can_attack()){
                enemy_pokemon.take_damage(player_pokemon.choose_combo());
                break;
            }
            else std::cout << "You don't have enough energy to perform a combo\n";
        }
        else if(input == 3){
            if(player.get_inventory_size()) {
                player.choose_potion(player_pokemon, enemy_pokemon);
            }
            else
                std::cout << "Your inventory is empty\n";
        }
        else std::cout << "Not a valid option... Please choose an action\n";
    }
    player_pokemon.restore_energy();
}
void map::enemy_turn(Pokemon &player_pokemon, Pokemon &enemy_pokemon) {
    unsigned int input;
    std::cout << "It's the enemy's turn!\n";
    std::cout << "Press 0 to skip turn\n";
    std::cout << "Press 1 to choose an attack\n";
    std::cout << "Press 2 to choose a combo\n\n";
    while(true){
        std::cout << "Player's pokemon:" << player_pokemon.get_name();
        rlutil::setColor(12);
        std::cout << " | HP: " << player_pokemon.get_HP();
        rlutil::setColor(14);
        std::cout << " | Energy: " << player_pokemon.get_energy() << "\n";
        rlutil::setColor(15);
        std::cout << "Enemy's pokemon:" << enemy_pokemon.get_name();
        rlutil::setColor(12);
        std::cout << " | HP: " << enemy_pokemon.get_HP();
        rlutil::setColor(14);
        std::cout << " | Energy: " << enemy_pokemon.get_energy() << "\n";
        rlutil::setColor(15);
        std::cin >> input;
        if(input == 0) break;
        else if (input == 1){
            if(enemy_pokemon.can_attack()){
                player_pokemon.take_damage(enemy_pokemon.choose_attack().get_dmg());
                break;
            }
            else std::cout << "You don't have enough energy to attack\n";
        }
        else if (input == 2){
            if(enemy_pokemon.can_attack()){
                player_pokemon.take_damage(enemy_pokemon.choose_combo());
                break;
            }
            else std::cout << "You don't have enough energy to perform a combo\n";
        }
        else std::cout << "Not a valid option... Please choose an action\n";
    }
    enemy_pokemon.restore_energy();
}
bool map::pokemon_encounter() {
    // Create a random number generator engine
    std::random_device rd;
    std::mt19937 gen(rd());
// Define the distribution based on the range of your container
    std::uniform_int_distribution<unsigned int> dist(0, pokemoni.size() - 1);
// Generate a truly random number
    unsigned int j = dist(gen);
    Pokemon enemy_pokemon = pokemoni[j], player_pokemon(enemy_pokemon);
    rlutil::setColor(4);
    std::cout << "You have encountered ";
    rlutil::setColor(15);
    std::cout << enemy_pokemon.get_name() << "\n" << "Please choose a Pokemon from your inventory to fight with!\n";
    player.display_pokemoni();
    unsigned int i;
    unsigned int player_pokemoni_size = player.get_pokemoni_size();
    while(true){
        std::cin >> i;
        if(i >= 1 and i <= player_pokemoni_size){
            player_pokemon = player.choose_pokemon(i);
            break;
        }
        else
            std::cout << "Invalid option\n";
    }
    unsigned int turn = 0;
    while(player_pokemon.is_alive() and enemy_pokemon.is_alive()){
        if(turn % 2 == 0){
            player_turn(player_pokemon,enemy_pokemon);
        }
        else{
            enemy_turn(player_pokemon, enemy_pokemon);
        }
        turn++;
    }
    if(enemy_pokemon.is_alive())
        return true;
    else{
        std::cout <<"You won the fight!\n";
        rlutil::anykey("Press any key to continue the game\n");
        player.add_pokemon(pokemoni[j]);
        return false;
    }
}

void map::start_game(){
    gen();
    entry_message();
    rlutil::setColor(2);
    std::cout << "Use WSAD keys to move and 0 to exit the game\n";
    std::cout << "Press 1 to access the shop\n";
    std::cout << "Press 2 to see your potion inventory\n";
    std::cout << "Press 3 to see your pokemon inventory\n";
    std::cout << "Press 4 to heal your pokemon if you can...\n";
    std::cout << "Note: every move you make on the board ages your current potions by 1\n";
    rlutil::setColor(6);
    rlutil::anykey("Hit any key to start.\n");
    draw();
    while (true) {
        // Input
        if (kbhit()) {
            char k = rlutil::getkey();
            int oldx = x_player, oldy = y_player;
            player.update_score();
            if (k == 'a') { x_player--; player.increase_age_to_potions();}
            else if (k == 'd') { x_player++; player.increase_age_to_potions();}
            else if (k == 'w') { y_player--; player.increase_age_to_potions();}
            else if (k == 's') { y_player++; player.increase_age_to_potions();}
            else if (k == '1') { access_shop();}
            else if (k == '2') { player.display_potions(); rlutil::anykey("Hit any key to continue\n");}
            else if (k == '3') { player.display_pokemoni(); rlutil::anykey("Hit any key to continue\n");}
            else if (k == '4') { player.heal_pokemoni();}
            else if (k == '0') break;
            if (layout[x_player][y_player] == "%") { x_player = oldx; y_player = oldy; }
            if (layout[x_player][y_player] == "P") {
                if(pokemon_encounter()) {
                    std::cout << "You lost...\n";
                    player.update_score();
                    std::cout << "Final score: " << player.get_score() << "\n";
                    break;
                }
                else{
                    player.update_score();
                    player.update_money(50);
                    layout[x_player][y_player] = "D";
                }
            }
            // Drawing
            draw();
        }
    }
    rlutil::setColor(14);
    std::cout << "You have gathered " << player.get_score() << " points during your game time\n";
    rlutil::setColor(15);
}

map::map(const Player& player_, int x, int y, std::vector<Pokemon> pokemoni_, std::vector<std::shared_ptr<Potion>> potions_) :
pokemoni(std::move(pokemoni_)), potions(std::move(potions_)), player(player_), x_player(x), y_player(y){}

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

map& map::get_map(const Player& player_, int x, int y, std::vector<Pokemon> pokemoni_, std::vector<std::shared_ptr<Potion>> potions_){
    static map harta{player_,x,y,std::move(pokemoni_),std::move(potions_)};
    return harta;
}

map::~map() = default;