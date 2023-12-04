#include "Item.hpp"

class UndergroundTicket : public Item {
public:
    UndergroundTicket();
    void use() override;
};