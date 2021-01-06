#pragma once

class ProtocolControllerListener {
  public:
    virtual ~ProtocolControllerListener() = default;
    virtual void update() = 0;

  protected:
    ProtocolControllerListener();
};
