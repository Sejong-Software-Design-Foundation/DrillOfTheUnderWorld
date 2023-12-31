#include "BatFang.hpp"
#include "common.hpp"

BatFang::BatFang() : Item() {
    this->name = "박쥐 송곳니";
    this->info = "보스 공격시 낮은 확률로 HP를 일정량 회복한다.";
    this->rank = 'B';
    this->price = B_RANK_PRICE;
    this->isUniqueHoldableItem = true;
    imageArray[imageLayer.imageCount++] = { bmpBatFangName, -1, -1, 1, 1 };
}

void BatFang::use() {
    pc.setHasBatFang(true);
}