#include "Item.hpp"

class MetalDetector : public Item {
public:
    MetalDetector();
    void use() override;
};