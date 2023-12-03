#include "Item.hpp"

class AttackSpeedBoost : public Item {
public:
    AttackSpeedBoost();
    void use() override;
};

AttackSpeedBoost::AttackSpeedBoost() : Item() {
    this->name = "���ݼӵ� ���� �ν�Ʈ";
    this->info = "���ݼӵ� ������ 1 ������Ų��.";
    this->rank = 'N';
    this->price = N_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpAttackSpeedBoostName, -1,-1, 1 };
}

void AttackSpeedBoost::use() {
    pc.setAtkSpdLev(pc.getAtkSpdLev() + 1);
}