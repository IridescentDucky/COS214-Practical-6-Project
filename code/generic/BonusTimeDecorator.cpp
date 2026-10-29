#include "BonusTimeDecorator.h"

BonusTimeDecorator::BonusTimeDecorator(Component* component, int extraTime): Decorator(component), extraTime(extraTime) {

}

int BonusTimeDecorator::getTime() {

    return component->getTime() + extraTime;
}