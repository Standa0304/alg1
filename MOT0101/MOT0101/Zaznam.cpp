#include "Zaznam.h"

// Konstruktor t��dy Zaznam
Zaznam::Zaznam(std::string tim, float napeti, float teplota, float vlhkost, Zn zn, std::string zaz)
    : tim(tim), napeti(napeti), teplota(teplota), vlhkost(vlhkost), zn(zn), zaz(zaz) {}
