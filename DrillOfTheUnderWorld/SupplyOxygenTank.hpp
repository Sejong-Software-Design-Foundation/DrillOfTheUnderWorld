#include "Item.hpp"

class SupplyOxygenTank : public Item {
public:
    SupplyOxygenTank();
    void use() override;
};