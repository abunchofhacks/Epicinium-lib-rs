#pragma once
#include "header.hpp"

#include "cell.hpp"
#include "player.hpp"
#include "vision.hpp"

class Bible;
class Board;
class ChangeSet;
class PlayerInfo;
struct TileToken;
struct UnitToken;


// VisionTransitionMapreduceImplementation has 3 realizations.
template <class This>
class VisionTMRI
{
public:
	VisionTMRI(const Bible& bible, Board& board,
			PlayerInfo& info,
			ChangeSet& changeset);

protected:
	const Bible& _bible;
	Board& _board;
	PlayerInfo& _info;
	ChangeSet& _changeset;
	std::vector<Vision> _results;

	void map(Cell index);
	void reduce(Cell index)
	{
		static_cast<This*>(this)->reduce(index);
	}

	void provider(Cell from, const TileToken& tile);
	void provider(Cell from, const UnitToken& unit);

public:
	void execute();
	void executeAround(Cell near, int range);
};

class VisionTransition : public VisionTMRI<VisionTransition>
{
public:
	using VisionTMRI::VisionTMRI;

private:
	friend VisionTMRI;

	void reduce(Cell index);
};

class InitialVisionTransition : public VisionTMRI<InitialVisionTransition>
{
public:
	using VisionTMRI::VisionTMRI;

private:
	friend VisionTMRI;

	void reduce(Cell index);
};

class RejoinVisionTransition : public VisionTMRI<RejoinVisionTransition>
{
public:
	using VisionTMRI::VisionTMRI;

private:
	friend VisionTMRI;

	void reduce(Cell index);
};
