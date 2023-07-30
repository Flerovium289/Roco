#ifndef _GLOBALENV_H
#define _GLOBALENV_H
#include "Player.h"
#include "WeatherEnvironment.h"
#include <iostream>
#include <vector>
#define MAX_PET_NUM 6
using namespace std;
class Administrator{
public:
    Administrator();

    //返回本回合先手玩家
    Player* judge_skill_speed(GlobalEnv &ge, Player &p1, Player &p2);
    //考虑天气、环境对于先手度的影响
    void check_we_effect_on_skill_speed(GlobalEnv &ge, int* skill_speed_1, int* skill_speed_2, Player &p1, Player &p2);
    //考虑天气、环境对宠物速度的影响
    void check_we_effect_on_pet_speed(GlobalEnv &ge, int* pet_speed_1, int* pet_speed_2, Player &p1, Player &p2);

    //综合天气环境、对面减伤情况等判断技能真实效果
    //天气的回血效果应当在技能最末触发
    //进入下一回合
    void go_to_next_round();
    //结算src->des本回合触发的单个技能，将技能效果发到消息队列后交给玩家双方结算
    void process_skill(GlobalEnv &ge, Player* src, Player* des, int src_skill_idx, vector<SkillEffect>& src_skill_effect);
    //处理一个玩家本回合所有的技能
    void process_player_action(GlobalEnv &ge, Player* fst_player, Player* snd_player, int fst_skill_idx, vector<SkillEffect>& src_skill_effect);
    
    void run(GlobalEnv &ge, Player &p1, Player &p2, int p1_skill_idx, int p2_skill_idx);


    int round;//当前回合数
    vector<SkillEffect> fst_skill_effect;//玩家1本回合的技能效果队列
    vector<SkillEffect> snd_skill_effect;//玩家2本回合的技能效果队列
    vector<SkillEffect> we_effect;//天气、环境造成的效果队列
    int p1_pet_idx;//玩家1正在出于对局的宠物下标
    int p2_pet_idx;//玩家2正在出于对局的宠物下标
    int p1_skill_speed;//玩家1当前技能先手度
    int p2_skill_speed;//玩家2当前技能先手度

};

#endif