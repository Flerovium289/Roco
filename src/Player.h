#ifndef _PLAYER_H
#define _PLAYER_H
#include "CombatPet.h"
class Player{
public:
    Player();
    void add_pet();
    void send_skill_speed_to_admin(int skill_idx, int &p1_skill_speed);
    //处理queue_for_receive_skill中的技能效果
    void apply_skill_effect(SkillEffect& tmp_skill_effect, int object_idx);
    //处理本回合天气/环境对hp和pp的效果
    void apply_ge_effect();
    //处理异常效果
    void apply_abnormal_effect();
    //当前宠物是否存活
    bool is_alive();
    //当前宠物本回合是否可以行动
    bool can_act();
    //使用编号为idx的技能，4~9为换宠
    //具体步骤：调用pets[temp_pet_idx]的use_skill函数，得到具体的技能效果信息，并用send_skill_speed_to_admin将其传给管理员
    void use_skill(int idx, Player* src_player, Player* des_player, std::vector<SkillEffect>& skill_effect, bool use_rand);
    //检查对手技能效果
    void check_rv_skill_effect(SkillEffect &rv_skill_effect);

    int temp_pet_idx;//当前宠物在pets中的索引
    int pet_num;//pets数目
    CombatPet pets[6];
};
#endif