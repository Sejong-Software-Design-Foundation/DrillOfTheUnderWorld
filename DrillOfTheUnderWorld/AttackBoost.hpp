#include "Item.hpp"

class AttackBoost : public Item {
public:
    AttackBoost();
    void use() override;
};