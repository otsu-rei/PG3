//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* c++
#include <cstdint>
#include <cstdio>
#include <format>
#include <random>
#include <string>
#include <thread>
#include <chrono>
#include <functional>

////////////////////////////////////////////////////////////////////////////////////////////
// typedef
////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////
// methods
////////////////////////////////////////////////////////////////////////////////////////////

//! @brief 6面ダイスを振る関数
//! @return 1~6をランダムで返す
int32_t RollDice() {
	static std::mt19937 seed(std::random_device{}());

	// 6面ダイスなので1~6
	std::uniform_int_distribution<int32_t> dist(1, 6);
	return dist(seed);
}

void SetTimeout(const std::string& outputLog, const std::chrono::seconds& waitTime /*second*/) {
	printf(outputLog.c_str());
	std::this_thread::sleep_for(waitTime);
}

////////////////////////////////////////////////////////////////////////////////////////////
// main
////////////////////////////////////////////////////////////////////////////////////////////
int main() {

	printf("サイコロを振ります...");
	int32_t dice = RollDice();

	printf("半か丁か当ててください. 半だと思うなら1, 丁だと思うなら0\n");

	int32_t answer = 0;
	scanf_s("%d", &answer);

	printf("答えは");

	// 1秒を3回待つ
	for (int32_t i = 0; i < 3; ++i) {
		SetTimeout(".", std::chrono::seconds(1));
	}

	printf("\n");

	std::function<std::string(void)> answerFunction = [answer, dice]() {
		// userの答えが合っている場合
		if (answer == dice % 2) {
			return "正解\n";
		}

		return "不正解\n";
	};

	printf(answerFunction().c_str());

	printf("\nダイス値: %d", dice);

	return 0;
}