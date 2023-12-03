#include "AttackBoost.hpp"
#include "common.hpp"


AttackBoost::AttackBoost() : Item() {
    this->name = "공격력 증가 부스트";
    this->info = "공격력 레벨을 1 증가시킨다.";
    this->rank = 'N';
    this->price = N_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpAttackBoostName, -1,-1, 1 };
}

void AttackBoost::use() {
    pc.setAtkLev(pc.getAtkLev() + 1);
}