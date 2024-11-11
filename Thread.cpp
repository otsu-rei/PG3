#include "Thread.h"

////////////////////////////////////////////////////////////////////////////////////////////
// ThreadPool class methods
////////////////////////////////////////////////////////////////////////////////////////////

void ThreadPool::Init() {
	threads_.resize(2); //!< 1つはmain threadとして使うため

	for (auto& thread : threads_) {
		thread.thread = std::thread([&]() {
			ThreadLog("begin thread. ");

			while (!isTerm_) {
				if (thread.task) {
					assert(thread.task->GetThreadState() == ThreadState::kWaiting);

					// ここでタスクを実行
					thread.task->SetThreadState(ThreadState::kRunning);
					thread.task->Execute();
					thread.task->SetThreadState(ThreadState::kCompleted);
					thread.task = nullptr;
					ThreadLog("task is end. ");

				} else {

					std::unique_lock<std::mutex> lock(mutex_);
					cond_.wait(lock, [&]() { return !tasks_.empty() || isTerm_; });

					if (isTerm_) {
						break; //!< 終了する
					}
					
					thread.task = tasks_.front();
					tasks_.pop();
					
				}
			}

			ThreadLog("end thread. ");
		});
	}
}

void ThreadPool::SetTask(IThread* task) {
	tasks_.push(task);
}

void ThreadPool::Term() {
	isTerm_ = true;
	//cond_.notify_all();

	for (auto& thread : threads_) {
		thread.thread.join();
	}
}

void ThreadPool::ThreadLog(const std::string& mes) {
	std::lock_guard<std::mutex> lock(mutex_);
	std::cout << mes << "[thread id]: " << std::this_thread::get_id() << std::endl;
}
