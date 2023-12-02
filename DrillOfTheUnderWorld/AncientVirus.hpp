#include "Item.hpp"

class AncientVirus : public Item {
public:
    AncientVirus();
    void use() override;
};

AncientVirus::AncientVirus() : Item() {
    this->name = "��� ���̷���";
    this->info = "PC�� �ִ� ü���� 10% �����Ѵ�.";
    this->rank = 'F';
    this->price = F_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpAncientVirusName, -1,-1, 1 };
}

void AncientVirus::use() {
    pc.setMaxHP(pc.getMaxHP() * 0.9);
}