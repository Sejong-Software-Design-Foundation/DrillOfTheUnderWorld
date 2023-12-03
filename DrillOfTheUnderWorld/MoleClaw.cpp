#include "MoleClaw.hpp"
#include "common.hpp"

MoleClaw::MoleClaw() : Item() {
    this->name = "µÎ´õÁö ¼ÕÅé";
    this->info = "±¤¹° ÆÄ±«½Ã ÀçÈ­ È¹µæ·®ÀÌ Áõ°¡ÇÑ´Ù.";
    this->rank = 'B';
    this->price = B_RANK_PRICE;
    this->isUniqueHoldableItem = true;
    imageArray[imageLayer.imageCount++] = { bmpMoleClawName, -1, -1, 1, 1 };
}

void MoleClaw::use() {
    pc.setHasMoleClaw(true);
}