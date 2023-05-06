//
// Created by Utilizator on 27/04/2023.
//

#ifndef OOP_POTION_H
#define OOP_POTION_H
#include <string>
#include <memory>
#include "Pokemon.h"
#include <rlutil.h>
class Potion {
    std::string potion_name;
    int potion_cost;
    int turns_until_old;
    int current_turns = 0;
    virtual void display(std::ostream &) const;
protected:
    Potion(const Potion &other);
    Potion &operator=(const Potion &other);
    explicit Potion(std::string  potion_name_, int potion_cost_, int truns_until_old_);
    [[nodiscard]] bool old_enough() const;
public:
    friend std::ostream &operator<<(std::ostream &os, const Potion &potion_);
    [[nodiscard]] virtual std::shared_ptr<Potion> clone() const = 0;
    virtual void apply_effect(Pokemon& poke) const = 0;
    virtual void turn_old() = 0;
    virtual void increase_turn_counter();
    virtual ~Potion();
};


#endif //OOP_POTION_H
