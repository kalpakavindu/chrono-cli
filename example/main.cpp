#include <iostream>

#include "src/Argument.hpp"
#include "src/Command.hpp"
#include "src/CommandRegistry.hpp"

using namespace ChronoCLI;

class MyCommand : public Command {
  // Define arguments
  Argument* arg1 = Argument::Required("test", "Test keyword argument", "t", "TEXT", "default value for test");
  Positional* pos1 = Positional::Optional(0, "Test positional", "TEXT");

 public:
  MyCommand() : Command("test", "Test command") {  // Command definition and argument registration
    RegisterArgument(arg1);
    RegisterArgument(pos1);
  }

  void Exec(GlobalArgRegistry gArgs) const override {  // Command execution function (your command logic)
    Argument* t2 = gArgs.findByKey("-t2");             // Accessing global arguments

    std::cout << "Test: " << arg1->getValue<std::string>() << std::endl;
    std::cout << "Test positional: " << pos1->getValue<std::string>() << std::endl;

    if (t2 != nullptr) {
      std::cout << "Global Test 2: " << t2->getValue<std::string>() << std::endl;
    }
  }
};

class MyRegistry : public CommandRegistry {
  // Define global arguments
  Argument* gArg1 = Argument::Flag("test1", "Test global flag 1", "t1");
  Argument* gArg2 = Argument::Optional("test2", "Test global flag 2", "t2", "TEXT");

 public:
  MyRegistry() {  // Global argument and command registration
    RegisterGlobalArgument(gArg1);
    RegisterGlobalArgument(gArg2);

    RegisterCommand(new MyCommand());
  }

  int GlobalExec() const override {  // Main execution function (optional)
    if (gArg1->isSet()) {
      std::cout << "Global test 1: " << gArg1->getValue<bool>() << std::endl;
      return 1;
    }

    if (gArg2->isSet()) {
      std::cout << "Global test 2: " << gArg2->getValue<std::string>() << std::endl;
      return 0;
    }

    return 0;
  }

  void AppVersion() const override {  // App version command (must defined)
    std::cout << "v1.0.0" << std::endl;
  }
};

int main(int argc, const char* argv[]) {
  MyRegistry().Run(argc, argv);  // Run the registry
}