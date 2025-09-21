#include <iostream>

#include "src/Argument.hpp"
#include "src/CommandRegistry.hpp"
#include "src/Exception.hpp"

using namespace ChronoCLI;

class MyCommand : public Command {
 private:
  Argument arg1 = Argument("--arg");

 public:
  MyCommand() : Command("test", "Test command") {
    RegisterArgument(arg1);
  }

  void Exec() override {
    std::cout << "Command completed: " << arg1.GetValue<std::string>() << std::endl;
  }

  void Help() override {
    std::cout << "This is a help message for test command." << std::endl;
  }
};

int main(int argc, const char* argv[]) {
  MyCommand cmd;

  CommandRegistry cli;
  cli.RegisterCommand(cmd);
  cli.Run(argc, argv);
}