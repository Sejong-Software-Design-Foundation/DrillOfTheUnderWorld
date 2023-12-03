#include "CaveSnake.hpp"
#include "common.hpp"

CaveSnake::CaveSnake() : Item() {
    this->name = "동굴 뱀";
    this->info = "현재 체력의 30%에 해당하는 피해를 입는다.";
    this->rank = 'F';
    this->price = F_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpCaveSnakeName, -1,-1, 1 };
}

void CaveSnake::use() {
    pc.setHP(pc.getHP() * 0.7);
}