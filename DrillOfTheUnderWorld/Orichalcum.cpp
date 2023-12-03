#include "Orichalcum.hpp"
#include "common.hpp"

Orichalcum::Orichalcum() : Item() {
    this->name = "��������";
    this->info = "1000���� ȹ���Ѵ�.";
    this->rank = 'S';
    this->price = 0; // �������ܸ� 0��
    this->isUniqueHoldableItem = true;
    imageArray[imageLayer.imageCount++] = { bmpOrichalcumName, -1, -1, 1, 1 };
}

void Orichalcum::use() {
    pc.setStone(pc.getStone() + 1000);
}