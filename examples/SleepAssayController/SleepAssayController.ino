#include <SleepAssayController.h>


SleepAssayController dev;

void setup()
{
  dev.setup();
  dev.startServer();
}

void loop()
{
  dev.update();
}
