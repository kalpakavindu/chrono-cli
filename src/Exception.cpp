#include "Exception.hpp"

#include <iostream>

using namespace ChronoCLI;

void Exception::print() const {
  std::cout << "[ERROR] " << what() << "\nUse --help for usage information." << std::endl;
}