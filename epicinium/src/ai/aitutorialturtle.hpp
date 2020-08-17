#pragma once
#include "header.hpp"

#include "airampantrhino.hpp"
#include "descriptor.hpp"


class AITutorialTurtle : public AIRampantRhino
{
public:
	using AIRampantRhino::AIRampantRhino;

private:
	virtual int maxOrders() override;
	virtual int maxMilitaryOrders() override;
	virtual int maxMilitaryUnits() override;
	virtual int maxDefenseUnits() override;
	virtual int maxCaptures() override;
	virtual int maxBombardments() override;

protected:
	virtual std::string ainame() const override;
	virtual std::string authors() const override;
};
