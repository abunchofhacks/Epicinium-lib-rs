#pragma once
#include "header.hpp"

#include "aicommander.hpp"
#include "descriptor.hpp"
#include "position.hpp"
#include "newtbrain.hpp"
#include "pathingfloodfill.hpp"


class AINeuralNewt : public AICommander
{
public:
	AINeuralNewt(const Player& player, const Difficulty& difficulty,
		const std::string& rulesetname, char character,
		std::shared_ptr<NewtBrain> brain);
	AINeuralNewt(const Player& player, const Difficulty& difficulty,
		const std::string& rulesetname, char character);
	AINeuralNewt(const AINeuralNewt&) = delete;
	AINeuralNewt(AINeuralNewt&&) = delete;
	AINeuralNewt& operator=(const AINeuralNewt&) = delete;
	AINeuralNewt& operator=(AINeuralNewt&&) = delete;
	virtual ~AINeuralNewt() = default;

private:
	TileFloodfill _ownBaseFloodfill;
	TileFloodfill _enemyBaseFloodfill;
	std::vector<PathingFloodfill> _pathingFloodfillCache; // (married)
	std::vector<Descriptor> _pathingFloodfillUses; // (married)

	std::shared_ptr<NewtBrain> _brain;
	NewtBrain::Output _evaluation;

	std::vector<Descriptor> _settlers;
	std::vector<Descriptor> _defenses;
	std::vector<Descriptor> _offenses;
	std::vector<Descriptor> _captors;
	std::vector<Descriptor> _blockers;
	std::vector<Descriptor> _bombarders;
	std::vector<Descriptor> _creators;
	std::vector<Descriptor> _expanders;
	std::vector<Descriptor> _cultivators;
	std::vector<Descriptor> _upgraders;
	std::vector<Descriptor> _stoppers;
	std::vector<Position> _targets;

	int _moneyleftover;

	void count();

	void lookAtUnfinishedOrder(const Order& order);

	PathingFloodfill& getExecutedPathingFloodfill(Cell from,
		const Descriptor& descriptor);

	void filterSubjects(std::vector<Descriptor>& subjects);
	void sortSubjects(std::vector<Descriptor>& subjects);

	void controlSettler(const Descriptor& desc,
		Order& bestOrder, int& bestOrderCost, Descriptor& bestOrderTarget,
		float& bestOrderScore);
	void controlCaptor(const Descriptor& desc,
		Order& bestOrder, int& bestOrderCost, Descriptor& bestOrderTarget,
		float& bestOrderScore);
	void controlCombatant(const Descriptor& desc,
		Order& bestOrder, int& bestOrderCost, Descriptor& bestOrderTarget,
		float& bestOrderScore);
	void controlBombarder(const Descriptor& desc,
		Order& bestOrder, int& bestOrderCost, Descriptor& bestOrderTarget,
		float& bestOrderScore);
	void moveDefense(const Descriptor& desc,
		Order& bestOrder, int& bestOrderCost, Descriptor& bestOrderTarget,
		float& bestOrderScore);
	void controlCreator(const Descriptor& desc,
		Order& bestOrder, int& bestOrderCost, Descriptor& bestOrderTarget,
		float& bestOrderScore);
	void controlExpander(const Descriptor& desc,
		Order& bestOrder, int& bestOrderCost, Descriptor& bestOrderTarget,
		float& bestOrderScore);
	void controlCultivator(const Descriptor& desc,
		Order& bestOrder, int& bestOrderCost, Descriptor& bestOrderTarget,
		float& bestOrderScore);
	void controlUpgrader(const Descriptor& desc,
		Order& bestOrder, int& bestOrderCost, Descriptor& bestOrderTarget,
		float& bestOrderScore);
	void controlStopper(const Descriptor& desc,
		Order& bestOrder, int& bestOrderCost, Descriptor& bestOrderTarget,
		float& bestOrderScore);

	void moveUnit(const Descriptor& desc,
		const PathingFloodfill& pathing,
		const Cell& from, const Cell& target, float targetScore,
		Order& bestOrder, int& bestOrderCost, Descriptor& bestOrderTarget,
		float& bestOrderScore);

	bool isTarget(const Position& position);
	bool hasOldOrder(const Descriptor& desc);
	bool hasNewOrder(const Descriptor& desc);
	bool isAdjacentToEnemyCombatant(const Descriptor& desc);
	bool isOccupied(const Position& position);

	int expectedSoil(Cell index);
	int expectedNiceness(Cell index);
	int expectedOverlap(Cell index);

protected:
	virtual std::string ainame() const override;
	virtual std::string authors() const override;

public:
	virtual void preprocess() override;
	virtual void process() override;
	virtual bool postprocess() override;
};

class DummyNewtBrain : public NewtBrain
{
public:
	DummyNewtBrain() = default;
	DummyNewtBrain(const DummyNewtBrain&) = delete;
	DummyNewtBrain(DummyNewtBrain&&) = delete;
	DummyNewtBrain& operator=(const DummyNewtBrain&) = delete;
	DummyNewtBrain& operator=(DummyNewtBrain&&) = delete;
	virtual ~DummyNewtBrain() = default;

	virtual void prepare(const AICommander& /**/) override {}
	virtual Output evaluate() override;
};
