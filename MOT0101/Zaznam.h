#pragma once
#include <string>

/// Struktura pro zaznamenání času
struct Zn {
    int rok;
    int mesic;
    int den;
    int hodina;
    int minuta;
    int vterina;
};

using namespace std;

///Třída na uložení záznamu 
class Zaznam
{
public:
	string tim; ///čas v podobě stringu
	float napeti; ///napětí získané z 1 bytu druhé části
	float teplota; ///teplota získané z 2 a 3 bytu druhé části
	float vlhkost; ///vlhkost získané z 4 a 5 bytu druhé části
    Zn zn; ///Rozparsovaný čas
    string zaz; ///Druhá část záznamu v nerozparované podobě
    
    ///Kontruktor třídy záznam
	Zaznam(std::string tim, float napeti, float teplota, float vlhkost, Zn zn, string zaz);

};

