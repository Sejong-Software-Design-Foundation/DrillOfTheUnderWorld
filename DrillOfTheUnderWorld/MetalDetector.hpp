#include "Item.hpp"

class MetalDetector : public Item {
public:
    MetalDetector();
    void use() override;
};

MetalDetector::MetalDetector() : Item() {
    this->name = "금속 탐지기";
    this->info = "광물이 더 자주 등장한다.";
    this->rank = 'S';
    this->price = S_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpMetalDetectorName, -1,-1, 1 };
}

void MetalDetector::use() {
    pc.setHasMetalDetector(true);
}