#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include "Zaznam.h"

/**
 * 
 * Structura Interval pro jednodušší práci s histogramem
 * 
 * @param lower_bound Spodní hranice
 * @param upper_bound horní hranice
 * @param cetnost počet výskytů
 *               
 */
struct Interval {
	float lower_bound;
	float upper_bound;
	int cetnost;
};

/**
 * 
 * Funkce pro vytvření histogramu
 * 
 * @param datas vector Záznamů
 * @param num_intervals počet vytvořených intervalů
 * @param min_value minimální hodnota
 * @param max_value maximální hodnota
 */
std::vector<Interval> histogram(const std::vector<Zaznam>& datas, int num_intervals, float min_value, float max_value) {
	std::vector<Interval> histogram_data;

	float interval_width = (max_value - min_value) / num_intervals;

	for (int i = 0; i < num_intervals; ++i) {
		Interval interval;
		interval.lower_bound = min_value + i * interval_width;
		interval.upper_bound = interval.lower_bound + interval_width;
		interval.cetnost = 0;
		histogram_data.push_back(interval);
	}

	for (const Zaznam& zaznam : datas) {
		float value = zaznam.teplota;
		if (value >= min_value && value <= max_value) {
			int interval_index = static_cast<int>((value - min_value) / interval_width);
			interval_index = std::min(std::max(interval_index, 0), num_intervals - 1);
			histogram_data[interval_index].cetnost++;
		}
	}

	return histogram_data;
}


/**
 * 
 * Funkce pro rozparsování času
 * 
 * @param cass nerozparsovaný čas
 *
 */ 
Zn cas(const std::string& cass){

	Zn cas;
	int index;
	int rok, mesic, den, hodina, minuta, vterina;

	index = cass.find('-');
	cas.rok = std::stoi(cass.substr(0, index));
	int index2 = cass.find('-', index + 1);
	cas.mesic = std::stoi(cass.substr(index + 1, index2 - index - 1));
	index = index2;
	index2 = cass.find('T', index + 1);
	cas.den = std::stoi(cass.substr(index + 1, index2 - index - 1));

	index = index2;
	index2 = cass.find(':', index + 1);
	cas.hodina = std::stoi(cass.substr(index + 1, index2 - index - 1));
	index = index2;
	index2 = cass.find(':', index + 1);
	cas.minuta = std::stoi(cass.substr(index+ 1, index2 - index - 1));
	index =index2;
	cas.vterina = std::stoi(cass.substr(index + 1));

	return cas;
}

/**
 * 
 * Funkce pro inicializaci dat a vytvoření instance
 * 
 * @param dat vstupní string s daty které zpracovávám
 * 
 */
Zaznam prevod(std::string dat) {
	string tim;
	float napeti{};
	float teplota{};
	float teplota2;
	float teplota3;
	float vlhkost{};
	float vlhkost2;
	float vlhkost3;

	std::stringstream datt(dat);
	int pom = 0;
	Zn casaa{};
	std::vector<std::string> time;
	std::string pom2;
	string zaz;
	while (std::getline(datt, pom2, ' ')) {
		if (pom == 0) {
			tim = pom2;
			casaa = cas(pom2);
		}
		else if (pom == 1) {
			zaz = pom2;
			napeti = std::stoul(pom2.substr(0, 2), nullptr, 16) * 30.0f;
			teplota = std::stoul(pom2.substr(2, 2), nullptr, 16);
			teplota2 = std::stoul(pom2.substr(4, 2), nullptr, 16);
			teplota3 = (1.0 / 10) * ((256 * teplota) + teplota2);
			vlhkost = std::stoul(pom2.substr(6, 2), nullptr, 16);
			vlhkost2 = std::stoul(pom2.substr(8, 2), nullptr, 16);
			vlhkost3 = (1.0 / 10) * ((256 * vlhkost) + vlhkost2);
		}
		pom++;
	}

	Zaznam zaznam(tim, napeti, teplota3, vlhkost3, casaa, zaz);
	return zaznam;
}

/**
 * 
 * Funkce vyhledánínejvyšší teploty
 * 
 * @param t vector záznamu z kterého se získa správný záznam
 *
 */

std::vector<Zaznam> maxT(std::vector<Zaznam>& t) {
	float max = t[1].teplota;
	for (int i = 0; i < t.size(); i++) {
		if (t[i].teplota > max) {
			max = t[i].teplota;
		}
	}
		std::vector<Zaznam> maxtT;

		for (int i = 0; i < t.size(); i++) {
			if (t[i].teplota == max) {
				maxtT.push_back(t[i]);
			}
		}
	return maxtT ;
}


/**
 * 
 * Funkce vyhledání nejnižší teploty
 * 
 * @param t vector záznamu z kterého se získa správný záznam
 *
 */

std::vector<Zaznam> minT(std::vector<Zaznam>&t) {
	float min = t[1].teplota;
	for (int i = 0; i < t.size(); i++) {
		if (t[i].teplota < min) {
			min = t[i].teplota;
		}
	}

		std::vector<Zaznam> mintT;

		for (int i = 0; i < t.size(); i++) {
			if (t[i].teplota == min) {
				mintT.push_back(t[i]);
			}
		}
		return mintT;
}

/**
 * 
 * Funkce pro vyhldání nejvyšší vlhkosti
 * 
 * @param t vector záznamu z kterého se získa správný záznam
 *
 */
