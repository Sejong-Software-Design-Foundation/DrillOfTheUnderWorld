#include "LuckStone.hpp"
#include "common.hpp"

LuckStone::LuckStone() : Item() {
    this->name = "행운의 돌";
    this->info = "아이템 구매 후 다음 상점 방문 시 구매값의 2배를 돌려준다.";
    this->rank = 'C';
    this->price = C_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpLuckStoneName, -1, -1, 1, 1 };
}

void LuckStone::use() {
    pc.setLuckStoneStage(stageLevel);
    pc.setHasLuckStone(true);
}