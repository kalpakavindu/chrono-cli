#include <iostream>

#include "src/Argument.hpp"
#include "src/Exception.hpp"

using namespace ChronoCLI;

// class MyCommand : public Command {
//  private:
//   Argument arg1 = Argument("--arg");

//  public:
//   MyCommand() : Command("test", "Test command") {
//     RegisterArgument(arg1);
//   }

//   void Exec() override {
//     std::cout << "Command completed: " << arg1.GetValue<std::string>() << std::endl;
//   }

//   void Help() override {
//     std::cout << "This is a help message for test command." << std::endl;
//   }
// };

int main(int argc, const char* argv[]) {
  try {
    PositionalArgument positionalArg("positional", true, "Instance of `PositionalArgument` class");

    std::cout << positionalArg.IsRequired() << std::endl;

  } catch (Exception& e) {
    e.print();
  }
}