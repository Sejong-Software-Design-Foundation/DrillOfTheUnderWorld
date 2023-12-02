#include "Item.hpp"

class MetalDetector : public Item {
public:
    MetalDetector();
    void use() override;
};

MetalDetector::MetalDetector() : Item() {
    this->name = "�ݼ� Ž����";
    this->info = "������ �� ���� �����Ѵ�.";
    this->rank = 'S';
    this->price = S_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpMetalDetectorName, -1,-1, 1 };
}

void MetalDetector::use() {
    pc.setHasMetalDetector(true);
}