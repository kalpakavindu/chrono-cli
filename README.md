# ChronoCLI

ChronoCLI is a modern, extensible C++ library for building command-line applications with support for commands, options, positional arguments, and in-built help messages.

## Features

- Define commands with arguments and positionals
- Required and optional argument support
- Global argument support
- In-built command help messages
- Type conversion for argument values
- Easy command extensibility via inheritance
- Extensible command registry

## Example Usage

See [`example/main.cpp`](example/main.cpp) for a complete sample.

### Command

> commands/MyCommand.hpp

```cpp
#include <iostream>

#include "chrono-cli/Command.hpp"
#include "chrono-cli/GlobalArgRegistry.hpp"

class MyCommand : public ChronoCLI::Command {
  // Define arguments
  ChronoCLI::Argument* arg1 = ChronoCLI::Argument::Required("test", "Test keyword argument", "t", "TEXT");
  ChronoCLI::Positional* pos1 = ChronoCLI::Positional::Optional(0, "Test positional", "TEXT");

 public:
  MyCommand() : ChronoCLI::Command("test", "Test command") {  // Command definition and argument registration
    RegisterArgument(arg1);
    RegisterArgument(pos1);
  }

  void Exec(const ChronoCLI::GlobalArgRegistry& gArgs) const override {  // Command execution function (your command logic)
    ChronoCLI::Argument* t2 = gArgs.findByKey("test2");                  // Accessing global arguments

    std::cout << "Test: " << arg1->getValue<std::string>() << std::endl;
    std::cout << "Test positional: " << pos1->getValue<std::string>() << std::endl;

    if (t2) {
      std::cout << "Global Test 2: " << t2->getValue<bool>() << std::endl;
    }
  }
};
```

### Custom Command Registry

> MyRegistry.hpp

```cpp
#include <iostream>

#include "chrono-cli/CommandRegistry.cpp"

#include "commands/MyCommand.hpp" // Test command above

class MyRegistry : public ChronoCLI::CommandRegistry {
  // Define global arguments
  ChronoCLI::Argument* gArg1 = ChronoCLI::Argument::Flag("test1", "Test global flag 1", "t1");
  ChronoCLI::Argument* gArg2 = ChronoCLI::Argument::Flag("test2", "Test global flag 2", "t2");

 public:
  MyRegistry() {  // Global argument and command registration
    RegisterGlobalArgument(gArg1);
    RegisterGlobalArgument(gArg2);

    RegisterCommand(new MyCommand());
  }

  int GlobalExec() const override {  // Main execution function (optional)
    if (gArg1->isSet()) {
      std::cout << "Test 1: " << gArg1->getValue<bool>() << std::endl;
      return 1;
    }

    if (gArg2->isSet()) {
      std::cout << "Test 2: " << gArg2->getValue<bool>() << std::endl;
      return 0;
    }

    return 0;
  }

  void AppVersion() const override {  // App version command (must define)
    std::cout << "v1.0.0" << std::endl;
  }
};
```

### Run application

> main.cpp

```cpp
#include "MyRegistry.hpp" // Test registry above

int main(int argc, const char* argv[]){
  MyRegistry().Run(argc, argv); // Run the registry
  return 0;
}
```

## Author

Developed by [kalpakavindu](https://kalpakavindu.vercel.app).
