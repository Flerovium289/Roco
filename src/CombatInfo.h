#ifndef _COMBATINFO_H
#define _COMBATINFO_H
#include <iostream>
#include <vector>
#include <map>
#include "Pet.h"
#include "Skill.h"
#include "AbnormalState.h"
//标记效果
//整型标记：可以用int表示的标记，int表示生效的回合数
enum CombatMark{double_loss_pp, must_dodge, must_hit, must_blaze, lock_strength, immune_expel, immune_neg_strength, full_rebound_damage, 
half_rebound_damage, offset_damage, rebound_effect, shield, immune_blaze};
//浮点型标记：
enum CombatFloatMark{treatment_effect, damage_reduction, damage_increment};
std::map<int, std::string> Idx2Mark{
{double_loss_pp, "额外消耗1pp"}, {must_dodge, "必闪"}, {must_hit, "必中"}, {must_blaze, "必暴"}, {lock_strength, "锁定强化"},
{immune_expel, "免疫驱逐"}, {immune_neg_strength, "免疫负面强化"}, {full_rebound_damage, "反弹伤害"}, {half_rebound_damage, "返还伤害"},
{offset_damage, "格挡伤害"}, {rebound_effect, "反弹效果"},{shield, "护盾值"},{immune_blaze, "免疫暴击"}
};
std::map<int, std::string> Idx2FloatMark{
{treatment_effect, "治疗效果"}, {damage_reduction, "减伤"}, {damage_increment,  "增伤"}
};
//强化等级
class StrengthenLevel{
public:
    StrengthenLevel();
    void print_strengthen_level();
    int P_atk;
    int M_atk;
    int P_def;
    int M_def;
    int speed;
    int hit;
    int dodge;
};
struct FloatMark{
    float num;//浮点型标记中的浮点值
    int round;//还需持续回合数
};
//战斗类标记
class Marks{
public:
    Marks();
    //获取正在生效的int_marks
    std::vector<int> get_int_marks();
    //获取正在生效的float_marks
    std::vector<FloatMark> get_float_marks();

    void print_marks();

    std::map<std::string, int> Mark2Idx;
    std::map<std::string, int> FloatMark2Idx;

    std::vector<int> int_marks;//bitmap格式的int_mark
    std::vector<FloatMark> float_marks;
};

#endif