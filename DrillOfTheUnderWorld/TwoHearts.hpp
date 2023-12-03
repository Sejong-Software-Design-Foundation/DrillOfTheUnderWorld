#include "Item.hpp"

class TwoHearts : public Item {
public:
    TwoHearts();
    void use() override;
};

TwoHearts::TwoHearts() : Item() {
    this->name = "�� ���� ����";
    this->info = "��� ������ ���ҷ��� �����Ѵ�.";
    this->rank = 'A';
    this->price = A_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpTwoHeartsName, -1,-1, 1 };
}

void TwoHearts::use() {
    pc.setHasTwoHearts(true);
}