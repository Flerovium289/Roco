#include "SkillEffect.h"
SkillEffect::SkillEffect():object(0),is_apply(false){
    HP_change = 0;
    for(int i = 0; i < 4; i++){
        PP_change[i] = 0;
    }
    control_abnormal_change = ControlAbnormal::none;
    hurt_abnormal_change = HurtAbnormal::none;
    other_abnormal_change = OtherAbnormal::none;
    we_change = -1;
    we_round_new = 0;
    we_round_change = 0;
}