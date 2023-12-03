#include "Disassembler.hpp"
#include "common.hpp"

Disassembler::Disassembler() : Item() {
    this->name = "해체기";
    this->info = "보유한 아이템 중 1개가 랭크에 맞는 돌개수로 치환된다.";
    this->rank = 'B';
    this->price = B_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpDisassemblerName, -1, -1, 1, 1 };
}

void Disassembler::use() {
    /*
    srand(static_cast<unsigned>(time(0)));

    if (!pc.getOwnedItemList().empty()) {
        int randomIndex = rand() % pc.getOwnedItemList().size();

        auto iter = pc.getOwnedItemList().begin() + randomIndex;
        int randomItemPrice = (*iter)->getPrice();
        pc.getOwnedItemList().erase(iter);

        pc.setStone(randomItemPrice);
    }
    */
}