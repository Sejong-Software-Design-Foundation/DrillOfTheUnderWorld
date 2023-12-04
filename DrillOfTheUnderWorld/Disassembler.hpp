#include "Item.hpp"
#include <vector>

class Disassembler : public Item {
public:
    Disassembler();
    void use() override;
    std::vector<Item*> useItem(std::vector<Item*> ownedItems);
};