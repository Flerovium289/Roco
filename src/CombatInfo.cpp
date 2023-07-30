#include <iostream>
#include <cmath>
#include "CombatInfo.h"
#include "AbnormalState.cpp"

StrengthenLevel::StrengthenLevel():P_atk(0),M_atk(0),P_def(0),M_def(0),speed(0),hit(0),dodge(0){}
void StrengthenLevel::print_strengthen_level(){
    if(P_atk != 0){
        std::cout << "攻击强化：" << P_atk << std::endl;
    }
    if(M_atk != 0){
        std::cout << "魔攻强化: " << M_atk << std::endl;
    }
    if(P_def != 0){
        std::cout << "防御强化: " << P_def << std::endl;
    }
    if(M_def != 0){
        std::cout << "魔抗强化: " << M_def << std::endl;
    }
    if(speed != 0){
        std::cout << "速度强化: " << speed << std::endl;
    }
    if(hit != 0){
        std::cout << "命中强化: " << hit << std::endl;
    }
}
Marks::Marks(){
    //初始化Mark2Idx字典
    for(const auto& p : Idx2Mark) {
        Mark2Idx[p.second] = p.first;
    }
    //初始化FloatMark2Idx字典
    for(const auto& p : Idx2FloatMark){
        FloatMark2Idx[p.second] = p.first;
    }
    //初始化整型标记
    int_marks.resize(Idx2Mark.size());
    for(auto i: int_marks){
        i = 0;
    }
    //初始化浮点数标记
    float_marks.resize(Idx2FloatMark.size());
    for(auto i: float_marks){
        i.num = 1;
        i.round = 0;
    }
}

void Marks::print_marks(){
    std::cout << "战斗标记：" << std::endl;
    for(int idx = 0; idx < int_marks.size(); idx++){
        if(int_marks[idx] > 0){
            std::cout << Idx2Mark[idx] << ": " << int_marks[idx] << std::endl;
        }
    }
    for(int idx = 0; idx < float_marks.size(); idx++){
        if(float_marks[idx].round > 0){
            std::cout << Idx2FloatMark[idx] << ": " << float_marks[idx].num << " " << float_marks[idx].round << "回合" << std::endl;
        }
    }
}
