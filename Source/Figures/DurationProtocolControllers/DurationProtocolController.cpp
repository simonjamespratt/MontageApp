#include "DurationProtocolController.h"

#include "GeometricProtocolController.h"
#include "MultiplesProtocolController.h"
#include "PrescribedProtocolController.h"

#include <stdexcept>

std::unique_ptr<DurationProtocolController>
DurationProtocolController::create(Type type, DurationProtocolParams &params)
{
    switch(type) {
    case Type::geometric:
        return std::make_unique<GeometricProtocolController>(params);
        break;
    case Type::multiples:
        return std::make_unique<MultiplesProtocolController>(params);
        break;
    case Type::prescribed:
        return std::make_unique<PrescribedProtocolController>(params);
        break;

    default:
        throw std::invalid_argument("Type not recognised");
    }
}
