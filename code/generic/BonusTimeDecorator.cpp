#include "BonusTimeDecorator.h"

template <typename T>
BonusTimeDecorator<T>::BonusTimeDecorator(Component<T>* component, int extraTime): Decorator<T>(component), extraTime(extraTime) {

}

template <typename T>
int BonusTimeDecorator<T>::getTime() {

    return this->component->getTime() + this->extraTime;
}

template class BonusTimeDecorator<int>;
