#include <iostream>

#include "engine.h"


int main(int argc, char **argv)
{
  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("Tutorial Window Name", 800, 600);
  srand(time(0));
  int x =3;
  

      std::cout << "Would you like to play?\n0. Exit\n1. Play" << std::endl;
      std::cin >> x;
      switch (x)
      {
      case 0:
          break;
      case 1:
          if (!engine->Initialize())
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
  

  return 0;
}
