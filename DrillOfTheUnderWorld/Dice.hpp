#include "Item.hpp"

class Dice : public Item {
public:
    Dice();
    void use() override;
};

Dice::Dice() : Item() {
    this->name = "�ֻ���";
    this->info = "PC�� �ɷ�ġ�� �������� �����Ѵ�.";
    this->rank = 'B';
    this->price = B_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpDiceName, -1,-1, 1 };
}

void Dice::use() {
    srand(static_cast<unsigned>(time(0)));

    pc.setAtkLev(rand() % 11);
    pc.setAtkSpdLev(rand() % 11);
    pc.setSpdLev(rand() % 11);
}