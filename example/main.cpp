#include <iostream>

#include "src/ArgumentParser.hpp"
#include "src/Exception.hpp"

using namespace ChronoCLI;

int main(int argc, const char* argv[]) {
  try {
    ArgumentParser parser(argc, argv);
    std::list<std::string> l = parser.GetGlobalList<std::string>("--test", ",");
    for (std::string& x : l) {
      std::cout << x << std::endl;
    }
  } catch (Exception& e) {
    e.print();
  }
  return 0;
}