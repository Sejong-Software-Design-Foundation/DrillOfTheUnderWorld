#include "BeggarDoll.hpp"
#include "common.hpp"

BeggarDoll::BeggarDoll() : Item() {
    this->name = "거지 인형";
    this->info = "PC 공격속도가 증가하지만, 공격시마다 돌이 소모된다.";
    this->rank = 'S';
    this->price = S_RANK_PRICE;
    this->isUniqueHoldableItem = true;
    imageArray[imageLayer.imageCount++] = { bmpBeggarDollName - 1, -1, 1, 1 };
}

void BeggarDoll::use() {
    pc.setHashasBeggarDoll(true);
}