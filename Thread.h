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
#include <chrono>
#include <cassert>
#include <functional>
#include <vector>

#include "CXXAttributeConfig.h"

//-----------------------------------------------------------------------------------------
// forward
//-----------------------------------------------------------------------------------------
class Thread;

////////////////////////////////////////////////////////////////////////////////////////////
// ExecutionState enum class
////////////////////////////////////////////////////////////////////////////////////////////
enum class ExecutionState {
	kWaiting,
	kRunning,
	kCompleted,
};

////////////////////////////////////////////////////////////////////////////////////////////
// Interface ThreadExecution class
////////////////////////////////////////////////////////////////////////////////////////////
class IThreadExecution {
public:

	//=========================================================================================
	// public methods
	//=========================================================================================

	virtual void Execute(_MAYBE_UNUSED const Thread* const thread) = 0;

	void WaitComplete();

	ExecutionState GetState() const { return state_; }

	void SetState(ExecutionState state) { state_ = state; }

protected:

	//=========================================================================================
	// protected variables
	//=========================================================================================

	ExecutionState state_ = ExecutionState::kWaiting;

};

////////////////////////////////////////////////////////////////////////////////////////////
// Thread class
////////////////////////////////////////////////////////////////////////////////////////////
class Thread {
public:

	//=========================================================================================
	// public methods
	//=========================================================================================

	Thread()  = default;
	~Thread() { Term(); }

	void Create(const std::function<void()>& threadFunc);

	void Term();

	void ExecuteTask();

	bool IsTerm() const { return isTerm_; }

	void SetTask(IThreadExecution* task) { task_ = task; }

private:

	//=========================================================================================
	// private variables
	//=========================================================================================

	std::thread thread_;

	bool isTerm_ = false;

	IThreadExecution* task_ = nullptr;

};

////////////////////////////////////////////////////////////////////////////////////////////
// ThreadCollection class
////////////////////////////////////////////////////////////////////////////////////////////
class ThreadCollection {
public:

	//=========================================================================================
	// public methods
	//=========================================================================================

	ThreadCollection()  = default;
	~ThreadCollection() { Term(); }

	void Init();

	void Term();

	void PushTask(IThreadExecution* task) { tasks_.push(task); }

private:

	//=========================================================================================
	// private variables
	//=========================================================================================

	std::vector<std::unique_ptr<Thread>> threads_;
	std::queue<IThreadExecution*> tasks_;

	std::mutex mutex_;

};

static std::mutex sMutex;
void ThreadLog(const std::string& mes);