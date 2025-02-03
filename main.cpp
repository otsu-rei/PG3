//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* c++
#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <array>
#include <string>
#include <memory>
#include <algorithm>
#include <thread>
#include <array>
#include <queue>
#include <functional>
#include <bitset>
#include <cassert>
#include <optional>
#include <filesystem>
#include <variant>
#include <mutex>
#include <stack>
#include <concepts>

#include "Tmp.h"

////////////////////////////////////////////////////////////////////////////////////////////
// main
////////////////////////////////////////////////////////////////////////////////////////////
int main() {

	// init.
	const size_t size = 1000000;

	std::string rhs(size, 'a');
	std::string lhs = "";

	{
		std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

		// copy
		lhs = rhs;

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

		std::cout << "(copy)" << "time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "[us]" << std::endl;
	}

	// reset
	rhs = std::string(size, 'a');
	lhs = "";

	{
		std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

		// move
		lhs = std::move(rhs);

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

		std::cout << "(move)" << "time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "[us]" << std::endl;
	}



	


	return 0;
}