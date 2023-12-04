#include "Item.hpp"

class MovementSpeedBoost : public Item {
public:
    MovementSpeedBoost();
    void use() override;
};