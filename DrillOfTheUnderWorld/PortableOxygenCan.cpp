#include "PortableOxygenCan.hpp"
#include "common.hpp"

PortableOxygenCan::PortableOxygenCan() : Item() {
    this->name = "휴대용 산소캔";
    this->info = "PC의 산소게이지를 모두 회복한다.";
    this->rank = 'E';
    this->price = E_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpPortableOxygenCanName, -1, -1, 1, 1 };
}

void PortableOxygenCan::use() {
    pc.setOxygen(pc.getMaxOxygen());
}