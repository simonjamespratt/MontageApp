#include "DurationProtocolController.h"

#include "GeometricProtocolController.h"
#include "MultiplesProtocolController.h"
#include "PrescribedProtocolController.h"

#include <stdexcept>

std::unique_ptr<DurationProtocolController>
DurationProtocolController::create(Type type)
{
    switch(type) {
    case Type::geometric:
        return std::make_unique<GeometricProtocolController>();
        break;
    case Type::multiples:
        return std::make_unique<MultiplesProtocolController>();
        break;
    case Type::prescribed:
        return std::make_unique<PrescribedProtocolController>();
        break;

    default:
        throw std::invalid_argument("Type not recognised");
    }
}
