#ifndef _BASIC_SKILL_H
#define _BASIC_SKILL_H
#include <vector>
#include "../src/CombatInfo.h"
#include "../src/Skill.h"
#include "../src/Player.h"
class ZhuaNao: public Skill{
    ZhuaNao();
    void trigger(Player* src, Player* des, std::vector<SkillEffect>& skill_effect_queue, bool use_rand);
};
#endif