#include <iostream>

#include "src/Exception.hpp"

using namespace ChronoCLI;

int main(int argc, const char* argv[]) {
  try {
    // throw ParserError::TypeConvertError("abc", typeid(int).name());
    // throw CommandError::InvalidArgument("filename", "must be a valid path");
    throw Exception("Test error");
  } catch (ParserError::ParserError& e) {
    e.print();
  } catch (CommandError::CommandError& e) {
    e.print();
  } catch (Exception& e) {
    e.print();
  }
  return 0;
}