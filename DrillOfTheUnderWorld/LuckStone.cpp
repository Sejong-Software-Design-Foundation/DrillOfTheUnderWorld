#include "LuckStone.hpp"
#include "common.hpp"

LuckStone::LuckStone() : Item() {
    this->name = "����� ��";
    this->info = "������ ���� �� ���� ���� �湮 �� ���Ű��� 2�踦 �����ش�.";
    this->rank = 'C';
    this->price = C_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpLuckStoneName, -1, -1, 1, 1 };
}

void LuckStone::use() {
    pc.setLuckStoneStage(stageLevel);
    pc.setHasLuckStone(true);
}