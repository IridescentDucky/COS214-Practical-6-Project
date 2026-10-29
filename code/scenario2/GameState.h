#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>

class Game;

//gamestate
class GameState
{
public:
    virtual ~GameState()
    {
    }
    virtual std::string getName() const = 0;
    virtual GameState* clone() const = 0;

    virtual void nextState(Game* game);
    virtual void retry(Game* game);
    virtual void release(Game* game);
    virtual void reviewWriting(Game* game);
    virtual void reviewAsset(Game* game);

protected:
    void reject(const std::string& operation) const;
};

//concepting
class Concepting : public GameState
{
public:
    std::string getName() const override;
    GameState* clone() const override;
    void nextState(Game* game) override;
};

//writing
class Writing : public GameState
{
public:
    std::string getName() const override;
    GameState* clone() const override;
    void nextState(Game* game) override;
};

//assetbuilding
class AssetBuilding : public GameState
{
public:
    std::string getName() const override;
    GameState* clone() const override;
    void nextState(Game* game) override;
};

//coding
class Coding : public GameState
{
public:
    std::string getName() const override;
    GameState* clone() const override;
    void nextState(Game* game) override;
};

//validate
class Validate : public GameState
{
public:
    std::string getName() const override;
    GameState* clone() const override;
    void nextState(Game* game) override;
    void retry(Game* game) override;
    void release(Game* game) override;
    void reviewWriting(Game* game) override;
    void reviewAsset(Game* game) override;
};

//review
class Review : public GameState
{
public:
    std::string getName() const override;
    GameState* clone() const override;
    void nextState(Game* game) override;
};

//release
class Release : public GameState
{
public:
    std::string getName() const override;
    GameState* clone() const override;
};

#endif
