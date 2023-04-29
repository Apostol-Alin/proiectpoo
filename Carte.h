//
// Created by Utilizator on 22/04/2023.
//

#ifndef OOP_CARTE_H
#define OOP_CARTE_H
#include <iostream>
#include <string>

class Carte {
    std::string rarity;
    int stage;
    static std::string generate_random_rarity();
public:
    [[nodiscard]] std::string& get_rarity();
    [[nodiscard]] int get_stage() const;
    void increase_stage();
    explicit Carte( int stage_ = 1);
    Carte(const Carte& other);
    Carte& operator=(const Carte& other);
    friend std::ostream& operator<<(std::ostream& os, const Carte& c);
    ~Carte();
};


#endif //OOP_CARTE_H
