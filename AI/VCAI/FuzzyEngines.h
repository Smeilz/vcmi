/*
* FuzzyEngines.h, part of VCMI engine
*
* Authors: listed in file AUTHORS in main folder
*
* License: GNU General Public License v2.0 or later
* Full text of license available in license.txt file, in main folder
*
*/
#pragma once
#include "fl/Headers.h"
#include "Goals.h"

class CArmedInstance;

class engineBase //subclasses create fuzzylite variables with "new" that are not freed - this is desired as fl::Engine wants to destroy these...
{
protected:
	fl::Engine engine;
	fl::RuleBlock rules;
	virtual void configure();
	void addRule(const std::string & txt);
public:
	engineBase();
};

class TacticalAdvantageEngine : public engineBase
{
public:
	TacticalAdvantageEngine();
	float getTacticalAdvantage(const CArmedInstance * we, const CArmedInstance * enemy); //returns factor how many times enemy is stronger than us
private:
	fl::InputVariable * ourWalkers, *ourShooters, *ourFlyers, *enemyWalkers, *enemyShooters, *enemyFlyers;
	fl::InputVariable * ourSpeed, *enemySpeed;
	fl::InputVariable * bankPresent;
	fl::InputVariable * castleWalls;
	fl::OutputVariable * threat;
};

class HeroMovementGoalEngineBase : public engineBase //in future - maybe derive from some (GoalEngineBase : public engineBase) class for handling non-movement goals with common utility for goal engines
{
public:
	HeroMovementGoalEngineBase();

	virtual float evaluate(Goals::AbstractGoal & goal) = 0;

protected:
	void setSharedFuzzyVariables(Goals::AbstractGoal & goal);

	fl::InputVariable * strengthRatio;
	fl::InputVariable * heroStrength;
	fl::InputVariable * turnDistance;
	fl::InputVariable * missionImportance;
	fl::OutputVariable * value;

private:
	float calculateTurnDistanceInputValue(const CGHeroInstance * h, int3 tile) const;
};

class VisitTileEngine : public HeroMovementGoalEngineBase
{
public:
	VisitTileEngine();
	float evaluate(Goals::AbstractGoal & goal) override;
};

class GetObjEngine : public HeroMovementGoalEngineBase
{
public:
	GetObjEngine();
	float evaluate(Goals::AbstractGoal & goal) override;
protected:
	fl::InputVariable * objectValue;
};