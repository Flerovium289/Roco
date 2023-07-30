#include <iostream>
#include <random>
#include "Administrator.h"
#define USE_RAND 0
Administrator::Administrator():round(0),p1_pet_idx(0),p2_pet_idx(0),p1_skill_speed(8),p2_skill_speed(8){}
/*
judge_skill_speed：判断本回合p1、p2谁先手，返回先手的玩家

Args：
ge：天气环境
p1：玩家1
p2：玩家2
*/
Player* Administrator::judge_skill_speed(GlobalEnv &ge, Player &p1, Player &p2){
    //考虑天气环境对出招先手度的影响（迷雾，说的就是你）
    check_we_effect_on_skill_speed(ge, &p1_skill_speed, &p2_skill_speed, p1, p2);
    if(p1_skill_speed > p2_skill_speed) return &p1;
    if(p1_skill_speed < p2_skill_speed) return &p2;
    //技能先手度相同，判断速度
    int p1_pet_speed = p1.pets[p1.temp_pet_idx].get_speed();
    int p2_pet_speed = p2.pets[p2.temp_pet_idx].get_speed();
    //考虑天气环境对出招速度的影响（疾风、铁壁啥的）
    check_we_effect_on_pet_speed(ge, &p1_pet_speed, &p2_pet_speed, p1, p2);
    if(p1_pet_speed > p2_pet_speed) return &p1;
    if(p1_pet_speed < p2_pet_speed) return &p2;
    //技能先手度、速度都相同，随机选择p1、p2出招
    if(rand() % 2){
        return &p1;
    }
    else{
        return &p2;
    }
}
/*
check_we_effect_on_skill_speed：处理天气/环境对出招先手度的影响，并据此修改相应技能的先手度

Args:
ge：天气环境
skill_speed_1：玩家1的技能先手度
skill_speed_2：玩家2的技能先手度
p1：玩家1
p2：玩家2
*/
void Administrator::check_we_effect_on_skill_speed(GlobalEnv &ge, int* skill_speed_1, int* skill_speed_2, Player &p1, Player &p2){

}
/*
check_we_effect_on_pet_speed：处理天气/环境对宠物速度的影响，并据此修改相应宠物的速度

Args:
ge：天气环境
pet_speed_1：宠物1的速度
pet_speed_2：宠物2的速度
p1：玩家1
p2：玩家2
*/
void Administrator::check_we_effect_on_pet_speed(GlobalEnv &ge, int* pet_speed_1, int* pet_speed_2, Player &p1, Player &p2){

}
/*
process_skill：结算src->des本回合触发的单个技能，将技能效果发到消息队列后交给玩家双方结算
src_player把技能效果封装成多个skill_effect包传给Admin的src_skill_effect队列，des_player根据自身状态检查并修改队列内容；
Admin根据src_skill_effect队列中的作用对象，把技能效果分发给双方进行处理

Args:
ge：天气环境
src_player：技能主动方
des_player：技能被动方
src_skill_idx：主动方使用的技能序号
src_skill_effect：主动方技能效果储存队列
*/
void Administrator::process_skill(GlobalEnv &ge, Player* src_player, Player* des_player, int src_skill_idx, vector<SkillEffect>& src_skill_effect){
    //使用本回合技能，把技能效果封装成多个skill_effect包传给Admin的skill_effect_1队列
    src_player->use_skill(src_skill_idx, src_player, des_player, src_skill_effect, USE_RAND);
    
    Attr src_pet_attr = src_player->pets[src_player->temp_pet_idx].pet_basic_info.attr;
    Attr des_pet_attr = des_player->pets[des_player->temp_pet_idx].pet_basic_info.attr;
    Attr src_skill_attr = src_player->pets[src_player->temp_pet_idx].skills[src_skill_idx].attr;
    
    for(auto item: fst_skill_effect){
        des_player->check_rv_skill_effect(item);//对手检查技能效果
        if(item.object == des_player->temp_pet_idx){//天气只对在场宠物有影响，对波及伤害无影响
            ge.check_skill_effect(item, src_pet_attr, des_pet_attr, src_skill_attr);
        }
        if(item.object > 0){//作用于对面
            des_player->apply_skill_effect(item, item.object - 1);//序号转化成索引0~5
        }
        else if(item.object < 0){//作用于自身
            src_player->apply_skill_effect(item, abs(item.object) - 1);
        }
        else{//作用于天气环境
            ge.apply_skill_effect(item);
        }
    }

}
/*
process_player_action: 结算一个玩家本回合所有的技能效果
先结算本回合使用技能，后结算天气，再按从左到右的顺序结算其余多段技能，最后结算异常效果（血脉效果？）

Args:
ge：天气环境
src_player：技能主动方
des_player：技能被动方
src_skill_idx：主动方使用的技能序号
src_skill_effect：主动方技能效果储存队列
*/
void Administrator::process_player_action(GlobalEnv &ge, Player* src_player, Player* des_player, int src_skill_idx, vector<SkillEffect>& src_skill_effect){
    if(src_player->can_act()){
        process_skill(ge, src_player, des_player, src_skill_idx, src_skill_effect);//结算本回合技能
    }
    
    //ge.send_effect_to_admin();
    //结算其余多段技能
    for(int i = 0; i < MAX_SKILL_NUM; i++){
        //若对面宠物已经阵亡，本技能无需进行结算
        if(des_player->pets[des_player->temp_pet_idx].get_HP() == 0){
            break;
        }
        //本回合刚使用的技能不触发
        if(i == src_skill_idx){
            continue;
        }
        //非多段技能，跳过
        if(src_player->pets[src_player->temp_pet_idx].skills[i].stage == 0){
            continue;
        }
        //多段技能的其余段数可能需要另外开一个函数进行结算
        process_skill(ge, src_player, des_player, i, src_skill_effect);
    }

    //受击方结算异常效果
    des_player->apply_abnormal_effect();
    //攻击方结算天气效果
    src_player->apply_ge_effect();//结算天气效果

}
/*
run：单个回合的对战逻辑
1. player1、player2选择本回合出招
2. Admin判定player1、player2出招先后（考虑天气），从而判定先处理谁的skill_effect队列（假设先处理player1的）
    3. player1使用本回合技能，把技能效果封装成多个skill_effect包传给Admin的skill_effect_1队列
    4. skill_effect_1队首元素出队，admin调用player2的特殊效果标记，直接根据这个结果进行修改，看看有没有需要修改的信息（免伤，反弹啥的）
        4.1 player2没有需要修改的地方
        4.2 player2修改作用于自身的效果（e.g.免伤）：直接修改对应的skill_effect对象
        4.3 player2修改作用于player1的效果（e.g.反弹、毒奶）：直接修改/原位添加对应的skill_effect对象
    5. 应用队首技能效果

    6. player1处理场上天气环境对HP、PP造成的效果，如果有新增的skill_effect，添加在队列末尾
        6.1 双方处理天气环境对HP、PP的效果
    7. player1使用其他分段触发的技能，流程同3 (若player2已经阵亡，则player1不再触发下一个招数)
    8. 判定异常效果对player2的作用
    9. 在player2出招前，先判断player2是否还能够出招；如果不能（阵亡，被控制），直接跳过player2的出招回合；否则重复3…~7循环
10. Admin进入下一回合，清空skill_effect队列，令天气、player1、player2修改自身与回合相关的信息
Args：
ge：天气环境
p1：玩家1
p2：玩家2
p1_skill_idx：玩家1本回合出招序号，[0, 3]为技能，[4, 9]为换宠
p2_skill_idx：玩家2本回合出招序号，[0, 3]为技能，[4, 9]为换宠
*/
void Administrator::run(GlobalEnv &ge, Player &p1, Player &p2, int p1_skill_idx, int p2_skill_idx){
    p1.send_skill_speed_to_admin(p1_skill_idx, p1_skill_speed);
    p2.send_skill_speed_to_admin(p2_skill_idx, p2_skill_speed);
    Player* fst_player = judge_skill_speed(ge, p1, p2);
    Player* snd_player = (fst_player == &p1)? &p2: &p1;
    int fst_skill_idx = (fst_player == &p1)? p1_skill_idx: p2_skill_idx;
    int snd_skill_idx = (fst_skill_idx == p1_skill_idx)? p2_skill_idx: p1_skill_idx;
    process_player_action(ge, fst_player, snd_player, fst_skill_idx, fst_skill_effect);
    //似乎不大对
    if(p2.is_alive()){
        process_player_action(ge, snd_player, fst_player, snd_skill_idx, snd_skill_effect);
    }

    //Admin进入下一回合，清空skill_effect队列，令天气、player1、player2修改自身与回合相关的信息
    go_to_next_round();
}
void Administrator::go_to_next_round(){
    fst_skill_effect.clear();
    snd_skill_effect.clear();
    we_effect.clear();

    round++;
}