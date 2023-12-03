#include "TwoHearts.hpp"
#include "common.hpp"

TwoHearts::TwoHearts() : Item() {
    this->name = "�� ���� ����";
    this->info = "��� ������ ���ҷ��� �����Ѵ�.";
    this->rank = 'A';
    this->price = A_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpTwoHeartsName, -1, -1, 1, 1 };
}

void TwoHearts::use() {
    pc.setHasTwoHearts(true);
}