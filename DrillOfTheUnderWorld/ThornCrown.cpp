#include "ThronCrown.hpp"
#include "common.hpp"

ThornCrown::ThornCrown() : Item() {
    this->name = "가시 면류관";
    this->info = "PC 공격력이 증가하지만, 2배의 피해를 입게 된다.";
    this->rank = 'S';
    this->price = S_RANK_PRICE;
    this->isUniqueHoldableItem = true;
    imageArray[imageLayer.imageCount++] = { bmpThornCrownName, -1, -1, 1, 1 };
}

void ThornCrown::use() {
    pc.setHasThronCrown(true);
}