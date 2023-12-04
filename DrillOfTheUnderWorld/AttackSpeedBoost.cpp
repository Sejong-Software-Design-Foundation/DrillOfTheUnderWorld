#include "AttackSpeedBoost.hpp"
#include "common.hpp"

AttackSpeedBoost::AttackSpeedBoost() : Item() {
    this->name = "���ݼӵ� ����";
    this->info = "���ݼӵ� ������ 1 ������Ų��.";
    this->rank = 'N';
    this->price = N_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpAttackSpeedBoostName, -1, -1, 1, 1 };
}

void AttackSpeedBoost::use() {
    pc.setAtkSpdLev(pc.getAtkSpdLev() + 1);
}