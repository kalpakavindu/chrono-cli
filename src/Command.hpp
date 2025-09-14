#ifndef CHRONOCLI_COMMAND_HPP
#define CHRONOCLI_COMMAND_HPP

#include <vector>

#include "Argument.hpp"
#include "ArgumentParser.hpp"

namespace ChronoCLI {

  class Command {
   protected:
    std::string m_name;
    std::string m_description;
    std::vector<Argument*> m_args;

   public:
    const std::string& GetName() const { return m_name; }

    virtual void Exec(const ArgumentParser& parser) = 0;
    virtual void Help() const = 0;
  };

}  // namespace ChronoCLI

#endif