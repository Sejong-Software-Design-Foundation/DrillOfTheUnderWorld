#include "Item.hpp"

class LuckStone : public Item {
public:
    LuckStone();
    void use() override;
};