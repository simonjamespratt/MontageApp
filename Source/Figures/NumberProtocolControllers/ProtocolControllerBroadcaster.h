#pragma once

#include "ProtocolControllerListener.h"

#include <memory>
#include <vector>

class ProtocolControllerBroadcaster {
  public:
    virtual ~ProtocolControllerBroadcaster() = default;

    virtual void
    addListener(std::shared_ptr<ProtocolControllerListener> listener);

    virtual void
    removeListener(std::shared_ptr<ProtocolControllerListener> listener);

    virtual void notify();

  protected:
    ProtocolControllerBroadcaster();

  private:
    std::vector<std::shared_ptr<ProtocolControllerListener>> listeners;
};