std::vector<Zaznam> maxV(std::vector<Zaznam>& t) {
	float max = t[1].vlhkost;
	for (int i = 0; i < t.size(); i++) {
		if (t[i].teplota > max) {
			max = t[i].vlhkost;
		}
	}

	std::vector<Zaznam> maxvV;

	for (int i = 0; i < t.size(); i++) {
		if (t[i].vlhkost == max) {
			maxvV.push_back(t[i]);
		}
	}
	return maxvV;
}

/**
 * 
 * Funkce pro vyhldání nejnižší vlhkosti
 * 
 * @param t vector záznamu z kterého se získa správný záznam
 *
 */

std::vector<Zaznam> minV(std::vector<Zaznam>& t) {
	float min = t[1].vlhkost;
	for (int i = 0; i < t.size(); i++) {
		if (t[i].teplota < min) {
			min = t[i].vlhkost;
		}
	}

	std::vector<Zaznam> minvV;

	for (int i = 0; i < t.size(); i++) {
		if (t[i].vlhkost == min) {
			minvV.push_back(t[i]);
		}
	}
	return minvV;
}


/**
 * 
 * Funkce pro kontrolu duplicit
 * 
 * @param porovnavani vector ve kterém jsou uloženy všechny již použité záznamy
 * @param dat string s vstupnímí daty u kterých zjištuju zda nejsou duplicitní
 */ 

int duplicity(std::vector<std::string>& porovnavani, const std::string& dat) {
	for (int i = 0; i < porovnavani.size(); i++) {
		if (dat == porovnavani[i]) {
			return 1;
		}
	}
	porovnavani.push_back(dat);
	return 0;
}

/**
 * 
 * Funkce pro vyhledávání záznamu dle času
 * 
 * @param datas vector všech uložených záznamů
 * @param zn string s hledaný časový údaj ve stringu
 */ 

Zaznam hledat(std::vector<Zaznam> datas, const std::string& zn) {
	for (int i = 0; i < datas.size(); i++) {
		if (datas[i].tim == zn) {
			return datas[i];
		}
	}	
}

/**
 * 
 * Funkce pro porovnáváná časů 
 * 
 * @param b struktura b pro porovnávání časů
 * @param a struktura a pro porovnávání časů
 */ 

int compareZn(const Zn& a, const Zn& b) {
	if (a.rok != b.rok) return a.rok > b.rok;
	if (a.mesic != b.mesic) return a.mesic > b.mesic;
	if (a.den != b.den) return a.den > b.den;
	if (a.hodina != b.hodina) return a.hodina > b.hodina;
	if (a.minuta != b.minuta) return a.minuta > b.minuta;
	return a.vterina < b.vterina;
}


/**
 * 
 * Funkce pro třízení záznamů dle času
 * 
 * @param datas vector všech uložených záznamů ve kterém se vyhledává
 * 
 */ 
void tridit(std::vector<Zaznam>& datas) {
	for (int i = 0; i < datas.size(); i++) {
		for (int j = 0; j < datas.size() - i - 1; j++) {
			if (compareZn(datas[j].zn, datas[j + 1].zn)) {
				std::swap(datas[j], datas[j + 1]);
			}
		}
	}
}

/**
 * 
 * Funkce pro vypsání vyýstupu do souboru
 * 
 * @param datas vector všech uložených záznamů které se mají vypsat
 * 
 */ 

void vypsat(std::vector<Zaznam> datas) {

	std::ofstream output("output.txt");

	for (int i = 0; i < datas.size(); ++i) {
		Zaznam zaznam = datas[i];
		output << zaznam.tim << " " << zaznam.zaz << std::endl;
	}


	output.close();
}

/// Main s voláním jednotlivých vytvořených funkcí funkcí
int main()
{

	std::string dat;
	std::ifstream input("IoTSensorData1.txt");

	std:vector<std::string> porovnavani;

	std::vector<Zaznam> datas;
	while (getline(input, dat)) {
		std::cout << dat << std::endl;
		if (duplicity(porovnavani, dat) == 0) {
			Zaznam data = prevod(dat);
			datas.push_back(data);
		}
	}

	input.close();

	tridit(datas);

	for (int i = 0; i < datas.size(); i++) {
		std::cout << datas[i].tim << datas[i].napeti << datas[i].teplota << datas[i].vlhkost << std::endl;
	}
	
	std::vector<Zaznam> maaxT = maxT(datas);
	std::vector<Zaznam> miinT = minT(datas);
	std::vector<Zaznam> maaxV = maxV(datas);
	std::vector<Zaznam> miinV = minV(datas);

	for (int i = 0; i < maaxT.size(); ++i) {
		std::cout << maaxT[i].teplota << std::endl;
	}
	for (int i = 0; i < miinT.size(); ++i) {
		std::cout <<miinT[i].teplota << std::endl;
	}
	for (int i = 0; i < maaxV.size(); ++i) {
		std::cout << maaxV[i].vlhkost << std::endl;
	}
	for (int i = 0; i < miinV.size(); ++i) {
		std::cout << miinV[i].vlhkost << std::endl;
	}


	Zaznam zazn = hledat(datas,"2024-03-12T20:28:09");

	std::cout << zazn.tim << zazn.zaz << std::endl;


	std::vector<Interval> temp_histogram = histogram(datas, 10, 0.0f, 50.0f);

	for (int i = 0; i < temp_histogram.size(); ++i) {
		std::cout << "Interval: [" << temp_histogram[i].lower_bound << ", " << temp_histogram[i].upper_bound << "], Frequency: " << temp_histogram[i].cetnost << std::endl;
	}



	vypsat(datas);

	return 0;
}