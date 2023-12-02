#include "Item.hpp"

class CaveSnake : public Item {
public:
    CaveSnake();
    void use() override;
};

CaveSnake::CaveSnake() : Item() {
    this->name = "���� ��";
    this->info = "���� ü���� 30%�� �ش��ϴ� ���ظ� �Դ´�.";
    this->rank = 'F';
    this->price = F_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpCaveSnakeName, -1,-1, 1 };
}

void CaveSnake::use() {
    pc.setHP(pc.getHP() * 0.7);
}