#ifndef _SKILL_H
#define _SKILL_H

#include <iostream>
#include <vector>
#include "SkillEffect.h"
class Player;
#define MAX_SKILL_NUM 4
enum SkillType {magic, physics, trans};
//技能基类，后续专属技能继承Skill，重载trigger函数
class Skill{
public:
    Skill();
    std::string name;
    SkillType type;//技能类型
    Attr attr;

    int must_hit;//1为必中，0为普通，-1为被抓瞎
    int speed;//出招速度
    int power;//威力值，为0则为变化类技能
    int total_pp;
    int temp_pp;
    int stage;//技能触发段数，若stage != 0则当前回合需要触发一次，并且stage--
    //计算基础威力伤害值（不计算天气）
    int get_basic_power_damage(int my_atk, int rv_def, int base, bool rand);
    //触发当前技能效果（考虑天气）
    virtual void trigger(Player* src, Player* des, std::vector<SkillEffect>& skill_effect_queue, bool use_rand){};
};
#endif