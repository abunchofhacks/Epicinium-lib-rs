#pragma once
#include "header.hpp"

#include "airampantrhino.hpp"
#include "descriptor.hpp"


class AIBrawlingBear : public AIRampantRhino
{
public:
	using AIRampantRhino::AIRampantRhino;

private:
	virtual int maxOrders() override;
	virtual int maxMilitaryOrders() override;
	virtual int maxMilitaryUnits() override;
	virtual int maxDefenseUnits() override;
	virtual int maxBombardments() override;
	virtual int maxCaptures() override;

	virtual bool canUseCombatAbilities() override;
	virtual bool canBuildBarracks() override;
	virtual bool canBuildCities() override;

protected:
	virtual std::string ainame() const override;
	virtual std::string authors() const override;
};
