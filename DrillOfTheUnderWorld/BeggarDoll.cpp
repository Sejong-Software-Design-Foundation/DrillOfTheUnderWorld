#include "BeggarDoll.hpp"
#include "common.hpp"

BeggarDoll::BeggarDoll() : Item() {
    this->name = "���� ����";
    this->info = "PC ���ݼӵ��� ����������, ���ݽø��� ���� �Ҹ�ȴ�.";
    this->rank = 'S';
    this->price = S_RANK_PRICE;
    this->isUniqueHoldableItem = true;
    imageArray[imageLayer.imageCount++] = { bmpBeggarDollName - 1, -1, 1, 1 };
}

void BeggarDoll::use() {
    pc.setHashasBeggarDoll(true);
}