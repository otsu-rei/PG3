#pragma once

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
#include <condition_variable>
#include <string>
#include <iostream>
#include <sstream>
#include <cassert>


////////////////////////////////////////////////////////////////////////////////////////////
// ThreadState enum class
////////////////////////////////////////////////////////////////////////////////////////////
enum class ThreadState : uint32_t {
	kWaiting,   //!< 待機中
	kRunning,   //!< 実行中
	kCompleted, //!< 完了
};

////////////////////////////////////////////////////////////////////////////////////////////
// Interface Thread class
////////////////////////////////////////////////////////////////////////////////////////////
class IThread {
public:

	//=========================================================================================
	// publicm methods
	//=========================================================================================

	virtual void Execute() = 0;

	const ThreadState GetThreadState() const { return state_; }

	void SetThreadState(ThreadState state) { state_ = state; }

protected:

	//=========================================================================================
	// protected variables
	//=========================================================================================

	ThreadState state_ = ThreadState::kWaiting;

};

////////////////////////////////////////////////////////////////////////////////////////////
// ThreadPool class
////////////////////////////////////////////////////////////////////////////////////////////
class ThreadPool {
public:

	//=========================================================================================
	// publicm methods
	//=========================================================================================

	ThreadPool()  = default;
	~ThreadPool() { Term(); }

	void Init();

	void SetTask(IThread* task);

	void Term();

	
private:

	////////////////////////////////////////////////////////////////////////////////////////////
	// ThreadInfo structure
	////////////////////////////////////////////////////////////////////////////////////////////
	struct ThreadInfo {
		std::thread thread;
		IThread*    task = nullptr;
	};

	//=========================================================================================
	// private variables
	//=========================================================================================

	std::queue<IThread*>    tasks_;
	std::vector<ThreadInfo> threads_;
	//* thread数は std::thread::hardware_concurrency() - 1 が理想

	bool isTerm_ = false;

	//* thread control members *//

	std::mutex              mutex_;
	std::condition_variable cond_;

	//=========================================================================================
	// private methods
	//=========================================================================================

	void ThreadLog(const std::string& mes);

};