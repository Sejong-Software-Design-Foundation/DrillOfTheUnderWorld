#include "Item.hpp"

class PortableOxygenCan : public Item {
public:
    PortableOxygenCan();
    void use() override;
};