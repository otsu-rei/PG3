//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* c++
#include <cstdint>
#include <cstdio>
#include <format>
#include <thread>
#include <queue>
#include <mutex>
#include <string>

////////////////////////////////////////////////////////////////////////////////////////////
// main
////////////////////////////////////////////////////////////////////////////////////////////
int main() {

	//* back thread

	std::mutex mutex;
	std::queue<int> q;
	bool isExit = false;

	std::thread th1([&]() {
		uint32_t frame = 0;

		while (!isExit) {

			std::string log = "";
			log += std::format("[back ground thread frame: {}] ", frame);

			mutex.lock();
			if (q.empty()) {
				log += "q is empty...\n";

			} else {
				log += std::format("q front: {}\n", q.front());
				q.pop();
			}
			mutex.unlock();

			printf(log.c_str());
			frame++;

			// 早くなりすぎないよう調整
			std::this_thread::sleep_for(std::chrono::milliseconds(600));
		}
	});

	//* main

	uint32_t frame = 0;

	while (true) {

		std::string log = "";

		log += std::format("[main thread frame: {}] ", frame);

		q.emplace(frame);
		log += std::format("q emplace: {}\n", frame);

		printf(log.c_str());
		frame++;

		// 早くなりすぎないよう調整
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}

	th1.join();

	return 0;
}