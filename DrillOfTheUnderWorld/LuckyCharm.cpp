#include "LuckyCharm.hpp"
#include "common.hpp"

LuckyCharm::LuckyCharm() : Item() {
    this->name = "��� ����";
    this->info = "������ �̸��� ������ 1ȸ ����Ѵ�.";
    this->rank = 'A';
    this->price = A_RANK_PRICE;
    this->isUniqueHoldableItem = true;
    imageArray[imageLayer.imageCount++] = { bmpLuckyCharmName, -1, -1, 1, 1 };
}

void LuckyCharm::use() {
    pc.setHasLuckCharm(true);
}