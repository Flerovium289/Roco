#ifndef _SkillEffect
#define _SkillEffect
#include "CombatInfo.h"

//技能的作用效果，由trigger函数发给judge裁判的消息队列，judge判定之后再转发给对方的消息队列
class SkillEffect{
public:
    SkillEffect();
    std::string skill_name;//本效果对应的技能名称
    int object;//作用对象序号，-6~-1为我方，1~6为敌方, 0为场上天气环境
    bool is_apply;//是否已经被处理
    int HP_change;//对作用方的hp改变
    int PP_change[4];//对作用方的pp改变
    StrengthenLevel strengthen_level_change;//对作用方强化等级的改变
    ControlAbnormal control_abnormal_change;//施加控制异常
    HurtAbnormal hurt_abnormal_change;//施加损血异常
    OtherAbnormal other_abnormal_change;//施加束缚等其他异常
    int we_change;//对天气环境的改变, -1表示没有作用
    int we_round_new;//改变的天气环境回合，如果we_change != -1，再考虑这一项
    int we_round_change;
    std::vector<std::pair<int, int>> int_marks_change;//对整型标记的改变，第一项为标记bitmap对应的idx，第二项为生效回合数
    std::vector<std::pair<int, FloatMark>> float_mark_change;//对非整型标记的改变，第一项为标记bitmap对应的idx，第二项为FloatMark对应参数
};
#endif