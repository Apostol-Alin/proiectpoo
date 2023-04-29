//
// Created by Utilizator on 22/04/2023.
//
#ifndef OOP_POWER_H
#define OOP_POWER_H
#include <string>
#include <iostream>
class Power{
    std::string name;
    std::string description;
    std::string power_type;
    float damage;
    int energy_cost;

public:
    [[nodiscard]] float get_dmg() const;
    [[nodiscard]] int get_energy_cost() const;
    [[nodiscard]] std::string get_power_type() const;
    [[nodiscard]] std::string get_name() const;
    Power();
    explicit Power(const std::string& name_, const std::string& description_, const std::string& power_type_, float damage_, int energy_cost_);
    Power(const Power& other);
    Power& operator=(const Power& other);
    friend std::ostream& operator<<(std::ostream& os, const Power& p);
    ~Power();
};

#endif //OOP_POWER_H
