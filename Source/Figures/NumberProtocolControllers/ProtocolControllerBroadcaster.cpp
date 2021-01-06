#include "ProtocolControllerBroadcaster.h"

ProtocolControllerBroadcaster::ProtocolControllerBroadcaster()
{}

void ProtocolControllerBroadcaster::addListener(Listener listener)
{
    listeners.push_back(listener);
}

void ProtocolControllerBroadcaster::notify()
{
    for(auto &listener : listeners) {
        listener();
    }
}
