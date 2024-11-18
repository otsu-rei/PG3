//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* c++
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cassert>

bool LoadFile(const std::string& filepath, std::vector<std::string>& datas) {

	std::fstream file(filepath);

	if (!file.is_open()) {
		return false;
	}

	std::string line;

	while (std::getline(file, line)) {

		if (!(line.front() == '[' && line.back() == ']')) { //!< []で区切られてるか確認
			continue;
		}

		line = line.substr(1, line.size() - 2);

		std::stringstream ss(line);
		std::string part;

		while (std::getline(ss, part, ',')) {
			if (!(part.front() == '"', part.back() == '"')) {
				continue;
			}

			part = part.substr(1, part.size() - 2);

			datas.emplace_back(part);
		}
	}

	return true;
}

struct GroupNumbers {
	uint32_t k;
	uint32_t g;
};

GroupNumbers GetGroupNumbers(const std::string& str) {

	GroupNumbers result = {};

	std::string k = str.substr(1, 3);
	result.k = std::stoi(k);

	std::string g = str.substr(5, 4);
	result.g = std::stoi(g);

	return result;
}

////////////////////////////////////////////////////////////////////////////////////////////
// main
////////////////////////////////////////////////////////////////////////////////////////////
int main() {

	std::vector<std::string> datas;

	assert(LoadFile("PG3_2024_03_02.txt", datas));

	// sort
	std::sort(datas.begin(), datas.end(), [](const std::string& a, const std::string& b) {

		GroupNumbers groupA = GetGroupNumbers(a);
		GroupNumbers groupB = GetGroupNumbers(b);

		//!< kで入れ替え
		if (groupA.k != groupB.k) {
			return groupA.k < groupB.k;
		} 

		//!< gで入れ替え
		return groupA.g < groupB.g;
	});

	for (size_t i = 0; i < datas.size(); ++i) {
		std::cout << datas[i] << std::endl;
	}

	return 0;
}