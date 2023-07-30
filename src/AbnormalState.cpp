
#include <iostream>
#include <math.h>
#include "AbnormalState.h"
AbnormalState::AbnormalState():control_abnormal((ControlAbnormal)none),hurt_abnormal((HurtAbnormal)none),other_abnormal((OtherAbnormal)none),
control_abnormal_round(0), hurt_abnormal_round(0), other_abnormal_round(0){
    for(int i = 0; i < CONTROL_ABNORMAL_NUM; i++){
        immune_control_abnormal[i] = 0;
    }
    for(int i = 0; i < HURT_ABNORMAL_NUM; i++){
        immune_hurt_abnormal[i] = 0;
    }
    for(int i = 0; i < OTHER_ABNORMAL_NUM; i++){
        immune_other_abnormal[i] = 0;
    }
}
void AbnormalState::set_immune_control_abnormal(int round){
    control_abnormal = (ControlAbnormal)immune;
    control_abnormal_round = round;
    for(int i = 0; i < CONTROL_ABNORMAL_NUM; i++){
        immune_control_abnormal[i] = round;
    }
}
void AbnormalState::set_immune_hurt_abnormal(int round){
    hurt_abnormal = (HurtAbnormal)immune;
    hurt_abnormal_round = round;
    for(int i = 0; i < HURT_ABNORMAL_NUM; i++){
        immune_hurt_abnormal[i] = round;
    }
}
void AbnormalState::set_immune_other_abnormal(int round){
    other_abnormal = (OtherAbnormal)immune;
    for(int i = 0; i < OTHER_ABNORMAL_NUM; i++){
        immune_other_abnormal[i] = round;
    }
}
void AbnormalState::set_control_abnormal(ControlAbnormal control_abnormal_change){
    if(control_abnormal_change != ControlAbnormal::none){//技能具有控制效果
        //不免疫当前控制效果
        if(!immune_control_abnormal[control_abnormal_change]){
            control_abnormal = control_abnormal_change;
        }
        control_abnormal_round = 1;//生效了一回合
    }
}
void AbnormalState::set_hurt_abnormal(HurtAbnormal hurt_abnormal_change){
    if(hurt_abnormal_change != HurtAbnormal::none){
        if(!immune_hurt_abnormal[hurt_abnormal_change]){
            hurt_abnormal = hurt_abnormal_change;
        }
        hurt_abnormal_round = 1;
    }
}
void AbnormalState::set_other_abnormal(OtherAbnormal other_abnormal_change){
    if(other_abnormal_change != OtherAbnormal::none){
        if(!immune_other_abnormal[other_abnormal_change]){
            other_abnormal = other_abnormal_change;
        }
        other_abnormal_round = 1;
    }
}


std::map<int, std::string>* get_dict_type(std::string immune_type){
    std::map<int, std::string>* dict = nullptr;
    if(immune_type == CONTROL_ABNORMAL_STR){
        return &ControlAbnormalMap;
    }
    if(immune_type == HURT_ABNORMAL_STR){
        return &HurtAbnormalMap;
    }
    if(immune_type == OTHER_ABNORMAL_STR){
        return &OtherAbnormalMap;
    }
    std::cout << "get_dict_type error: dict not found!" << std::endl;
    std::cout << "immune_type: " << immune_type << std::endl;
    return nullptr;
}
void AbnormalState::print_item_immune(int immune_arr[], int len, std::string immune_type){
    int min_immune_round = INF;
    for(int i = 0; i < len; i++){
        min_immune_round = std::min(min_immune_round, immune_arr[i]);
    }
    if(min_immune_round){
        std::cout << "免疫" << immune_type << min_immune_round << "回合" << std::endl;
    }
    else{
        std::cout << immune_type << ":" << std::endl;
        std::map<int, std::string> dict = *get_dict_type(immune_type);
        for(int i = 0; i < len; i++){
            if(immune_arr[i]){
                std::cout << "免疫" << dict[i] << immune_arr[i] << "回合" << std::endl;
            }
        }
    }
}
void AbnormalState::print_immune(){
    int min_immune_round = INF;
    for(int i = 0; i < CONTROL_ABNORMAL_NUM; i++){
        min_immune_round = std::min(min_immune_round, immune_control_abnormal[i]);
    }
    for(int i = 0; i < HURT_ABNORMAL_NUM; i++){
        min_immune_round = std::min(min_immune_round, immune_hurt_abnormal[i]);
    }
    for(int i = 0; i < OTHER_ABNORMAL_NUM; i++){
        min_immune_round = std::min(min_immune_round, immune_other_abnormal[i]);
    }
    if(min_immune_round){
        std::cout << "免疫异常" << min_immune_round << "回合" << std::endl;
    }
    else {
        print_item_immune(immune_control_abnormal, CONTROL_ABNORMAL_NUM, CONTROL_ABNORMAL_STR);
        print_item_immune(immune_hurt_abnormal, HURT_ABNORMAL_NUM, HURT_ABNORMAL_STR);
        print_item_immune(immune_other_abnormal, OTHER_ABNORMAL_NUM, OTHER_ABNORMAL_STR);
    }
}
