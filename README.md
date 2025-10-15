# ChronoCLI

ChronoCLI is a modern, extensible C++ library for building command-line applications with support for commands, options, positional arguments, and automatic help generation.

## Features

- Define commands with arguments and positionals
- In-built command help messages
- Custom exception hierarchy for robust error handling
- Type conversion for argument values
- Required and optional argument support
- Easy command extensibility via inheritance

## Example Usage

See [`example/main.cpp`](example/main.cpp) for a complete sample.

```cpp
#include <chrono-cli/Command.hpp>
#include <chrono-cli/CommandRegistry.hpp>
#include <chrono-cli/Argument.hpp>

class MyCommand : public ChronoCLI::Command {
    ChronoCLI::Argument arg = ChronoCLI::Argument("--file", "-f", true, "Input file");

public:
    MyCommand() : Command("test", "A test command") {
        RegisterArgument(arg);
    }

    void Exec() override {
        std::string filename = arg.getValue<std::string>();
        std::cout << "Processing file: " << filename << std::endl;
    }
};

int main(int argc, const char* argv[]) {
    try{
        MyCommand cmd;

        ChronoCLI::CommandRegistry registry;
        registry.RegisterCommand(cmd);
        registry.Run(argc, argv);
        
    }catch(Exception& e){
        e.print();
    }

    return 0;
}
```

## Author

Developed by [kalpakavindu](https://kalpakavindu.vercel.app).
