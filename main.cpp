//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* c++
#include <cstdint>
#include <iostream>
#include <list>

typedef const char* STR;

////////////////////////////////////////////////////////////////////////////////////////////
// methods
////////////////////////////////////////////////////////////////////////////////////////////
void OutputStation(const std::list<STR> line) {
	for (const auto& station : line) {
		std::cout << "- " << station << std::endl;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
// main
////////////////////////////////////////////////////////////////////////////////////////////
int main() {

	std::list<STR> yamanoteLine = {
		"Tokyo", "Kanda", "Akihabara", "Okachimachi", "Ueno", "Uguisudani", "Nippori", /*"Nishi-Nippori",*/
		"Tabata", "Komagome", "Sugamo", "Otsuka", "Ikebukuro", "Mejiro", "Takadanobaba", "Shin-Okubo",
		"Shinjuku", "Yoyogi", "Harajuku", "Shibuya", "Ebisu", "Meguro", "Gotanda", "Osaki",
		"Shinagawa", /*"Takanawa Gateway",*/ "Tamachi", "Hamamatsucho", "Shimbashi", "Yurakucho"
	};

	std::cout << "yamanote line 1970." << std::endl;
	OutputStation(yamanoteLine);

	std::cout << "\nyamanote line 2019." << std::endl;
	// "Nishi-Nippori"駅 を挿入
	auto it = std::find(yamanoteLine.begin(), yamanoteLine.end(), "Nippori");

	if (it != yamanoteLine.end()) {
		yamanoteLine.emplace(++it, "Nishi-Nippori");
	}

	OutputStation(yamanoteLine);

	std::cout << "\nyamanote line 2022." << std::endl;
	// "Takanawa Gateway"駅 を挿入
	it = std::find(yamanoteLine.begin(), yamanoteLine.end(), "Shinagawa");

	if (it != yamanoteLine.end()) {
		yamanoteLine.emplace(++it, "Takanawa Gateway");
	}

	OutputStation(yamanoteLine);

	return 0;
}