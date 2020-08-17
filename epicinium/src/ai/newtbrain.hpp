#pragma once
#include "header.hpp"

#include "tiletype.hpp"
#include "unittype.hpp"
#include "position.hpp"

class AICommander;


class NewtBrain
{
public:
	struct Output
	{
		enum Parameter : uint8_t
		{
			WEIGHT_MONEY,
			WEIGHT_ISTARGET,
			WEIGHT_OCCUPIED,
			WEIGHT_OVERLAP,
			MUL_SETTLE,
			MUL_MOVE_SETTLER,
			MUL_PRODUCE,
			MUL_EXPAND,
			MUL_CULTIVATE,
			MUL_UPGRADE,
			MUL_CAPTURE,
			MUL_SHAPE,
			MUL_FOCUS,
			MUL_LOCKDOWN,
			MUL_SHELL,
			MUL_BOMBARD,
			MUL_MOVE_DEFENSE,
			ATTACK_CHANCE,
		};

		static constexpr size_t PARAMETER_SIZE = ATTACK_CHANCE + 1;

		std::array<float, PARAMETER_SIZE> params;

		std::array<float, TILETYPE_SIZE> tiletypes;
		std::array<float, UNITTYPE_SIZE> unittypes;

		std::array<std::array<float, Position::MAX_COLS>, Position::MAX_ROWS>
			groundSubjectPreference;
		std::array<std::array<float, Position::MAX_COLS>, Position::MAX_ROWS>
			tileSubjectPreference;
		std::array<std::array<float, Position::MAX_COLS>, Position::MAX_ROWS>
			placementPreference;

		static constexpr size_t SIZE = PARAMETER_SIZE
			+ TILETYPE_SIZE + UNITTYPE_SIZE
			+ Position::MAX_COLS * Position::MAX_ROWS
			+ Position::MAX_COLS * Position::MAX_ROWS
			+ Position::MAX_COLS * Position::MAX_ROWS;

		void assign(const std::vector<float>& output);

		std::string toPrettyString() const;
	};

	NewtBrain() = default;
	NewtBrain(const NewtBrain&) = delete;
	NewtBrain(NewtBrain&&) = delete;
	NewtBrain& operator=(const NewtBrain&) = delete;
	NewtBrain& operator=(NewtBrain&&) = delete;
	virtual ~NewtBrain() = default;

	virtual void prepare(const AICommander& input) = 0;
	virtual Output evaluate() = 0;
};
