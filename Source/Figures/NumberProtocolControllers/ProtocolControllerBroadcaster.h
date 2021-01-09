#pragma once

#include <functional>
#include <vector>

// TODO: check best practice for making this an "interface", i.e. cannot be
// instantiated directly, seeing as it doesn't have any pure virtual functions
class ProtocolControllerBroadcaster {
    using Listener = std::function<void()>;

  public:
    virtual ~ProtocolControllerBroadcaster() = default;
    void addListener(Listener listener);
    // TODO: reinstate this
    // virtual void removeListener();
    void notify();

  protected:
    ProtocolControllerBroadcaster();

  private:
    std::vector<Listener> listeners;
};
