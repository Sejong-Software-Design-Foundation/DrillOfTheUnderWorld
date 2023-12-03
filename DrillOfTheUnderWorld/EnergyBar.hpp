#include "Item.hpp"

class EnergyBar : public Item {
public:
    EnergyBar();
    void use() override;
};

EnergyBar::EnergyBar() : Item() {
    this->name = "��������";
    this->info = "PC�� ü���� ��� ȸ���Ѵ�.";
    this->rank = 'E';
    this->price = E_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpEnergyBarName, -1,-1, 1 };
}

void EnergyBar::use() {
    pc.setHP(pc.getMaxHP());
}