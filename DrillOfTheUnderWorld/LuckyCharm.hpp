#include "Item.hpp"

class LuckyCharm : public Item {
public:
    LuckyCharm();
    void use() override;
};

LuckyCharm::LuckyCharm() : Item() {
    this->name = "��� ����";
    this->info = "������ �̸��� ������ 1ȸ ����Ѵ�.";
    this->rank = 'A';
    this->price = A_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpLuckyCharmName, -1,-1, 1 };
}

void LuckyCharm::use() {
    pc.setHasLuckCharm(true);
}