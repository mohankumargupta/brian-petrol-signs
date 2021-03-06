#pragma once

#include "command.h"

class Test7Command : public Command
{
  public:
    void execute(DMD3 *canvas)  override {
      clearSerialMonitor();
      canvas->clear();
      canvas->drawChar(0,0, 'Q');
      printCanvas(canvas);
      canvas->update();
    }
};
