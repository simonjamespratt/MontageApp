#include "ProtocolControllerBroadcaster.h"

ProtocolControllerBroadcaster::ProtocolControllerBroadcaster()
{}

void ProtocolControllerBroadcaster::addListener(Listener listener)
{
    listeners.emplace_back(std::move(listener));
}

void ProtocolControllerBroadcaster::notify()
{
    for(auto const &listener : listeners) {
        listener();
    }
}
