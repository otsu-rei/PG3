#include "Thread.h"

void IThreadExecution::WaitComplete() {
	while (state_ != ExecutionState::kCompleted) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void Thread::Create(const std::function<void()>& threadFunc) {
	thread_ = std::thread(threadFunc);
}

void Thread::Term() {
	isTerm_ = true;

	if (thread_.joinable()) {
		thread_.join();
	}
}

void Thread::ExecuteTask() {
	if (task_ == nullptr) {
		return;
	}

	if (task_->GetState() == ExecutionState::kWaiting) {
		ThreadLog("## Begin Task: ");
		task_->SetState(ExecutionState::kRunning);
		task_->Execute(this);
		task_->SetState(ExecutionState::kCompleted);
		ThreadLog("## End Task: ");
	}

	task_ = nullptr; //!< taskを完了
}

void ThreadLog(const std::string& mes) {
	std::lock_guard<std::mutex> lock(sMutex);
	std::cout << mes << "[thread id]: " << std::this_thread::get_id() << std::endl;
}

void ThreadCollection::Init() {
	threads_.resize(3);

	for (auto& thread : threads_) {
		thread = std::make_unique<Thread>();

		thread->Create([&]() {
			ThreadLog("# Begin Thread: ");

			while (true) {
				thread->ExecuteTask();

				if (thread->IsTerm()) {
					break;
				}

				std::lock_guard<std::mutex> lock(mutex_);

				if (!tasks_.empty()) {
					thread->SetTask(tasks_.front());
					tasks_.pop();
				}
			}

			ThreadLog("# End Thread: ");
		});
	}
}

void ThreadCollection::Term() {
	threads_.clear();
}
