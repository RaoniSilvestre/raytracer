#include "core/app.hpp"

#include <iostream>

int main(int argc, char *argv[]) {

  if (argc < 2) {
    std::cout << "Insira o nome do arquivo e se quiser single core, a flag -m."
              << std::endl;
    return 1;
  }

  std::string filename = argv[1];
  RunningOptions opts;
  opts.input = filename;
  if (argc == 3) {
    std::string single_thread = argv[2];
    if (single_thread == "-s") {
      opts.singlethread = true;
    } else {
      opts.singlethread = false;
    }
  }

  App::run(opts);

  return 0;
}
