#include "Item.hpp"

class Dice : public Item {
public:
    Dice();
    void use() override;
};