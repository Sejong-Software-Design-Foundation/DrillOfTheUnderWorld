#include "Item.hpp"

class MoleClaw : public Item {
public:
    MoleClaw();
    void use() override;
};

MoleClaw::MoleClaw() : Item() {
    this->name = "µÎ´õÁö ¼ÕÅé";
    this->info = "±¤¹° ÆÄ±«½Ã ÀçÈ­ È¹µæ·®ÀÌ Áõ°¡ÇÑ´Ù.";
    this->rank = 'B';
    this->price = B_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpMoleClawName, -1,-1, 1 };
}

void MoleClaw::use() {
    pc.setHasMoleClaw(true);
}