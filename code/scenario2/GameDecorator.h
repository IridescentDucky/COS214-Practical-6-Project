#ifndef GAMEDECORATOR_H
#define GAMEDECORATOR_H

#include "FileSystemComponent.h"


class GameDecorator : public FileSystemComponent {

protected:
    FileSystemComponent* component;

public:
    GameDecorator(FileSystemComponent* component);
    virtual ~GameDecorator();
    virtual int getScore();
    virtual int getTime();

};


#endif