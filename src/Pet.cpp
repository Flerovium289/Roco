#include <iostream>
#include <random>
#include "Pet.h"
#include <string>
using namespace std;
int getRand(int a, int b){
    return (rand() % (b-a+1))+ a;
}
//SixDim
SixDim::SixDim():HP(0),P_atk(0),M_atk(0),P_def(0),M_def(0),speed(0){};
SixDim::SixDim(int hp, int P_a, int P_d, int M_a, int M_d, int sp){
    HP = hp;
    P_atk = P_a;
    M_atk = M_a;
    P_def = P_d;
    M_def = M_d;
    speed = sp;
}
void SixDim::set_six_dim(int hp, int P_a, int P_d, int M_a, int M_d, int sp){
    HP = hp;
    P_atk = P_a;
    M_atk = M_a;
    P_def = P_d;
    M_def = M_d;
    speed = sp;
}
void SixDim::set_six_dim(SixDim &sd){
    HP = sd.HP;
    P_atk = sd.P_atk;
    M_atk = sd.M_atk;
    P_def = sd.P_def;
    M_def = sd.M_def;
    speed = sd.speed;
}

//PetRaceValue
PetRaceValue::PetRaceValue():SixDim(){}
void PetRaceValue::set_race_value(SixDim &sd){
    SixDim::set_six_dim(sd);
}

//Talent
Talent::Talent(){}
void Talent::generate_random_talent(int a, int b){
    int randoms[6] = {0};
    for(int i = 0; i < 6; i++){
        randoms[i] = getRand(a, b);
    }
    set_six_dim(randoms[0],randoms[1],randoms[2],randoms[3],randoms[4],randoms[5]);
}
void Talent::set_talent(SixDim &sd){set_six_dim(sd);}

//PetBasicInfo
PetBasicInfo::PetBasicInfo():attr(none){}
PetBasicInfo::PetBasicInfo(string n):name(n),attr(none){}
int PetBasicInfo::get_HP(){
    return panel_ability_value.HP;
}
int PetBasicInfo::get_M_atk(){
    return panel_ability_value.M_atk;
}
int PetBasicInfo::get_M_def(){
    return panel_ability_value.M_def;
}
int PetBasicInfo::get_P_atk(){
    return panel_ability_value.P_atk;
}
int PetBasicInfo::get_P_def(){
    return panel_ability_value.P_def;
}
int PetBasicInfo::get_speed(){
    return panel_ability_value.speed;
}
void PetBasicInfo::set_basic_info(SixDim &sd){
    panel_ability_value.set_six_dim(sd);
}
int get_normal_ability_val(int rv){
    return rv * 2 + 5;
}
void PetBasicInfo::generate_basic_info(Attr at, SixDim &rv, SixDim &tl){
    attr = at;
    race_value.set_race_value(rv);
    talent.set_talent(tl);

    panel_ability_value.HP = race_value.HP * 2 + 110 + talent.HP;
    panel_ability_value.M_atk = get_normal_ability_val(race_value.M_atk) + talent.M_atk;
    panel_ability_value.P_atk = get_normal_ability_val(race_value.P_atk) + talent.P_atk;
    panel_ability_value.M_def = get_normal_ability_val(race_value.M_def) + talent.M_def;
    panel_ability_value.P_def = get_normal_ability_val(race_value.M_def) + talent.P_def;
    panel_ability_value.speed = get_normal_ability_val(race_value.speed) + talent.speed;

}
void PetBasicInfo::add_effort_point(int point, int* item){
    *item += floor(point / 4);
}
//在generate_basic_info、add_effort后调用
void PetBasicInfo::add_characteristic(int* add_item, int* sub_item){
    (*add_item) *= 1.1;
    (*sub_item) *= 0.9;
}

void PetBasicInfo::add_weapon(int point, int* item){
    *item += point;
}
void PetBasicInfo::add_guardian_beast(int val){
    panel_ability_value.HP += val;
    panel_ability_value.M_atk += val;
    panel_ability_value.P_atk += val;
    panel_ability_value.M_def += val;
    panel_ability_value.P_def += val;
}
void PetBasicInfo::add_intimacy(int point, int* item){
    *item += point;
}
void PetBasicInfo::print_info(){
    cout << "名称: " << name << endl;
    cout << "精力: " << panel_ability_value.HP << endl;
    cout << "物攻: " << panel_ability_value.P_atk << endl;
    cout << "防御: " << panel_ability_value.P_def << endl;
    cout << "魔攻: " << panel_ability_value.M_atk << endl;
    cout << "魔抗: " << panel_ability_value.M_def << endl;
    cout << "速度: " << panel_ability_value.speed << endl;
}
