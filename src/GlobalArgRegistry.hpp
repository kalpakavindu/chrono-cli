#pragma once
#ifndef CHRONOCLI_GLOBAL_ARG_REGISTRY
#define CHRONOCLI_GLOBAL_ARG_REGISTRY

#include <map>

#include "Argument.hpp"

namespace ChronoCLI {

  /**
   * @class ChronoCLI::GlobalArgRegistry
   * @brief Registry for global command-line arguments.
   */
  class GlobalArgBase {
   private:
    std::map<std::string, Argument*> m_argMap;

   public:
    /**
     * @brief Registers a new argument in the global registry.
     *
     * @param arg Pointer to the Argument to be set.
     *
     * @throws ChronoCLI::Exception If the argument is required or an argument with the same key or shortkey already registered.
     */
    void RegisterArgument(Argument* arg);

    /**
     * @brief Sets the value for a given argument key.
     *
     * This method returns `false` if the provided key not exists in the registry.
     *
     * @param key Argument key or shortkey.
     * @param value String value for the argument.
     */
    bool setOption(const std::string& key, const std::string& value);

    /**
     * @brief Returns the number of registered arguments.
     */
    size_t size() const;

    /**
     * @brief Returns a std::map of all registered arguments.
     */
    const std::map<std::string, Argument*>& getMap() const;

    /**
     * @brief Destructor to clean up allocated Argument instances.
     */
    ~GlobalArgBase();
  };

  /**
   * @class ChronoCLI::GlobalArgRegistry
   * @brief Access class for Global Arguments
   */
  class GlobalArgRegistry {
   private:
    const GlobalArgBase& m_base;

   public:
    GlobalArgRegistry(const GlobalArgBase& base) : m_base(base) {}

    /**
     * @brief Finds an argument by its key.
     *
     * This returns a `nullptr` if the provided key not exists in the registry.
     * Use `--` for keys and `-` for shortkeys. eg: `--test` and `-t`.
     *
     * @param key Argument key (starting with `--`) or shortkey (starting with `-`).
     */
    Argument* findByKey(const std::string& key) const;

    /**
     * @brief Checks if an argument with the given key exists in the registry.
     *
     * Use `--` for keys and `-` for shortkeys. eg: `--test` and `-t`.
     *
     * @param key Argument key (starting with `--`) or shortkey (starting with `-`).
     */
    bool hasArg(const std::string& key) const;

    /**
     * @brief Returns the number of registered arguments.
     */
    size_t size() const;

    /**
     * @brief Returns std::map of a copy of all registered arguments.
     */
    std::map<std::string, Argument*> getMap() const;
  };

}  // namespace ChronoCLI

#endif