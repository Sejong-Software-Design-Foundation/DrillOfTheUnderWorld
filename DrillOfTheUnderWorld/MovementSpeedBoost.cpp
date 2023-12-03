#include "MovementSpeedBoost.hpp"
#include "common.hpp"

MovementSpeedBoost::MovementSpeedBoost() : Item() {
    this->name = "�̵��ӵ� ���� �ν�Ʈ";
    this->info = "�̵��ӵ� ������ 1 ������Ų��.";
    this->rank = 'N';
    this->price = N_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpMovementSpeedBoostName, -1, -1, 1, 1 };
}

void MovementSpeedBoost::use() {
    pc.setSpdLev(pc.getSpdLev() + 1);
}