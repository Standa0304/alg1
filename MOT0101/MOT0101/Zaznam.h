#pragma once
#include <string>

struct Zn {
    int rok;
    int mesic;
    int den;
    int hodina;
    int minuta;
    int vterina;
};

using namespace std;
class Zaznam
{
public:
	string tim;
	float napeti;
	float teplota;
	float vlhkost;
    Zn zn;
    string zaz;
    

	Zaznam(std::string tim, float napeti, float teplota, float vlhkost, Zn zn, string zaz);

};

