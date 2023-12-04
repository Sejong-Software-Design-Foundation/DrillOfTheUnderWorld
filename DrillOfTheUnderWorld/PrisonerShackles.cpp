#include "PrisonerShackles.hpp"
#include "common.hpp"

PrisonerShackles::PrisonerShackles() : Item() {
    this->name = "죄수용 족쇄";
    this->info = "PC의 이동속도 레벨이 1만큼 감소한다.";
    this->rank = 'F';
    this->price = F_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpPrisonerShacklesName, -1, -1, 1, 1 };
}

void PrisonerShackles::use() {
    pc.setSpdLev(pc.getSpdLev() - 1);
}