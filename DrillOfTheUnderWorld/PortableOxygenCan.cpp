#include "PortableOxygenCan.hpp"
#include "common.hpp"

PortableOxygenCan::PortableOxygenCan() : Item() {
    this->name = "�޴�� ���ĵ";
    this->info = "PC�� ��Ұ������� ��� ȸ���Ѵ�.";
    this->rank = 'E';
    this->price = E_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpPortableOxygenCanName, -1, -1, 1, 1 };
}

void PortableOxygenCan::use() {
    pc.setOxygen(pc.getMaxOxygen());
}