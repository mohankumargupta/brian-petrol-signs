#pragma once

#include "command.h"

class Test4Command : public Command
{
  public:
    void execute(DMD3 *canvas)  override {
      clearSerialMonitor();
      canvas->clear();
      canvas->setPixel(0,15);
      printCanvas(canvas);
      canvas->update();
    }
};
