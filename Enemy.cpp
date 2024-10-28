#include "Enemy.h"

//=========================================================================================
// static variables
//=========================================================================================

void (Enemy::* Enemy::PhaseTable[static_cast<size_t>(Phase::kCountOfPhase)])() = {
	&Enemy::Approach,
	&Enemy::Shot,
	&Enemy::BreakAway
};

////////////////////////////////////////////////////////////////////////////////////////////
// Enemy class methods
////////////////////////////////////////////////////////////////////////////////////////////

void Enemy::Update() {

	while (true) {

		// phase table に呼び出し
		(this->*PhaseTable[static_cast<size_t>(phase_)])();

		if (phase_ == Phase::kCountOfPhase) {
			break;
		}
	}

}

void Enemy::Approach() {
	std::cout << "phase approach..." << std::endl;
	phase_ = Phase::kPhase_Shot;
}

void Enemy::Shot() {
	std::cout << "phase shot..." << std::endl;
	phase_ = Phase::kPhase_BreakAway;
}

void Enemy::BreakAway() {
	std::cout << "phase break away..." << std::endl;
	phase_ = Phase::kCountOfPhase;
}


