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
//    void pokemon_encounter(){
//
//    }d

void map::start_game(){
    gen();
    entry_message();
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
map::map(const Player& player_, int x, int y, std::vector<Pokemon> pokemoni_) : pokemoni(std::move(pokemoni_)), player(player_), x_player(x), y_player(y) {}