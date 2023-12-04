#include "MetalDetector.hpp"
#include "common.hpp"

MetalDetector::MetalDetector() : Item() {
    this->name = "�ݼ� Ž����";
    this->info = "������ �� ���� �����Ѵ�.";
    this->rank = 'S';
    this->price = S_RANK_PRICE;
    this->isUniqueHoldableItem = true;
    imageArray[imageLayer.imageCount++] = { bmpMetalDetectorName, -1, -1, 1, 1 };
}

void MetalDetector::use() {
    pc.setHasMetalDetector(true);
}