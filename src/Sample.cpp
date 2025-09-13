#include "Sample.hpp"

#include <iostream>

#include "Colors.hpp"

using namespace ChronoCLI;

void ChronoCLI::printMessage(const std::string& msg) {
  std::cout << Colors::yellow << "Stream test: " << msg << Colors::reset << std::endl;

  std::cout << Colors::blue("String test: " + msg) << std::endl;
}