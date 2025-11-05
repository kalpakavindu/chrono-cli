#pragma once
#ifndef CHRONOCLI_COMMANDREGISTRY_HPP
#define CHRONOCLI_COMMANDREGISTRY_HPP

#include "Command.hpp"

namespace ChronoCLI {

  class CommandRegistry {
   private:
    std::map<std::string, Command*> m_cmdMap;
    GlobalArgBase m_gArgs;

   protected:
    /**
     * @brief Register Command
     *
     * @param cmd Pointer to the command to be registered.
     *
     * @throws ChronoCLI::Exception If a Command with the same name already registered.
     */
    void RegisterCommand(Command* cmd);

    /**
     * @brief Register global Argument
     *
     * Only optional keyword arguments or flags can be provided. Positionals not allowed here.
     *
     * @param arg Pointer to the Argument to be registered.
     *
     * @throws ChronoCLI::Exception If the argument is required or an argument with same key or shortkey already registered.
     */
    void RegisterGlobalArgument(Argument* arg);

    /**
     * @brief Display global help information.
     *
     * This is the `--help`,`-h` subcommand. Override this to display your own help message.
     *
     * @param appname Name of the executable used to trigger this function.
     */
    virtual void Help(const std::string& appname) const;

    /**
     * @brief Display application version information.
     *
     * This pure virtual function is the `--version`,`-v` subcommand. Must override for display the version of your app.
     */
    virtual void AppVersion() const = 0;

    /**
     * @brief Global execution function.
     *
     * This virtual function will be called before every command.
     * Returning `1` will terminate the app after executing this function. Returning `0` won't terminate the app and execute further specified commands.
     * Override this function according to your logic.
     */
    virtual int GlobalExec() const { return 0; };

   public:
    /**
     * @brief Runs the command line application.
     *
     * This function is the starting point of the application.
     *
     * @param argc `argc` from the main function.
     * @param argv `argv` from the main function.
     */
    void Run(int argc, const char* argv[]);

    /**
     * @brief Destructor of the registry.
     *
     * This will deallocate all the registered commands, clear the command map and execute the destructor of the `GlobalArgRegistry` upon destruction.
     */
    ~CommandRegistry();
  };

}  // namespace ChronoCLI

#endif