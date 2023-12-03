#include "UndergroundTicket.hpp"
#include "common.hpp"

UndergroundTicket::UndergroundTicket() : Item() {
    this->name = "���� Ƽ��";
    this->info = "�������� �Ǹ��ϴ� �������� ������ 30%  ���εȴ�.";
    this->rank = 'S';
    this->price = S_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpUndergroundTicketName, -1, -1, 1, 1 };
}

void UndergroundTicket::use() {
    pc.setHasUndergroundTicket(true);
}