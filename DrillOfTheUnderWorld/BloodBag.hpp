#include "Item.hpp"

class BloodBag : public Item {
public:
    BloodBag();
    void use() override;
};

BloodBag::BloodBag() : Item() {
    this->name = "���� ��";
    this->info = "PC�� �ִ� ü���� 10% �����Ѵ�.";
    this->rank = 'C';
    this->price = C_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpBloodBagName, -1,-1, 1 };
}

void BloodBag::use() {
    pc.setMaxHP(pc.getMaxHP() * 1.1);
}