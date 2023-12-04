#include "Item.hpp"

class AttackSpeedBoost : public Item {
public:
    AttackSpeedBoost();
    void use() override;
};