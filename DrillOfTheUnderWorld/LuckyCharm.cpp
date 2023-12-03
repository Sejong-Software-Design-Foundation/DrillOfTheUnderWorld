#include "LuckyCharm.hpp"
#include "common.hpp"

LuckyCharm::LuckyCharm() : Item() {
    this->name = "행운 부적";
    this->info = "죽음의 이르는 공격을 1회 방어한다.";
    this->rank = 'A';
    this->price = A_RANK_PRICE;
    this->isUniqueHoldableItem = true;
    imageArray[imageLayer.imageCount++] = { bmpLuckyCharmName, -1, -1, 1, 1 };
}

void LuckyCharm::use() {
    pc.setHasLuckCharm(true);
}