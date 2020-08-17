#include "newtbrain.hpp"
#include "source.hpp"


void NewtBrain::Output::assign(const std::vector<float>& data)
{
	DEBUG_ASSERT(data.size() == Output::SIZE);

	size_t i = 0;

	DEBUG_ASSERT(data.begin() + i + Output::PARAMETER_SIZE <= data.end());
	DEBUG_ASSERT(params.size() == Output::PARAMETER_SIZE);
	std::copy(data.begin() + i, data.begin() + i + Output::PARAMETER_SIZE,
		params.begin());
	i += Output::PARAMETER_SIZE;

	DEBUG_ASSERT(data.begin() + i + TILETYPE_SIZE <= data.end());
	DEBUG_ASSERT(tiletypes.size() == TILETYPE_SIZE);
	std::copy(data.begin() + i, data.begin() + i + TILETYPE_SIZE,
		tiletypes.begin());
	i += TILETYPE_SIZE;

	DEBUG_ASSERT(data.begin() + i + UNITTYPE_SIZE <= data.end());
	DEBUG_ASSERT(unittypes.size() == UNITTYPE_SIZE);
	std::copy(data.begin() + i, data.begin() + i + UNITTYPE_SIZE,
		unittypes.begin());
	i += UNITTYPE_SIZE;

	for (auto& row : groundSubjectPreference)
	{
		DEBUG_ASSERT(data.begin() + i + Position::MAX_COLS <= data.end());
		DEBUG_ASSERT(row.size() == Position::MAX_COLS);
		std::copy(data.begin() + i, data.begin() + i + Position::MAX_COLS,
			row.begin());
		i += Position::MAX_COLS;
	}

	for (auto& row : tileSubjectPreference)
	{
		DEBUG_ASSERT(data.begin() + i + Position::MAX_COLS <= data.end());
		DEBUG_ASSERT(row.size() == Position::MAX_COLS);
		std::copy(data.begin() + i, data.begin() + i + Position::MAX_COLS,
			row.begin());
		i += Position::MAX_COLS;
	}

	for (auto& row : placementPreference)
	{
		DEBUG_ASSERT(data.begin() + i + Position::MAX_COLS <= data.end());
		DEBUG_ASSERT(row.size() == Position::MAX_COLS);
		std::copy(data.begin() + i, data.begin() + i + Position::MAX_COLS,
			row.begin());
		i += Position::MAX_COLS;
	}
}

std::string NewtBrain::Output::toPrettyString() const
{
	std::stringstream strm;

	for (size_t i = 0; i < params.size(); i++)
	{
		strm << "\t";
		switch (i)
		{
			case WEIGHT_MONEY: strm << "WEIGHT_MONEY: "; break;
			case WEIGHT_ISTARGET: strm << "WEIGHT_ISTARGET: "; break;
			case WEIGHT_OCCUPIED: strm << "WEIGHT_OCCUPIED: "; break;
			case WEIGHT_OVERLAP: strm << "WEIGHT_OVERLAP: "; break;
			case MUL_SETTLE: strm << "MUL_SETTLE: "; break;
			case MUL_MOVE_SETTLER: strm << "MUL_MOVE_SETTLER: "; break;
			case MUL_PRODUCE: strm << "MUL_PRODUCE: "; break;
			case MUL_EXPAND: strm << "MUL_EXPAND: "; break;
			case MUL_CULTIVATE: strm << "MUL_CULTIVATE: "; break;
			case MUL_UPGRADE: strm << "MUL_UPGRADE: "; break;
			case MUL_CAPTURE: strm << "MUL_CAPTURE: "; break;
			case MUL_SHAPE: strm << "MUL_SHAPE: "; break;
			case MUL_FOCUS: strm << "MUL_FOCUS: "; break;
			case MUL_LOCKDOWN: strm << "MUL_LOCKDOWN: "; break;
			case MUL_SHELL: strm << "MUL_SHELL: "; break;
			case MUL_BOMBARD: strm << "MUL_BOMBARD: "; break;
			case MUL_MOVE_DEFENSE: strm << "MUL_MOVE_DEFENSE: "; break;
			case ATTACK_CHANCE: strm << "ATTACK_CHANCE: "; break;
		}
		strm << std::fixed << std::setprecision(3) << params[i] << "\n";
	}

	strm << "TileType values: " << std::hex;
	for (float x : tiletypes)
	{
		if (x < 0.0f) strm << "-";
		else if (x > 1.0f) strm << "+";
		else strm << (((int) (10.0f * x + 0.5f)) & 0xF);
	}
	strm << std::dec << "\n";

	strm << "UnitType values: ";
	for (float x : unittypes)
	{
		if (x < 0.0f) strm << "-";
		else if (x > 1.0f) strm << "+";
		else strm << (((int) (10.0f * x + 0.5f)) & 0xF);
	}
	strm << "\n";

	strm << "groundSubjectPreference:\n";
	for (const auto& row : groundSubjectPreference)
	{
		strm << "\t[" << std::hex;
		for (float x : row)
		{
			if (x < 0.0f) strm << "#";
			else if (x > 1.0f) strm << "@";
			else if (x < 0.2f) strm << "X";
			else if (x > 0.8f) strm << "O";
			else if (x < 0.4f) strm << "x";
			else if (x > 0.6f) strm << "o";
			else strm << " ";
		}
		strm << std::dec << "]\n";
	}

	strm << "tileSubjectPreference:\n";
	for (const auto& row : tileSubjectPreference)
	{
		strm << "\t[" << std::hex;
		for (float x : row)
		{
			if (x < 0.0f) strm << "#";
			else if (x > 1.0f) strm << "@";
			else if (x < 0.2f) strm << "X";
			else if (x > 0.8f) strm << "O";
			else if (x < 0.4f) strm << "x";
			else if (x > 0.6f) strm << "o";
			else strm << " ";
		}
		strm << std::dec << "]\n";
	}

	strm << "placementPreference:\n";
	for (const auto& row : placementPreference)
	{
		strm << "\t[" << std::hex;
		for (float x : row)
		{
			if (x < 0.0f) strm << "#";
			else if (x > 1.0f) strm << "@";
			else if (x < 0.2f) strm << "X";
			else if (x > 0.8f) strm << "O";
			else if (x < 0.4f) strm << "x";
			else if (x > 0.6f) strm << "o";
			else strm << " ";
		}
		strm << std::dec << "]\n";
	}

	return strm.str();
}
