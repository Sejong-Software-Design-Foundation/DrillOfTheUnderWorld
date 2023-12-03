#include "Item.hpp"

class SupplyOxygenTank : public Item {
public:
    SupplyOxygenTank();
    void use() override;
};

SupplyOxygenTank::SupplyOxygenTank() : Item() {
    this->name = "������ �����";
    this->info = "PC�� �ִ� ��� �������� 10% �����Ѵ�.";
    this->rank = 'C';
    this->price = C_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpSupplyOxygenTankName, -1,-1, 1 };
}

void SupplyOxygenTank::use() {
    pc.setMaxOxygen(pc.getMaxOxygen() * 1.1);
}