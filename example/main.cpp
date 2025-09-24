#include <iostream>

#include "src/Argument.hpp"
#include "src/CommandRegistry.hpp"

using namespace ChronoCLI;

class MyCommand : public Command {
 private:
  Argument arg1 = Argument("arg1", "", false, "Test argument 1");
  Argument arg2 = Argument("arg2", "a2", true, "Test argument 2");
  PositionalArgument arg3 = PositionalArgument("test_name", true, "Test name for the argument");

 public:
  MyCommand() : Command("test", "Test command") {
    RegisterArgument(arg1);
    RegisterArgument(arg2);
    RegisterArgument(arg3);
  }

  void Exec() override {
    std::cout << "Command completed:" << "\n";
    std::cout << arg1.getKeyName() << ": " << arg1.getValue<std::string>() << "\n";
    std::cout << arg2.getKeyName() << ": " << arg2.getValue<std::string>() << "\n";
    std::cout << arg3.getKeyName() << ": " << arg3.getValue<std::string>() << std::endl;
  }
};

int main(int argc, const char* argv[]) {
  try {
    MyCommand cmd1;

    CommandRegistry C;
    C.RegisterCommand(cmd1);

    C.Run(argc, argv);
  } catch (Exception& e) {
    e.print();
  }
}