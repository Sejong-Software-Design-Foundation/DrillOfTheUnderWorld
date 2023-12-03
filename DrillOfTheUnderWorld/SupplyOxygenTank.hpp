#include "Item.hpp"

class SupplyOxygenTank : public Item {
public:
    SupplyOxygenTank();
    void use() override;
};

SupplyOxygenTank::SupplyOxygenTank() : Item() {
    this->name = "보급형 산소통";
    this->info = "PC의 최대 산소 게이지가 10% 증가한다.";
    this->rank = 'C';
    this->price = C_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpSupplyOxygenTankName, -1,-1, 1 };
}

void SupplyOxygenTank::use() {
    pc.setMaxOxygen(pc.getMaxOxygen() * 1.1);
}