#include <iostream>
#include <random>
#include "Skill.h"
float gen_rand_float(float A, float B){
    return A + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(B-A)));
}
Skill::Skill():type((SkillType)trans),attr((Attr)none),must_hit(0),speed(8),power(0),total_pp(0),temp_pp(0),stage(0){}
int Skill::get_basic_power_damage(int my_atk, int rv_def, int base, bool rand){
    if(!rand){
        return (42 * base * my_atk / rv_def / 50 + 2) * 0.9;
    }
    else{
        return (42 * base * my_atk / rv_def / 50 + 2) * gen_rand_float(0.8, 1);
    }
}
