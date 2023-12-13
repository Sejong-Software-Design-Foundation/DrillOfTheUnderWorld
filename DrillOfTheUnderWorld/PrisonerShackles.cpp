#include "PrisonerShackles.hpp"
#include "common.hpp"

PrisonerShackles::PrisonerShackles() : Item() {
    this->name = "�˼��� ����";
    this->info = "PC�� �̵��ӵ� ������ 1��ŭ �����Ѵ�.";
    this->rank = 'F';
    this->price = F_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpPrisonerShacklesName, -1, -1, 1, 1 };
    this->isUniqueHoldableItem = true;
}

void PrisonerShackles::use() {
    pc.setSpdLev(pc.getSpdLev() - 1);
}