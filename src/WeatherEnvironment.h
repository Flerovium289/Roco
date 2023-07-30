#ifndef _WEATHER_ENVIRONMENT_H
#define _WEATHER_ENVIRONMENT_H
#include "SkillEffect.h"
enum Weather{empty, locked, rainy, foggy, windy, thunderstorm};//还需添加
enum Enviornment{empty, mirage};//还需添加
struct WeatherEnviron
{
    Weather w;
    Enviornment e;
};
//天气/环境
class GlobalEnv{
public:
    GlobalEnv():we_round(0){we.w = (Weather::empty);};
    //根据WorE和回合数round更改全场天气环境，若更改天气环境成功，return true，否则return false
    bool set_we(WeatherEnviron WorE, int round);
    //根据场上的天气环境检查skill_effect，并对skill_effect进行修改
    virtual void check_skill_effect(SkillEffect &skill_effect, Attr src_pet_attr, Attr des_pet_attr, Attr src_skill_attr);
    //将技能效果tmp_skill_effect应用于apply_skill_effect
    void apply_skill_effect(SkillEffect tmp_skill_effect);
    
    WeatherEnviron we;//当前天气环境
    int we_round; //场上天气/环境持续回合数   
};
#endif