#include "Item.hpp"

class BloodBag : public Item {
public:
    BloodBag();
    void use() override;
};

BloodBag::BloodBag() : Item() {
    this->name = "블러드 백";
    this->info = "PC의 최대 체력이 10% 증가한다.";
    this->rank = 'C';
    this->price = C_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpBloodBagName, -1,-1, 1 };
}

void BloodBag::use() {
    pc.setMaxHP(pc.getMaxHP() * 1.1);
}