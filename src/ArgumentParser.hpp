#ifndef CHRONOCLI_ARGUMENTPARSER_HPP
#define CHRONOCLI_ARGUMENTPARSER_HPP

namespace ChronoCLI {

  class ArgumentParser {
   public:
    void Parse(int argc, char* argv[]);
  };

}  // namespace ChronoCLI

#endif