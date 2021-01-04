#include "ProtocolControllerBroadcaster.h"

void ProtocolControllerBroadcaster::addListener(
    std::shared_ptr<ProtocolControllerListener> listener)
{
    listeners.push_back(listener);
}

void ProtocolControllerBroadcaster::removeListener(
    std::shared_ptr<ProtocolControllerListener> listener)
{}
