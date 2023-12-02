#include "Item.hpp"

class FreshBrewedCoffee : public Item {
public:
    FreshBrewedCoffee();
    void use() override;
};

FreshBrewedCoffee::FreshBrewedCoffee() : Item() {
    this->name = "�� ���� Ŀ��";
    this->info = "PC�� �ִ� ��Ұ������� 10% �����Ѵ�.";
    this->rank = 'C';
    this->price = C_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpFreshBrewedCoffeeName, -1,-1, 1 };
}

void FreshBrewedCoffee::use() {
    pc.setMaxOxygen(pc.getMaxOxygen() * 1.1);
}