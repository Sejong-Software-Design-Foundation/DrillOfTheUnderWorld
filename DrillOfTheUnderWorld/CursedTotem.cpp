#include "CursedTotem.hpp"
#include "common.hpp"

CursedTotem::CursedTotem() : Item() {
    this->name = "저주받은 토템";
    this->info = "공격력 레벨이 1만큼 감소한다.";
    this->rank = 'F';
    this->price = F_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpCursedTotemName, -1,-1, 1 };
}

void CursedTotem::use() {
    pc.setAtkLev(pc.getAtkLev() - 1);
}