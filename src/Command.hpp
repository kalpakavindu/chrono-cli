#pragma once
#ifndef CHRONOCLI_COMMAND_HPP
#define CHRONOCLI_COMMAND_HPP

#include <map>
#include <vector>

#include "Argument.hpp"

namespace ChronoCLI {

  /**
   * @brief Represents a command with its arguments and execution logic
   *
   * This is a base class that you should inherit to create your own commands.
   */
  class Command {
   private:
    std::map<std::string, Argument*> m_args;
    std::vector<PositionalArgument*> m_positionals;
    std::string m_name;
    std::string m_description;

   protected:
    /**
     * @brief Register a new argument with the command
     * @param arg The argument to register
     */
    void RegisterArgument(Argument& arg);

    /**
     * @brief Register a new positional argument with the command
     * @param arg The positional argument to register
     */
    void RegisterArgument(PositionalArgument& arg);

   public:
    /**
     * @brief Construct a new Command object
     * @param name The name of the command
     * @param description A brief description of the command
     */
    Command(const std::string& name, const std::string& description) : m_name(name), m_description(description) {}

    /**
     * @brief Get the command name
     */
    const std::string& getName() const { return m_name; }

    /**
     * @brief Get the command description
     */
    const std::string& getDesc() const { return m_description; }

    /**
     * @brief Get a map of pointers for the registered arguments
     */
    const std::map<std::string, Argument*>& getArgs() { return m_args; }

    /**
     * @brief Get a map of pointers for the registered positional arguments
     */
    const std::vector<PositionalArgument*>& getPositionalArgs() { return m_positionals; }

    /**
     * @brief Print help information for the command
     * @param appname The name of the application
     *
     * This is a virtual function that can be override for customize the help information of the command.
     */
    virtual void Help(const std::string& appname) const;

    /**
     * @brief Execute the command action
     *
     * This is a pure virtual function that must be implemented by your custom commands.
     */
    virtual void Exec() = 0;
  };

}  // namespace ChronoCLI

#endif