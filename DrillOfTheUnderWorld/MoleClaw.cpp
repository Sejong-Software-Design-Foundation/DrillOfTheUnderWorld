#include "MoleClaw.hpp"
#include "common.hpp"

MoleClaw::MoleClaw() : Item() {
    this->name = "�δ��� ����";
    this->info = "���� �ı��� ��ȭ ȹ�淮�� �����Ѵ�.";
    this->rank = 'B';
    this->price = B_RANK_PRICE;
    this->isUniqueHoldableItem = true;
    imageArray[imageLayer.imageCount++] = { bmpMoleClawName, -1, -1, 1, 1 };
}

void MoleClaw::use() {
    pc.setHasMoleClaw(true);
}