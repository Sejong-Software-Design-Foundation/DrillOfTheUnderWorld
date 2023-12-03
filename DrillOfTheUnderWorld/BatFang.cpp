#include "BatFang.hpp"
#include "common.hpp"

BatFang::BatFang() : Item() {
    this->name = "���� �۰���";
    this->info = "���� ���ݽ� ���� Ȯ���� HP�� ������ ȸ���Ѵ�.";
    this->rank = 'B';
    this->price = B_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpBatFangName, -1,-1, 1 };
}

void BatFang::use() {
    pc.setHasBatFang(true);
}