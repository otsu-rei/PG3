//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* c++
#include <cstdint>
#include <cstdio>
#include <cassert>
#include <format>

////////////////////////////////////////////////////////////////////////////////////////////
// methods
////////////////////////////////////////////////////////////////////////////////////////////

//! @brief 再帰的給料の計算
//! @param[in] 働いた時間
//! @return 給料
int32_t CalculateSalaryRecursive(uint32_t workTime) {
	assert(workTime != 0); //!< 働いてない

	if (workTime == 1) { //!< 最初の1時間は100円
		return 100;
	}

	//!< 前の1時間でもらった給料 * 2 - 50円
	return CalculateSalaryRecursive(workTime - 1) * 2 - 50;
}

//! @brief 一般給料の計算
//! @param[in] 働いた時間
//! @return 給料
int32_t CalculateSalary(uint32_t workTime) {
	return workTime * 1072; //!< 基本自給は1072円
}

////////////////////////////////////////////////////////////////////////////////////////////
// main
////////////////////////////////////////////////////////////////////////////////////////////
int main() {

	// 働いた時間
	uint32_t workTime = 1;

	while (true) {

		int32_t defaultSalary   = CalculateSalary(workTime);          //!< 一般給料
		int32_t recursiveSalary = CalculateSalaryRecursive(workTime); //!< 再帰的給料

		printf(std::format("\n働いた時間: {}時間\n", workTime).c_str());
		printf(std::format("> 一般給料: {}円\n", defaultSalary).c_str());
		printf(std::format("> 再帰的給料: {}円\n", recursiveSalary).c_str());

		if (recursiveSalary > defaultSalary) { //!< 再帰的給料が一般給料を超えた場合
			break;
		}

		workTime++;
	}
	

	return 0;
}