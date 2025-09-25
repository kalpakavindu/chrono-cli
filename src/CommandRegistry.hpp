#pragma once
#ifndef CHRONOCLI_COMMANDREGISTRY_HPP
#define CHRONOCLI_COMMANDREGISTRY_HPP

#include "Command.hpp"

namespace ChronoCLI {

  /**
   * @brief Manages the registration and execution of commands
   *
   * This class allows you to register multiple commands and execute them based on user input.
   */
  class CommandRegistry {
   private:
    std::map<std::string, Command*> m_commands;
    void m_Help(const std::string& appname) const;

   public:
    /**
     * @brief Register a new command
     * @param cmd The command to register
     */
    void RegisterCommand(Command& cmd);

    /**
     * @brief Run the command line parser and execute the appropriate command
     * @param argc The argument count from main()
     * @param argv The argument vector from main()
     * @throws CommandError::UnknownCommand if the specified command is not registered
     * @throws CommandError::MissingArgument if a required argument is missing
     * @throws CommandError::CommandError if no command were specified by the user and no help option was given
     * @throws Exception if no commands were registered
     */
    void Run(int argc, const char* argv[]);
  };

}  // namespace ChronoCLI

#endif