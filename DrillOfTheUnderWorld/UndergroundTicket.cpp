#include "UndergroundTicket.hpp"
#include "common.hpp"

UndergroundTicket::UndergroundTicket() : Item() {
    this->name = "지하 티켓";
    this->info = "상점에서 판매하는 아이템의 가격이 30%  할인된다.";
    this->rank = 'S';
    this->price = S_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpUndergroundTicketName, -1, -1, 1, 1 };
}

void UndergroundTicket::use() {
    pc.setHasUndergroundTicket(true);
}