#include "AncientVirus.hpp"
#include "common.hpp"

AncientVirus::AncientVirus() : Item() {
    this->name = "고대 바이러스";
    this->info = "PC의 최대 체력이 10% 감소한다.";
    this->rank = 'F';
    this->price = F_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpAncientVirusName, -1, -1, 1, 1 };
}

void AncientVirus::use() {
    pc.setMaxHP(pc.getMaxHP() * 0.9);
} 