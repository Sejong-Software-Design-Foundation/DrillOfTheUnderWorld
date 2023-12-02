#include "Item.hpp"

class ThornCrown : public Item {
public:
    ThornCrown();
    void use() override;
};

ThornCrown::ThornCrown() : Item() {
    this->name = "���� �����";
    this->info = "PC ���ݷ��� ����������, 2���� ���ظ� �԰� �ȴ�.";
    this->rank = 'S';
    this->price = S_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpThornCrownName, -1,-1, 1 };
}

void ThornCrown::use() {
    pc.setHasThronCrown(true);
}