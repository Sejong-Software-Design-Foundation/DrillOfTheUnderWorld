#include "Item.hpp"

class Disassembler : public Item {
public:
    Disassembler();
    void use() override;
};