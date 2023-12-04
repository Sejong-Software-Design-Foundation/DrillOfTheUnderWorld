#include "Disassembler.hpp"
#include "common.hpp"

Disassembler::Disassembler() : Item() {
    this->name = "해체기";
    this->info = "보유한 아이템 중 1개가 랭크에 맞는 돌개수 * (1~5배)로 치환된다.";
    this->rank = 'B';
    this->price = B_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpDisassemblerName, -1, -1, 1, 1 };
}

void Disassembler::use() {
}

std::vector<Item*> Disassembler::useItem(std::vector<Item*> ownedItems){
    srand(static_cast<unsigned>(time(0)));

    if (!ownedItems.empty()) {
        int randomIndex = rand() % ownedItems.size();

        auto iter = ownedItems.begin() + randomIndex;
        int randomItemPrice = (*iter)->getPrice();
        ownedItems.erase(iter);

        pc.setStone(pc.getStone() + randomItemPrice * (rand() % 5 + 1));
    }
    return ownedItems;
}