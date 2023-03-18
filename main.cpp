#include <iostream>
#include <string>
#include <vector>
//#include <random>
//class Actiune{
//    std::string type;
//    int energy_cost;
//public:
//    Actiune(const std::string type_, int energy_cost_) : type(type_), energy_cost(energy_cost_) {};
//
//
//};

class Power{
    std::string name;
    std::string description;
    std::string power_type;
    int energy_cost;
    float damage;

public:
    [[nodiscard]] float get_dmg() const{ return damage;}
    [[nodiscard]] int get_energy_cost() const{ return energy_cost;}
    [[nodiscard]] std::string get_power_type() const{ return power_type;}
    [[nodiscard]] std::string get_name() const{ return name;}
    explicit Power(const std::string& name_="power", const std::string& description_="-", const std::string& power_type_="-", float damage_=0, int energy_cost_ = 0){
        this->name = name_;
        this->description = description_;
        this->power_type = power_type_;
        this->damage = damage_;
        this->energy_cost = energy_cost_;
        //std::cout<<"Constructor de initializare pentru Power\n";
    }
    Power(const Power& other): name(other.name), description(other.description), power_type(other.power_type), energy_cost(other.energy_cost), damage(other.damage){
        //std::cout<<"Constructor de copiere pentru Power\n";
    }
    Power& operator=(const Power& other){
        name = other.name;
        description = other.description;
        power_type = other.power_type;
        damage = other.damage;
        energy_cost = other.energy_cost;
        //std::cout<<"operator= de copiere pentru Power\n";
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const Power& p){
        os<<"Name of power: "<<p.name<<"\n"<<"Description: "<<p.description<<"\n"<<"Power type: "<<p.power_type<<"\n"<<"Damage: "<<p.damage<<"\n"<<"Energy cost:"<<p.energy_cost<<"\n";
        return os;
    }
    ~Power(){// std::cout<<"Destructor Power\n";
    }

};
class Pokemon {
    std::string name;
    std::string type;
    std::vector <Power> attack;
    std::string weakness;
    std::string resistance;
    int retreat_cost;
    float HP;
    float max_HP;
    float length;
    int weight;
    float damage_taken_modifier;
    float damage_dealt_modifier;
    int energy;
    int total_energy;
    [[nodiscard]] const Power* get_power(unsigned int i) const{
        return &attack.at(i-1);
    }

public:

    [[nodiscard]] float get_HP() const{ return HP;}
    [[nodiscard]] bool is_alive() const{ return HP>0.f;}
    [[nodiscard]] int get_energy() const{ return total_energy;}
//    [[nodiscard]] float get_attack_damage(unsigned int i) const{
//        return get_power(i)->get_dmg();
//    }
    void check_weakness_resistance(const Power& p){
        if(this->weakness == p.get_power_type())
            update_damage_taken_modifier(0.9f);
        if(this->resistance ==  p.get_power_type())
            update_damage_taken_modifier(1.1f);
    }
    void take_damage(float damage_){
        HP -= damage_ * damage_taken_modifier;
        if(HP < 0.f){
            HP = 0;
        }
    }
    void restore_energy(int value = 20){
        energy += value;
        if(energy > total_energy)
            energy = total_energy;
    }
    [[maybe_unused]] const Power* choose_attack(){
        std::cout<<"Current energy: "<<energy<<"\n";
        std::cout<<"Please choose an attack:\n";
        unsigned int i = 1;
        for(const auto & a : attack){
            std::cout<<i<<". "<<a.get_name()<<"\t"<<"Energy cost: "<<a.get_energy_cost()<<"\n";
            i++;
        }
        std::cin >> i;
        const Power * temp = get_power(i);
        if(temp->get_energy_cost() <= energy){
            energy -= temp->get_energy_cost();
            return get_power(i);
        }
        else
            throw std::logic_error("Not enough energy\n");
    }

