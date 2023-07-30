#ifndef _PET_H
#define _PET_H
#include <iostream>
#define ATTR_NUM 18
enum Attr{normal, ghost, Mwater, none};
int attr_table[ATTR_NUM][ATTR_NUM];

class SixDim{
public:
    //精力，物攻，防御，魔攻，魔抗，速度
    SixDim();
    //精力，物攻，防御，魔攻，魔抗，速度
    SixDim(int hp, int pa, int pd, int ma, int md, int sp);
    void set_six_dim(int hp, int pa, int pd, int ma, int md, int sp);
    void set_six_dim(SixDim &sd);
    int HP;
    int P_atk;//物攻
    int M_atk;
    int P_def;
    int M_def;
    int speed;
};
class PetRaceValue: public SixDim{
public:
    PetRaceValue();
    void set_race_value(SixDim &sd);
};
class Talent: public SixDim{
public:
    Talent();
    void generate_random_talent(int a, int b);
    void set_talent(SixDim &sd);
};
//基础信息
class PetBasicInfo{
public:
    PetBasicInfo();
    PetBasicInfo(std::string name);
    int get_HP();
    int get_P_atk();
    int get_M_atk();
    int get_P_def();
    int get_M_def();
    int get_speed();
   
    void generate_basic_info(Attr attr, SixDim &rv, SixDim &tl);
    void set_basic_info(SixDim &sd);//直接输入面板
    void add_effort_point(int point, int* item);
    void add_characteristic(int* add_item, int* sub_item);

    void add_weapon(int point, int* item);
    void add_guardian_beast(int val);
    void add_intimacy(int point, int* item);
    
    void print_info();

    std::string name;
    Attr attr;//属性
    PetRaceValue race_value;
    Talent talent;

    SixDim panel_ability_value;
};
#endif
