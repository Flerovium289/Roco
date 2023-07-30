#ifndef _COMBAT_PET
#define _COMBAT_PET
#include "Skill.h"
//一只宠物的对战信息
class CombatPet{
public:
    CombatPet();
    void set_combat_info(PetBasicInfo& pbi, SixDim& pti, AbnormalState& as, StrengthenLevel &sl, Marks &marks);
    //将技能sk填入技能列表的idx位置
    void set_skills(int idx, Skill &sk);
    //当前宠物是否存活
    bool is_alive();
    //返回当前HP
    int get_HP();
    //返回当前物攻值（加上强化等级）
    int get_P_atk();
    //返回当前防御值（加上强化等级）
    int get_P_def();
    //返回当前魔攻值（加上强化等级）
    int get_M_atk();
    //返回当前魔抗值（加上强化等级）
    int get_M_def();
    //返回当前速度（加上强化等级）
    int get_speed();
    //返回当前标记
    std::vector<int> get_int_marks();
    std::vector<FloatMark> get_float_marks();

    //使用下标为idx的技能，将其加入used_skill队列
    //考虑如何扣除pp
    void use_skill(int idx, std::vector<SkillEffect>& skill_effect_queue);
    
    //加入血脉

    PetBasicInfo pet_basic_info;
    SixDim pet_temp_info;
    AbnormalState abnormal_state;
    StrengthenLevel strengthen_level;
    Marks marks;
    Skill skills[4];
    std::vector<int> used_skill;//储存使用过的技能序列
};
#endif