    [[maybe_unused]] std::vector <const Power*> choose_combo(){
        //vreau, de fapt std::vector <const Power*>* choose_combo
        //si sa returnez &combos
        //insa primesc warning ca returnez referinta
        //catre ceva pus pe stack
        std::vector <const Power*> combos;
        const Power * chosen_power = nullptr;
        unsigned int i;
        chosen_power = choose_attack();
        combos.emplace_back(chosen_power);
        do{
//            combo_attack:
//            1st step -> choose an atack and create the vector of attacks
            std::cout << "Choose an action:\n";
            std::cout << "1. Add attack to combo\n";
            std::cout << "2. Remove attack from combo\n";
            std::cout << "3. Finish combo\n";
            std::cin >> i;
            try {
                switch (i) {
                    case 1: {
                        chosen_power = choose_attack();
                        combos.emplace_back(chosen_power);
                        break;
                    }
                    case 2: {
                        unsigned int k = 0;
                        std::cout<<"Choose an attack to remove from your combo:\n";
                        for(const auto & a : combos){
                            std::cout<<k+1<<"."<<a->get_name()<<"\n";
                            k++;
                        }
                        std::cin >> k;
                        energy += combos.at(k-1)->get_energy_cost();
                        combos.erase(combos.begin()+k-1);
                        break;
                    }
                    case 3: {
                        if(!combos.empty())
                            return combos;
                        else
                            std::cout<<"The combo is empty\n Please choose at least one attack!\n";
                    }
                    default: {
                        std::cout << "Invalid option\n";
                    }
                }
            }
            catch(std::out_of_range const &exc){
                std::cout<<exc.what();
            }
            catch(std::logic_error const &exc){
                std::cout<<exc.what();
            }
//            2nd step -> ask user for action : add attack to combo, remove attack from combo, finish combo
//            3rd step  -> if add attack -> call choose_attack -> go to step 2
//                    -> if remove attack -> display vector of attacks chosen so far -> get index for removal -> go to step 2
//                    -> else return the vector
//            catch error -> repeat from step 2
        }while(true);
    }
    void heal(float healing_value){
        HP += healing_value;
        if(HP > max_HP)
            HP = max_HP;
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
    Pokemon(const std::string& name_, const std::string& type_, std::vector <Power>& attack_, const std::string& weakness_,const std::string& resistance_, int retreat_cost_,float max_HP_, float length_, int weight_, float damage_taken_modifier_ = 1.f, float damage_dealt_modifier_ = 1.f, int total_energy_=0):
            name(name_),type(type_), attack(attack_), weakness(weakness_), resistance(resistance_), retreat_cost(retreat_cost_), HP(max_HP_), max_HP(max_HP_), length(length_), weight(weight_), damage_taken_modifier(damage_taken_modifier_), damage_dealt_modifier(damage_dealt_modifier_), energy(total_energy_), total_energy(total_energy_){}

//    Pokemon(const std::string& name_, const std::string& type_,const std::string& attack_name, const std::string& attack_description_, const std::string& attack_type, float damage, const std::string& weakness_, const std::string& resistance_, int retreat_cost_, float HP_, float length_, int weight_, float damage_taken_modifier_ = 1, float damage_dealt_modifier_ = 1):
//            name(name_), type(type_), attack(attack_name,attack_description_, attack_type, damage),weakness(weakness_), resistance(resistance_), retreat_cost(retreat_cost_), HP(HP_), length(length_), weight(weight_), damage_taken_modifier(damage_taken_modifier_), damage_dealt_modifier(damage_dealt_modifier_){}
    Pokemon(const Pokemon& other): name(other.name), type(other.type), attack(other.attack), weakness(other.weakness), resistance(other.resistance), retreat_cost(other.retreat_cost), HP(other.HP), max_HP(other.max_HP), length(other.length), weight(other.weight), damage_taken_modifier(other.damage_taken_modifier), damage_dealt_modifier(other.damage_dealt_modifier), energy(other.energy), total_energy(other.total_energy){}
    Pokemon& operator=(const Pokemon& other){
        name = other.name;
        type = other.type;
        attack = other.attack;
        weakness = other.weakness;
        resistance = other.resistance;
        retreat_cost = other.retreat_cost;
        HP = other.HP;
        max_HP = other.max_HP;
        length = other.length;
        weight = other.weight;
        damage_dealt_modifier = other.damage_dealt_modifier;
        damage_taken_modifier = other.damage_taken_modifier;
        energy = other.energy;
        total_energy = other.total_energy;
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const Pokemon& p){
        os<<"Name: "<<p.name<<"\n"<<"Pokemon type: "<<p.type<<"\n"<<"HP: "<<p.HP<<"\tEnergy: "<<p.energy<<"\n";
        os<<"Attacks:\n";
        for(const auto & k: p.attack){
            os<<"\t"<<k<<"\n";
        }
        os<<"Weakness: "<<p.weakness<<"\n"<<"Resistance: "<<p.resistance<<"\n"<<"Length: "<<p.length<<"     "<<"Weight: "<<p.weight<<"\n";
        return os;
    }
    ~Pokemon()= default;

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
    static std::string generate_random_rarity(){
        int k = rand() % 1000;
        if(k >= 990)
            return "Holographic";
        if(k >= 800)
            return "Golden";
        return "Basic";
    }
public:
    Carte( int stage_, const Pokemon& poke_) : rarity(generate_random_rarity()), stage(stage_), pokemon(poke_){}
    Carte(const Carte& other) : rarity(other.rarity), stage(other.stage), pokemon(other.pokemon){}
    Carte& operator=(const Carte& other){
        rarity = other.rarity;
        stage = other.stage;
        pokemon = other.pokemon;
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const Carte& c){
        os<<c.rarity<<"     "<<"Stage: "<<c.stage<<"\n"<<c.pokemon;
        return os;
    }
    ~Carte()= default;
};

//class Pokeball va fi folosit pentru mostenire
//class Pokeball{
//
//};
class Player{
    std::vector <Carte> c;
    int money;
public:
    [[nodiscard]] int get_money() const{ return money;}
    void update_money(int cost){ money -= cost;}
    explicit Player(std::vector <Carte>& c_, int money_ = 200) : c(c_), money(money_){}
    Player(const Player& other)= default;
    Player& operator=(const Player&other)= default;
    ~Player() = default;
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
    Pokemon pika("Pikachu","Lightning",puteri_pikachu,"Earth","-",10,50.f,0.4064f,13,1.f,1.f,100);
    Pokemon bulb("Bulbasaur","Earth",puteri_bulb,"Fire","-",10,60.f,0.7112f,15,1.f,1.f,100);
    Pokemon charm("Charmander","Fire",puteri_charm,"Water","-",10,50.f,0.6096f,19,1.f,1.f,100);
    Carte c_pika(1,pika);
    Carte c_bulb(1,bulb);
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
    pika.take_damage(20.f);
    std::cout<<"HP Pikachu dupa ce a luat damage: "<<pika.get_HP()<<"\n";
    pika.heal(30.f);
    std::cout<<"HP Pikachu dupa heal: "<<pika.get_HP()<<"\n";
    std::cout<<"Is Pikachu still alive after that?:  "<<pika.is_alive()<<"\n";
    std::cout<<pika.get_energy()<<'\n';
    bulb.update_damage_dealt_modifier(2.f);
    bulb.update_damage_taken_modifier(1.5f);
    bulb.reset_damage_dealt_modifier();
    bulb.reset_damage_taken_modifier();
    pika.check_weakness_resistance(power_bulbasaur);
    //*********************
//    rulati pentru a creea un combo de attackuri pentru pikachu
    float dmg = 0.f;
    std::vector <const Power*> combo = (pika.choose_combo());
    for(const auto & k : combo){
        dmg += k->get_dmg();
    }
    pika.restore_energy();
    std::cout<<dmg<<'\n';
    std::cout<<power_bulbasaur.get_dmg()<<'\n';
    std::vector<Carte> c;
    c.emplace_back(c_bulb);
    Player player1(c,3000);
    player1.update_money(20);
    std::cout<<player1.get_money();
    return 0;

}