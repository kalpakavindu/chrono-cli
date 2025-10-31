#pragma once
#ifndef CHRONOCLI_COMMAND_HPP
#define CHRONOCLI_COMMAND_HPP

#include <vector>

#include "Argument.hpp"
#include "GlobalArgRegistry.hpp"

namespace ChronoCLI {

  /**
   * @class ChronoCLI::Command
   * @brief Represents a command in the CLI application.
   */
  class Command {
   private:
    std::string m_name;
    std::string m_desc;

    std::map<std::string, Argument*> m_argMap;
    std::vector<Positional*> m_posVec;

   protected:
    /**
     * @brief Register an argument to the command.
     *
     * @param arg Pointer to the Argument to be registered.
     *
     * @throws ChronoCLI::Exception If an argument with the same key or shortkey already registered.
     */
    void RegisterArgument(Argument* arg);

    /**
     * @brief Register a positional argument to the command.
     *
     * @param arg Pointer to the Positional to be registered.
     *
     * @throws ChronoCLI::Exception If a positional argument with the same id already registered.
     */
    void RegisterArgument(Positional* arg);

   public:
    /**
     * @brief Populates the required members of Command class.
     *
     * @param name Name of the command.
     * @param description Description of the command.
     */
    Command(const std::string& name, const std::string& description) : m_name(name), m_desc(description) {}

    /**
     * @brief Get the name of the command.
     */
    std::string getName() const;

    /**
     * @brief Get the description of the command.
     */
    std::string getDesc() const;

    /**
     * @brief Set value to a registered argument by it's key or shortkey.
     *
     * This method returns `false` if the provided key or shortkey isn't registered.
     *
     * @param key Key or Shortkey of the argument to be set.
     * @param value String value for the argument.
     */
    bool setArgument(const std::string& key, const std::string& value = "");

    /**
     * @brief Set value to a registered positional argument by it's id.
     *
     * This method returns `false` if the provided id isn't registered.
     *
     * @param id Id of the positional argument.
     * @param value String value for the positional argument.
     */
    bool setPositional(unsigned int id, const std::string& value);

    /**
     * @brief Execution function of the command.
     *
     * This pure virtual function is the core of the command. Override this function to implement the logic of the command. Every exception thrown inside this method will be caught by the `ChronoCLI::CommandRegistry::Run()` method.
     *
     * @param globalArgs Reference to the GlobalArgRegistry to access global arguments.
     */
    virtual void Exec(GlobalArgRegistry globalArgs) const = 0;

    /**
     * @brief Display help information for the command.
     *
     * This is the `--help`,`-h` subcommand for this command. Override this to display your own help message for this command.
     *
     * @param appname Name of the executable used to trigger this function. Defaults to an empty string.
     */
    virtual void Help(const std::string& appname = "") const;

    /**
     * @brief Destructor of the command.
     *
     * This will deallocate all the registered arguments and positionals and clear the maps upon the destruction ensuring the memory safety.
     */
    ~Command();
  };

}  // namespace ChronoCLI

#endif