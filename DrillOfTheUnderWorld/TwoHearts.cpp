#include "TwoHearts.hpp"
#include "common.hpp"

TwoHearts::TwoHearts() : Item() {
    this->name = "두 개의 심장";
    this->info = "산소 게이지 감소량이 감소한다.";
    this->rank = 'A';
    this->price = A_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpTwoHeartsName, -1, -1, 1, 1 };
}

void TwoHearts::use() {
    pc.setHasTwoHearts(true);
}