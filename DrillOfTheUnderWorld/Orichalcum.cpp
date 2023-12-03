#include "Orichalcum.hpp"
#include "common.hpp"

Orichalcum::Orichalcum() : Item() {
    this->name = "오리할콘";
    this->info = "1000돌을 획득한다.";
    this->rank = 'S';
    this->price = 0; // 오리할콘만 0원
    this->isUniqueHoldableItem = true;
    imageArray[imageLayer.imageCount++] = { bmpOrichalcumName, -1, -1, 1, 1 };
}

void Orichalcum::use() {
    pc.setStone(pc.getStone() + 1000);
}