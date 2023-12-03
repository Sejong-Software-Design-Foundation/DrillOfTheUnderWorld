#include "Item.hpp"

class CursedTotem : public Item {
public:
    CursedTotem();
    void use() override;
};