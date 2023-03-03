#include <iostream>
#include <string>

class Power{

    std::string name;
    std::string description;
    std::string power_type;
    float damage;

public:
    const float get_dmg() const{ return damage;}
    Power(const std::string& name_="power", const std::string& description_="-", const std::string& power_type_="-", float damage_=0){
        this->name = name_;
        this->description = description_;
        this->power_type = power_type_;
        this->damage = damage_;
        //std::cout<<"Constructor de initializare pentru Power\n";
    }
    Power(const Power& other): name(other.name), description(other.description), power_type(other.power_type), damage(other.damage){
        //std::cout<<"Constructor de copiere pentru Power\n";
    }
    Power& operator=(const Power& other){
        name=other.name;
        description=other.description;
        power_type=other.power_type;
        damage=other.damage;
        //std::cout<<"operator= de copiere pentru Power\n";
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const Power& p){
        os<<"Name of power: "<<p.name<<"\n"<<"Description: "<<p.description<<"\n"<<"Power type: "<<p.power_type<<"\n"<<"Damage: "<<p.damage<<"\n";
        return os;
    }
    ~Power(){// std::cout<<"Destructor Power\n";
    }

};

//class Actiune{
//std::string type;
//int energy_cost;
//};
class Pokemon {
    std::string name;
    std::string type;
    Power attack;
    std::string weakness;
    std::string resistance;
    int retreat_cost;
    float HP;
    float length;
    int weight;
    float damage_taken_modifier;
    float damage_dealt_modifier;

public:

    float get_HP() {return HP;}
    bool is_alive(){ return HP>0;}
    float get_attack_damage(){
        return attack.get_dmg()*damage_dealt_modifier;
    }
    void take_damage(float damage_){
        HP = std::max(HP -= damage_*damage_taken_modifier, 0.f);
    }
    void heal(float healing_value){
        HP += healing_value;
    }
    void update_damage_taken_modifier(float modifier){
        damage_taken_modifier *= modifier;
    }
    void update_damage_dealt_modifier(float modifier){
        damage_dealt_modifier *= modifier;
    }
    void reset_damage_taken_modifier(float modifier){
        damage_taken_modifier = 1;
    }
    void reset_damage_dealt_modifier(float modifier){
        damage_dealt_modifier = 1;
    }

    Pokemon(const std::string& name_, const std::string& type_, const Power& attack_, const std::string& weakness_,const std::string& resistance_, int retreat_cost_,int HP_, float length_, int weight_, float damage_taken_modifier_ = 1, float damage_dealt_modifier_ = 1):
            name(name_),type(type_), attack(attack_), weakness(weakness_), resistance(resistance_), retreat_cost(retreat_cost_), HP(HP_), length(length_), weight(weight_), damage_taken_modifier(damage_taken_modifier_), damage_dealt_modifier(damage_dealt_modifier_){}

    Pokemon(const std::string& name_, const std::string& type_,const std::string& attack_name, const std::string& attack_description_, const std::string& attack_type, int damage, const std::string& weakness_, const std::string& resistance_, int retreat_cost_, int HP_, float length_, int weight_, float damage_taken_modifier_ = 1, float damage_dealt_modifier_ = 1):
            name(name_), type(type_), attack(attack_name,attack_description_, attack_type, damage),weakness(weakness_), resistance(resistance_), retreat_cost(retreat_cost_), HP(HP_), length(length_), weight(weight_), damage_taken_modifier(damage_taken_modifier_), damage_dealt_modifier(damage_dealt_modifier_){}
    Pokemon(const Pokemon& other): name(other.name), type(other.type), attack(other.attack), weakness(other.weakness), resistance(other.resistance), retreat_cost(other.retreat_cost), HP(other.HP), length(other.length), weight(other.weight), damage_taken_modifier(other.damage_taken_modifier), damage_dealt_modifier(other.damage_dealt_modifier){}
    Pokemon operator=(const Pokemon& other){
        name = other.name;
        type = other.type;
        attack = other.attack;
        weakness = other.weakness;
        resistance = other.resistance;
        retreat_cost = other.retreat_cost;
        HP = other.HP;
        length = other.length;
        weight = other.weight;
        damage_dealt_modifier = other.damage_dealt_modifier;
        damage_taken_modifier = other.damage_taken_modifier;
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const Pokemon& p){
        os<<"Name: "<<p.name<<"     "<<"Pokemon type: "<<p.type<<"     "<<"HP: "<<p.HP<<"\n"<<p.attack<<p.weakness<<"\n"<<p.resistance<<"\n"<<"Length: "<<p.length<<"     "<<"Weight: "<<p.weight<<"\n";
        return os;
    }
    ~Pokemon(){}

};
class Potiune{
    std::string potion_name;
public:
    void apply_effect(Pokemon *poke){}
};
//class Potiune_Heal : public Potiune{
//    float healing_value;
//public:
//    void apply_effect(Pokemon *poke){
//        poke.heal(healing_value);
//    }
//};
class Carte {
    std::string rarity;
    int stage;
    Pokemon pokemon;
};

int main() {

    Power p1{"Curse","Blablabla","Dark",20},p2=p1;
    Pokemon pikachu{"Pikachu","Lightning",p1,"Earth","-",30,100,1.56,30};
    Pokemon da{"Charmander", "Fire", "Flamethrower", "DADADA","Fire", 40, "Water", "Earth", 20,90,1.60,25};
    //p1.alter_damage(-20);
    std::cout<<pikachu;
    return 0;

}
