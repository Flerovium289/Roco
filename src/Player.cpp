#include "Player.h"
Player::Player(){

}
//存入宠物信息（参数待定）
void Player::add_pet(){

};
//向Administrator发送出招速度
void Player::send_skill_speed_to_admin(int skill_idx, int &p1_skill_speed){
    p1_skill_speed = pets[temp_pet_idx].skills[skill_idx].speed;
};
//应用queue_for_receive_skill中的技能效果
void Player::apply_skill_effect(SkillEffect& tmp_skill_effect, int object_idx){
    CombatPet* temp_operating_pet = &pets[object_idx];//被作用方宠物
    temp_operating_pet->pet_temp_info.HP += tmp_skill_effect.HP_change;//技能对HP的变化
    for(int i = 0; i < 4; i++){//技能对PP的变化
        temp_operating_pet->skills[i].temp_pp += tmp_skill_effect.PP_change[i];
    }
    //处理技能强化的改变
    temp_operating_pet->strengthen_level.P_atk += tmp_skill_effect.strengthen_level_change.P_atk;
    temp_operating_pet->strengthen_level.P_def += tmp_skill_effect.strengthen_level_change.P_def;
    temp_operating_pet->strengthen_level.M_atk += tmp_skill_effect.strengthen_level_change.M_atk;
    temp_operating_pet->strengthen_level.M_def += tmp_skill_effect.strengthen_level_change.M_def;
    temp_operating_pet->strengthen_level.speed += tmp_skill_effect.strengthen_level_change.speed;
    temp_operating_pet->strengthen_level.hit += tmp_skill_effect.strengthen_level_change.hit;
    temp_operating_pet->strengthen_level.dodge += tmp_skill_effect.strengthen_level_change.dodge;

    //处理技能附加的异常状态
    temp_operating_pet->abnormal_state.set_control_abnormal(tmp_skill_effect.control_abnormal_change);
    temp_operating_pet->abnormal_state.set_hurt_abnormal(tmp_skill_effect.hurt_abnormal_change);
    temp_operating_pet->abnormal_state.set_other_abnormal(tmp_skill_effect.other_abnormal_change);

    //处理对标记的改变
    for(auto item: tmp_skill_effect.int_marks_change){
        temp_operating_pet->marks.int_marks[item.first] = item.second;
    }
    for(auto item: tmp_skill_effect.float_mark_change){
        temp_operating_pet->marks.float_marks[item.first] = item.second;
    }
};
//处理本回合天气/环境对hp和pp的效果
void Player::apply_ge_effect(){

};
//处理异常效果
void Player::apply_abnormal_effect(){

};
//当前宠物是否存活
bool Player::is_alive(){

};
//当前宠物是否可以行动
bool Player::can_act(){
    
};
//使用编号为idx的技能，4~9为换宠
//具体步骤：调用pets[temp_pet_idx]的trigger函数，得到具体的技能效果信息，并用send_skill_speed_to_admin将其传给管理员
void Player::use_skill(int idx, Player* src_player, Player* des_player, std::vector<SkillEffect>& skill_effect, bool use_rand){
    src_player->pets[temp_pet_idx].skills[idx].trigger(src_player, des_player, skill_effect, use_rand);
}
void Player::check_rv_skill_effect(SkillEffect &rv_skill_effect){

}