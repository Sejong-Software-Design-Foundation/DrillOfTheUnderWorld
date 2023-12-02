#include "Item.hpp"

class AttackBoost : public Item {
public:
    AttackBoost();
    void use() override;
};

AttackBoost::AttackBoost() : Item() {
    this->name = "���ݷ� ���� �ν�Ʈ";
    this->info = "���ݷ� ������ 1 ������Ų��.";
    this->rank = 'N';
    this->price = N_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpAttackBoostName, -1,-1, 1 };
}

void AttackBoost::use() {
    pc.setAtkLev(pc.getAtkLev() + 1);
}