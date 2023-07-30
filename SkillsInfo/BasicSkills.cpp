#include "BasicSkills.h"
ZhuaNao::ZhuaNao(): Skill(){
    name = "抓挠";
    type = SkillType::physics;
    attr = Attr::normal;
    must_hit = 0;
    speed = 8;
    power = 40;
    total_pp = 35;
    temp_pp = 35;
    stage = 0;
}
/*
trigger：
src：攻击方当前战斗面板
des：被攻击方当前战斗面板
des_idx：被攻击方的索引
SkillEffect_queue：技能效果队列
use_rand：伤害是否考虑随机浮动
*/
void ZhuaNao::trigger(Player* src, Player* des, std::vector<SkillEffect>& skill_effect_queue, bool use_rand){
    SkillEffect effect;
    effect.skill_name = name;
    effect.object = des->temp_pet_idx;
    effect.HP_change = -get_basic_power_damage(src->pets[src->temp_pet_idx].get_P_atk(), des->pets[des->temp_pet_idx].get_P_def(), power, use_rand);
    skill_effect_queue.push_back(effect);
    temp_pp--;
}
