#include "Disassembler.hpp"
#include "common.hpp"

Disassembler::Disassembler() : Item() {
    this->name = "��ü��";
    this->info = "������ ������ �� 1���� ��ũ�� �´� ������ * (1~5��)�� ġȯ�ȴ�.";
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