#include "Item.hpp"

class AttackSpeedBoost : public Item {
public:
    AttackSpeedBoost();
    void use() override;
};

AttackSpeedBoost::AttackSpeedBoost() : Item() {
    this->name = "공격속도 증가 부스트";
    this->info = "공격속도 레벨을 1 증가시킨다.";
    this->rank = 'N';
    this->price = N_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpAttackSpeedBoostName, -1,-1, 1 };
}

void AttackSpeedBoost::use() {
    pc.setAtkSpdLev(pc.getAtkSpdLev() + 1);
}