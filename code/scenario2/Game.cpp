#include "Game.h"
#include "GameState.h"

#include <iostream>

//abstractgame
AbstractGame::AbstractGame(const std::string& name, const std::string& description, const std::string& ageRating)
    : name(name), description(description), ageRating(ageRating), state(new Concepting())
{
}

AbstractGame::~AbstractGame()
{
    delete state;
}

std::string AbstractGame::getName() const
{
    return name;
}

std::string AbstractGame::getDescription() const
{
    return description;
}

std::string AbstractGame::getAgeRating() const
{
    return ageRating;
}

std::string AbstractGame::getStateName() const
{
    return state->getName();
}

//game
Game::Game(const std::string& name, const std::string& description, const std::string& ageRating)
    : AbstractGame(name, description, ageRating)
{
}

GameState* Game::getState() const
{
    return state;
}

void Game::setState(GameState* newState)
{
    if (newState == nullptr)
    {
        return;
    }
    std::cout << "  [State] " << name << ": " << state->getName() << " -> " << newState->getName() << std::endl;
    GameState* old = state;
    state = newState;
    delete old;
}

void Game::handleState()
{
    state->nextState(this);
}

void Game::retry()
{
    state->retry(this);
}

void Game::release()
{
    state->release(this);
}

void Game::reviewWriting()
{
    state->reviewWriting(this);
}

void Game::reviewAsset()
{
    state->reviewAsset(this);
}
