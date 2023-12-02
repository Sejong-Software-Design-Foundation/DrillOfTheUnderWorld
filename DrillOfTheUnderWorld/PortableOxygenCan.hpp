#include "Item.hpp"

class PortableOxygenCan : public Item {
public:
    PortableOxygenCan();
    void use() override;
};

PortableOxygenCan::PortableOxygenCan() : Item() {
    this->name = "�޴�� ���ĵ";
    this->info = "PC�� ��Ұ������� ��� ȸ���Ѵ�.";
    this->rank = 'E';
    this->price = E_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpPortableOxygenCanName, -1,-1, 1 };
}

void PortableOxygenCan::use() {
    pc.setOxygen(pc.getMaxOxygen());
}