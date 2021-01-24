#include "NumberProtocolController.h"

#include "AdjacentStepsProtocolController.h"
#include "BasicProtocolController.h"
#include "CycleProtocolController.h"

#include <stdexcept>

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

std::unique_ptr<NumberProtocolController>
NumberProtocolController::create(Type type, Params params)
{
    switch(type) {
    case Type::adjacentSteps:
        return std::make_unique<AdjacentStepsProtocolController>();
        break;
    case Type::basic:
        return std::make_unique<BasicProtocolController>();
        break;
    case Type::cycle:
        return std::make_unique<CycleProtocolController>(params);
        break;

    default:
        throw std::invalid_argument("Type not recognised");
    }
}