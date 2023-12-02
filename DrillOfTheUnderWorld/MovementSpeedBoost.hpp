#include "Item.hpp"

class MovementSpeedBoost : public Item {
public:
    MovementSpeedBoost();
    void use() override;
};

MovementSpeedBoost::MovementSpeedBoost() : Item() {
    this->name = "이동속도 증가 부스트";
    this->info = "이동속도 레벨을 1 증가시킨다.";
    this->rank = 'N';
    this->price = N_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpMovementSpeedBoostName, -1,-1, 1 };
}

void MovementSpeedBoost::use() {
    pc.setSpdLev(pc.getSpdLev() + 1);
}