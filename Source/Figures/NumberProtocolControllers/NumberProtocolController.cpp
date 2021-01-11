#include "NumberProtocolController.h"

void NumberProtocolController::attach(Observer observer)
{
    observers.emplace_back(observer);
}

void NumberProtocolController::notifyParamsChanged()
{
    auto newParams = getParams();
    for(auto const &observer : observers) {
        observer(newParams);
    }
}
