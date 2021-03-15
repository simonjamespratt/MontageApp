#include "SubsetProtocolController.h"

SubsetProtocolController::SubsetProtocolController(
    aleatoric::NumberProtocolParams initialParams)
{
    setParams(initialParams);
}

void SubsetProtocolController::setParams(aleatoric::NumberProtocolParams params)
{
    jassert(params.getActiveProtocol() ==
            aleatoric::NumberProtocol::Type::subset);

    auto subsetParams = params.getSubset();
    min = subsetParams.getMin();
    max = subsetParams.getMax();
}

aleatoric::NumberProtocolParams SubsetProtocolController::getParams()
{
    // TODO: delete this
    DBG("min: " << min);
    DBG("max: " << max);

    return aleatoric::NumberProtocolParams(aleatoric::SubsetParams(min, max));
}

void SubsetProtocolController::resized()
{}
