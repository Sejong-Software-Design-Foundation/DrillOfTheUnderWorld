#include "EnergyBar.hpp"
#include "common.hpp"

EnergyBar::EnergyBar() : Item() {
    this->name = "에너지바";
    this->info = "PC의 체력을 모두 회복한다.";
    this->rank = 'E';
    this->price = E_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpEnergyBarName, -1, -1, 1, 1 };
}

void EnergyBar::use() {
    pc.setHP(pc.getMaxHP());
}