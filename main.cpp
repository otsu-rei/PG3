//-----------------------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------------------
//* c++
#include <cstdint>
#include <cstdio>
#include <format>
#include <thread>
#include <queue>
#include <chrono>

#include "Thread.h"

////////////////////////////////////////////////////////////////////////////////////////////
// TaskA class
////////////////////////////////////////////////////////////////////////////////////////////
class TaskA
	: public IThread {
public:

	void Execute() override {
		std::cout << "begin sleep thread id:" << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(2));
		std::cout << "end sleep thread id:" << std::this_thread::get_id() << std::endl;
	}

private:

};

////////////////////////////////////////////////////////////////////////////////////////////
// main
////////////////////////////////////////////////////////////////////////////////////////////
int main() {

	std::unique_ptr<ThreadPool> pool = std::make_unique<ThreadPool>();
	pool->Init();

	TaskA a;
	TaskA b;
	TaskA c;

	pool->SetTask(&a);
	pool->SetTask(&b);
	pool->SetTask(&c);

	while (true) {
		if (a.GetThreadState() == ThreadState::kCompleted) {
			std::cout << "taskA is completed." << std::endl;
			break;
		}
	}

	while (true) {
		if (b.GetThreadState() == ThreadState::kCompleted) {
			std::cout << "taskB is completed." << std::endl;
			break;
		}
	}

	while (true) {
		if (c.GetThreadState() == ThreadState::kCompleted) {
			std::cout << "taskB is completed." << std::endl;
			break;
		}
	}

	return 0;
}