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
	: public IThreadExecution {
public:

	void Execute(_MAYBE_UNUSED const Thread* const thread) override {
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}

private:
};

////////////////////////////////////////////////////////////////////////////////////////////
// TaskB class
////////////////////////////////////////////////////////////////////////////////////////////
class TaskB
	: public IThreadExecution {
public:

	void Execute(_MAYBE_UNUSED const Thread* const thread) override {
		std::this_thread::sleep_for(std::chrono::seconds(6));
	}

private:
};

////////////////////////////////////////////////////////////////////////////////////////////
// main
////////////////////////////////////////////////////////////////////////////////////////////
int main() {

	std::unique_ptr<ThreadCollection> collection = std::make_unique<ThreadCollection>();
	collection->Init();

	TaskA a;
	TaskB b;
	TaskA c;

	collection->PushTask(&a);
	collection->PushTask(&b);
	collection->PushTask(&c);

	a.WaitComplete();
	b.WaitComplete();
	c.WaitComplete();

	return 0;
}