#include "GameState.h"
#include "Game.h"

#include <iostream>

//gamestate
void GameState::reject(const std::string& operation) const
{
    std::cout << "  [State] '" << operation << "' is not allowed while " << getName() << std::endl;
}

void GameState::nextState(Game*)
{
    reject("nextState");
}

void GameState::retry(Game*)
{
    reject("retry");
}

void GameState::release(Game*)
{
    reject("release");
}

void GameState::reviewWriting(Game*)
{
    reject("reviewWriting");
}

void GameState::reviewAsset(Game*)
{
    reject("reviewAsset");
}

//concepting
std::string Concepting::getName() const
{
    return "Concepting";
}

GameState* Concepting::clone() const
{
    return new Concepting();
}

void Concepting::nextState(Game* game)
{
    game->setState(new Writing());
}

//writing
std::string Writing::getName() const
{
    return "Writing";
}

GameState* Writing::clone() const
{
    return new Writing();
}

void Writing::nextState(Game* game)
{
    game->setState(new AssetBuilding());
}

//assetbuilding
std::string AssetBuilding::getName() const
{
    return "AssetBuilding";
}

GameState* AssetBuilding::clone() const
{
    return new AssetBuilding();
}

void AssetBuilding::nextState(Game* game)
{
    game->setState(new Coding());
}

//coding
std::string Coding::getName() const
{
    return "Coding";
}

GameState* Coding::clone() const
{
    return new Coding();
}

void Coding::nextState(Game* game)
{
    game->setState(new Validate());
}

//validate
std::string Validate::getName() const
{
    return "Validate";
}

GameState* Validate::clone() const
{
    return new Validate();
}

void Validate::nextState(Game* game)
{
    game->setState(new Review());
}

void Validate::retry(Game* game)
{
    game->setState(new Coding());
}

void Validate::release(Game* game)
{
    game->setState(new Release());
}

void Validate::reviewWriting(Game* game)
{
    game->setState(new Writing());
}

void Validate::reviewAsset(Game* game)
{
    game->setState(new AssetBuilding());
}

//review
std::string Review::getName() const
{
    return "Review";
}

GameState* Review::clone() const
{
    return new Review();
}

void Review::nextState(Game* game)
{
    game->setState(new Release());
}

//release
std::string Release::getName() const
{
    return "Release";
}

GameState* Release::clone() const
{
    return new Release();
}
