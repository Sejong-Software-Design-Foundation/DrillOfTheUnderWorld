#include "Item.hpp"

class CursedTotem : public Item {
public:
    CursedTotem();
    void use() override;
};

CursedTotem::CursedTotem() : Item() {
    this->name = "���ֹ��� ����";
    this->info = "���ݷ� ������ 1��ŭ �����Ѵ�.";
    this->rank = 'F';
    this->price = F_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpCursedTotemName, -1,-1, 1 };
}

void CursedTotem::use() {
    pc.setAtkLev(pc.getAtkLev() - 1);
}