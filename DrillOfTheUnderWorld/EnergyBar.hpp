#include "Item.hpp"

class EnergyBar : public Item {
public:
    EnergyBar();
    void use() override;
};