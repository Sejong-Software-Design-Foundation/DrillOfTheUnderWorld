#include "Item.hpp"

class BloodBag : public Item {
public:
    BloodBag();
    void use() override;
};