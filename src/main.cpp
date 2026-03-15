#include "core/app.hpp"
#include <iostream>

int main(int argc, char *argv[]) {

  if (argc != 2) {
    std::cout << "Insira o nome do arquivo e nada mais." << std::endl;
    return 1;
  }

  std::string filename = argv[1];
  RunningOptions opts = RunningOptions{filename};
  App::run(opts);

  return 0;
}
