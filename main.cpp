#include <iostream>
#include <string>

class Power{

    std::string name;
    std::string description;
    std::string power_type;
    float damage;

public:
    float get_dmg() const{ return damage;}
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

    float get_HP() const{return HP;}
    bool is_alive() const{ return HP>0.f;}
    float get_attack_damage(){
        return attack.get_dmg()*damage_dealt_modifier;
    }
    void take_damage(float damage_){
        HP -= damage_*damage_taken_modifier;
        if(HP<0.f){
            HP=0;
        }
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
    void reset_damage_taken_modifier(){
        damage_taken_modifier = 1.f;
    }
    void reset_damage_dealt_modifier(){
        damage_dealt_modifier = 1.f;
    }

    Pokemon(const std::string& name_, const std::string& type_, const Power& attack_, const std::string& weakness_,const std::string& resistance_, int retreat_cost_,float HP_, float length_, int weight_, float damage_taken_modifier_ = 1, float damage_dealt_modifier_ = 1):
            name(name_),type(type_), attack(attack_), weakness(weakness_), resistance(resistance_), retreat_cost(retreat_cost_), HP(HP_), length(length_), weight(weight_), damage_taken_modifier(damage_taken_modifier_), damage_dealt_modifier(damage_dealt_modifier_){}

    Pokemon(const std::string& name_, const std::string& type_,const std::string& attack_name, const std::string& attack_description_, const std::string& attack_type, float damage, const std::string& weakness_, const std::string& resistance_, int retreat_cost_, float HP_, float length_, int weight_, float damage_taken_modifier_ = 1, float damage_dealt_modifier_ = 1):
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
        os<<"Name: "<<p.name<<"     "<<"Pokemon type: "<<p.type<<"     "<<"HP: "<<p.HP<<"\n"<<p.attack<<"Weakness: "<<p.weakness<<"\n"<<"Resistance: "<<p.resistance<<"\n"<<"Length: "<<p.length<<"     "<<"Weight: "<<p.weight<<"\n";
        return os;
    }
    ~Pokemon(){}

};
//class Potiune{
    //std::string potion_name;
//public:
    //void apply_effect(Pokemon *poke){}
//};
//Aici aveam un warning de unused parameter
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
public:
    Carte(const std::string& rarity_, int stage_, const Pokemon& poke_) : rarity(rarity_), stage(stage_), pokemon(poke_){}
    Carte(const Carte& other) : rarity(other.rarity), stage(other.stage), pokemon(other.pokemon){}
    Carte operator=(const Carte& other){
        rarity = other.rarity;
        stage = other.stage;
        pokemon = other.pokemon;
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const Carte& c){
        os<<c.rarity<<"     "<<"Stage: "<<c.stage<<"\n"<<c.pokemon;
        return os;
    }
    ~Carte(){}
};

int main() {

    Power power_bulbasaur("Seed Rain","Unleash a rain of seeds that deals magic damage to foes","Earth",30);
    Power power_pikachu("Tunder Bolt","Zap the enemy to deal damage","Lightning",36);
    Power power_charmander("Flame Thrower","BUUUUUURN!!!!!","Fire",35);
    Pokemon pika("Pikachu","Lightning",power_pikachu,"Earth","-",10,50.f,0.4064,13);
    Pokemon bulb("Bulbasaur","Earth",power_bulbasaur,"Fire","-",10,60.f,0.7112,15);
    Pokemon charm("Charmander","Fire",power_charmander,"Water","-",10,50.f,0.6096,19);
    Carte c_pika("Holographic",1,pika);
    Carte c_bulb("Basic",1,bulb);
    c_bulb=c_pika;
    std::cout<<power_bulbasaur<<"\n";
    std::cout<<charm<<"\n";
    std::cout<<c_pika<<"\n";
    std::cout<<c_bulb<<"\n";
    std::cout<<bulb<<"\n";
    power_bulbasaur=power_charmander;
    std::cout<<power_bulbasaur<<"\n";
    std::cout<<bulb<<"\n";
    std::cout<<"\n";
    std::cout<<"HP Pikachu inainte de a lua damage: "<<pika.get_HP()<<"\n";
    pika.take_damage(bulb.get_attack_damage());
    std::cout<<"HP Pikachu dupa ce a luat damage: "<<pika.get_HP()<<"\n";
    pika.heal(30.f);
    std::cout<<"HP Pikachu dupa heal: "<<pika.get_HP()<<"\n";
    std::cout<<"Is Pikachu still alive after that?:  "<<pika.is_alive()<<"\n";
    bulb.update_damage_dealt_modifier(2.f);
    bulb.update_damage_taken_modifier(1.5);
    bulb.reset_damage_dealt_modifier();
    bulb.reset_damage_taken_modifier();
    return 0;

}
