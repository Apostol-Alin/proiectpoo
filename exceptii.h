//
// Created by Utilizator on 01/05/2023.
//

#ifndef OOP_EXCEPTII_H
#define OOP_EXCEPTII_H
#include <stdexcept>

class game_error : public std::runtime_error{
    using std::runtime_error::runtime_error;
};

class potion_error : public game_error{
    using game_error::game_error;
};

class pokemon_error : public game_error{
    using game_error::game_error;
};

class invalid_option : public std::out_of_range{
    using std::out_of_range::out_of_range;
};

#endif //OOP_EXCEPTII_H
