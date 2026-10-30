#ifndef GAME_H
#define GAME_H

#include <string>

class GameState;

//abstractgame
class AbstractGame
{
public:
    AbstractGame(const std::string& name, const std::string& description, const std::string& ageRating);
    virtual ~AbstractGame();

    std::string getName() const;
    std::string getDescription() const;
    std::string getAgeRating() const;
    std::string getStateName() const;

    virtual GameState* getState() const = 0;
    virtual void setState(GameState* newState) = 0;

protected:
    std::string name;
    std::string description;
    std::string ageRating;
    GameState* state;
};

//game
class Game : public AbstractGame
{
public:
    Game(const std::string& name, const std::string& description, const std::string& ageRating);

    GameState* getState() const override;
    void setState(GameState* newState) override;

    void handleState();
    void retry();
    void release();
    void reviewWriting();
    void reviewAsset();
};

#endif
