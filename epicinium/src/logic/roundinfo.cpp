#include "roundinfo.hpp"
#include "source.hpp"

#include "cycle.hpp"


RoundInfo::RoundInfo() :
	_gameover(false),
	_round(0),
	_year(1),
	_season(Season::SPRING),
	_daytime(Daytime::LATE),
	_phase(Phase::GROWTH)
{}
