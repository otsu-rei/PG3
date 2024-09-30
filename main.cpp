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

////////////////////////////////////////////////////////////////////////////////////////////
// typedef
////////////////////////////////////////////////////////////////////////////////////////////

typedef void (*OutputFunction)(const std::string&);

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

//! @brief dice値が半か丁か判別する
//! @param[in] dice       ダイスの値
//! @param[in] userAnswer 半か丁か(半の場合は1, 丁の場合は0)
//! @return 正解または不正解のstring
std::string CheckAnswer(int32_t dice, int32_t userAnswer) {

	// userの答えが合っている場合
	if (userAnswer == dice % 2) {
		return "正解\n";
	}

	return "不正解\n";
}

//! @brief consoleにstrを出力
void OutputConsole(const std::string& str) {
	printf(str.c_str());
}

void Wait(OutputFunction func, int32_t waitSecond) {

	int32_t waitTime = waitSecond;

	// waitTimeが0秒になるまで続ける
	while (waitTime > 0) {

		func(".");

		std::this_thread::sleep_for(std::chrono::seconds(1));
		waitTime--; //!< 1秒待った
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
// main
////////////////////////////////////////////////////////////////////////////////////////////
int main() {

	printf("サイコロを振ります...\n");

	int32_t dice = RollDice();

	printf("半か丁か当ててください. 半だと思うなら1, 丁だと思うなら0\n");

	int32_t answer = 0;
	scanf_s("%d", &answer);

	printf("答えは");

	OutputFunction func = &OutputConsole;
	Wait(func, 3);

	printf("\n");
	printf(std::format("diceの値: {}\n", dice).c_str());
	printf(CheckAnswer(dice, answer).c_str());

	return 0;
}