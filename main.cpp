//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* c++
#include <cstdint>
#include <iostream>
#include <cassert>
#include <format>
#include <optional>

////////////////////////////////////////////////////////////////////////////////////////////
// methods
////////////////////////////////////////////////////////////////////////////////////////////

//! @brief 再帰的給料の計算
//! @param[in] 働いた時間
//! @return 給料
int32_t CalculateNextSalaryRecursive() {
	static std::optional<size_t> salary = std::nullopt; //!< 1時間前の給料

	// 給料の計算
	if (salary.has_value()) {
		salary = salary.value() * 2 - 50;

	} else {
		// 初回の給料計算
		salary = 100;
	}

	return salary.value();
}

//! @brief 一般給料の計算
//! @param[in] 働いた時間
//! @return 給料
int32_t CalculateSalary() {
	return 1072;
}

////////////////////////////////////////////////////////////////////////////////////////////
// main
////////////////////////////////////////////////////////////////////////////////////////////
int main() {

	size_t time = 0;

	size_t defaultSalary   = 0;
	size_t recursiveSalary = 0;

	while (true) {

		++time;
		defaultSalary   += CalculateSalary();
		recursiveSalary += CalculateNextSalaryRecursive();

		std::cout << std::format("time:{} default:{} recursive:{}\n", time, defaultSalary, recursiveSalary) << std::endl;

		if (recursiveSalary >= defaultSalary) {
			break;
		}
	}

	return 0;
}