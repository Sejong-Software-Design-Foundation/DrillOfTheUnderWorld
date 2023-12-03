#include "Item.hpp"

class PrisonerShackles : public Item {
public:
    PrisonerShackles();
    void use() override;
};