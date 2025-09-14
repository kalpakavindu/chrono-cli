#include <iostream>

int main(int argc, const char* argv[]) {
  std::cout << "Argument count: " << argc;
  std::cout << "\nArguments:\n";
  for (int i = 0; i < argc; ++i) {
    std::cout << "  argv[" << i << "]: " << argv[i] << "\n";
  }

  return 0;
}