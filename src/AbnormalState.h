#ifndef _ABNORMAL_STATE_H_
#define _ABNORMAL_STATE_H_
#include <map>
#include <string>
#define CONTROL_ABNORMAL_NUM 7
#define HURT_ABNORMAL_NUM 4
#define OTHER_ABNORMAL_NUM 1
#define INF INT32_MAX
#define CONTROL_ABNORMAL_STR "控制异常"
#define HURT_ABNORMAL_STR "损血异常"
#define OTHER_ABNORMAL_STR "其他异常"


//异常状态
enum ControlAbnormal{terror, frozen, confusion, sleep, baffle, anesthesia, burn, none, immune};
enum HurtAbnormal{parasitic, curse, poison, ac_poison, none, immune};
enum OtherAbnormal{bound, none, immune};
std::map<int, std::string> ControlAbnormalMap = {
{(ControlAbnormal)terror,"恐惧"},{(ControlAbnormal)frozen,"冰冻"},{(ControlAbnormal)confusion,"混乱"}, {(ControlAbnormal)sleep, "睡眠"},
{(ControlAbnormal)baffle,"迷惑"},{(ControlAbnormal)anesthesia,"麻醉"},{(ControlAbnormal)burn, "烧伤"},
{(ControlAbnormal)none, "无"},{((ControlAbnormal)immune), "免疫控制异常"}
};
std::map<int, std::string> HurtAbnormalMap = {
{(HurtAbnormal)parasitic,"寄生"},{(HurtAbnormal)curse, "诅咒"},{(HurtAbnormal)poison, "中毒"}, 
{((HurtAbnormal)ac_poison), "剧毒"}, {(HurtAbnormal)none, "无"}, {(HurtAbnormal)immune, "免疫损血异常"}
};
std::map<int, std::string> OtherAbnormalMap = {
{(OtherAbnormal)bound, "束缚"},{(OtherAbnormal)none, "无"}, {(OtherAbnormal)immune, "免疫其他异常"}
};
//异常状态对应的函数指针数组，调用函数指针来实现异常状态的效果
bool (*ControlAbnormalFunc[CONTROL_ABNORMAL_NUM])(int&);//控制类异常函数，传入回合数，返回本回合是否生效（参数需要再改改，比如混乱没法实现）
void (*HurtAbnormalFunc[HURT_ABNORMAL_NUM])(int &, int &, int &, int &);//损血类异常函数，传入src方和des方的最大HP、当前HP
int (*OtherAbnormalFunc[OTHER_ABNORMAL_NUM])(int &);//其他异常函数（束缚），传入当前出招速度，返回减半出招速度



//记录宠物的异常状态
class AbnormalState{
public:
    AbnormalState();
    void set_immune_control_abnormal(int round);
    void set_immune_hurt_abnormal(int round);
    void set_immune_other_abnormal(int round);

    void set_control_abnormal(ControlAbnormal control_abnormal_change);
    void set_hurt_abnormal(HurtAbnormal hurt_abnormal_change);
    void set_other_abnormal(OtherAbnormal other_abnormal_change);
    
    void print_item_immune(int immune_arr[], int len, std::string immune_type);//打印单项免疫情况
    void print_immune();
    
    ControlAbnormal control_abnormal;//当前控制异常
    HurtAbnormal hurt_abnormal;//当前损血异常
    OtherAbnormal other_abnormal;//当前其他异常
    int control_abnormal_round;//已生效回合数
    int hurt_abnormal_round;
    int other_abnormal_round;

    int immune_control_abnormal[CONTROL_ABNORMAL_NUM];
    int immune_hurt_abnormal[HURT_ABNORMAL_NUM];
    int immune_other_abnormal[OTHER_ABNORMAL_NUM];
};
#endif