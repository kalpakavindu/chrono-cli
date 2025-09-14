#include "Exception.hpp"

#include <iostream>

using namespace ChronoCLI;

void Exception::print() const {
  std::cout << "[ERROR] " << what() << std::endl;
}

void CommandError::CommandError::print() const {
  std::cout << what() << "\nUse --help for usage information." << std::endl;
}

void ParserError::ParserError::print() const {
  std::cout << "[ERROR] " << what() << std::endl;
}