#include <iostream>

#include "engine.h"


int main(int argc, char **argv)
{
  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("Tutorial Window Name", 800, 600);
  int x =3;
  
  while (x != 0)
  {
      std::cout << "What mode would you like?\n0. Exit\n1. Planetary Observation\n2. Exploration Mode" << std::endl;
      std::cin >> x;
      switch (x)
      {
      case 0:
          break;
      case 1:
          if (!engine->Initialize(x))
          {
              printf("The engine failed to start.\n");
              delete engine;
              engine = NULL;
              return 1;
          }
          engine->Run();
          delete engine;
          engine = NULL;
          break;
      case 2:
          if (!engine->Initialize(x))
          {
              printf("The engine failed to start.\n");
              delete engine;
              engine = NULL;
              return 1;
          }
          engine->Run();
          delete engine;
          engine = NULL;
      default:
          std::cout << "Invalid value" << std::endl;
          break;
      }
  }

  return 0;
}
