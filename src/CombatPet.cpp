#include "CombatPet.h"
CombatPet::CombatPet(){}
void CombatPet::set_combat_info(PetBasicInfo& pbi, SixDim& pti, AbnormalState& as, StrengthenLevel &sl, Marks &mk){
    pet_basic_info = pbi;
    pet_temp_info = pti;
    abnormal_state = as;
    strengthen_level = sl;
    marks = mk;
}
