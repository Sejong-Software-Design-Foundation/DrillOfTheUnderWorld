#include "Item.hpp"

class FreshBrewedCoffee : public Item {
public:
    FreshBrewedCoffee();
    void use() override;
};