#pragma once
#ifndef CHRONOCLI_EXCEPTION_HPP
#define CHRONOCLI_EXCEPTION_HPP

#include <exception>
#include <string>

namespace ChronoCLI {

  /**
   * @brief Base exception class for ChronoCLI
   *
   * All custom exceptions in ChronoCLI inherit from this class.
   */
  class Exception : public std::exception {
   private:
    std::string error_message;
    std::string error_type;
    mutable std::string full_message;

   public:
    explicit Exception(const std::string& message) : error_message(message), error_type("UnexpectedError") {}

    /**
     * @brief Construct a new Exception object
     * @param type The type of the Exception
     * @param message The message for the Exception
     */
    Exception(const std::string& type, const std::string& message) : error_message(message), error_type(type) {}

    const char* what() const noexcept override {
      full_message = error_type + ": " + error_message;
      return full_message.c_str();
    }

    /**
     * @brief Prints the error in the stdout
     */
    virtual void print() const;
  };

  // Basic command input errors
  namespace CommandError {
    /**
     * @brief Base exception class for command line based errors
     *
     * All custom comman line based errors are inherited from this class.
     */
    class CommandError : public Exception {
     public:
      /**
       * @brief Construct a new CommandError object
       * @param type The type of the error
       * @param message The message for the error
       */
      CommandError(const std::string& type, const std::string& message) : Exception(type, message) {}

      void print() const override;
    };

    /**
     * @brief Unknown option error
     */
    class UnknownOption : public CommandError {
     public:
      /**
       * @brief Construct a new UnknownOption error object
       * @param option The unknown option given by the user
       */
      UnknownOption(const std::string& option) : CommandError("UnknownOption", "The option '" + option + "' is not recognized") {}
    };

    /**
     * @brief Unknown command error
     */
    class UnknownCommand : public CommandError {
     public:
      /**
       * @brief Construct a new UnknownCommand error object
       * @param command The unknown command given by the user
       */
      UnknownCommand(const std::string& command) : CommandError("UnknownCommand", "The command '" + command + "' is not recognized") {}
    };

    /**
     * @brief Invalid option error
     */
    class InvalidOption : public CommandError {
     public:
      /**
       * @brief Construct a new InvalidOption error object
       * @param option The invalid option name
       */
      InvalidOption(const std::string& option) : CommandError("InvalidOption", "The option '" + option + "' is invalid") {}
    };

    /**
     * @brief Invalid argument error
     */
    class InvalidArgument : public CommandError {
     public:
      /**
       * @brief Construct a new InvalidArgument error object
       * @param argument The invalid argument name
       * @param reason The reason to be invalid
       */
      InvalidArgument(const std::string& argument, const std::string& reason)
          : CommandError("InvalidArgument", "Argument '" + argument + "' is invalid: " + reason) {}
    };

    /**
     * @brief Missing argument error
     */
    class MissingArgument : public CommandError {
     public:
      /**
       * @brief Construct a new MissingArgument error object
       * @param argument The argument name that is missing
       */
      MissingArgument(const std::string& argument) : CommandError("MissingArgument", "Required argument '" + argument + "' is missing") {}
    };

    /**
     * @brief Too Many Argument error
     */
    class TooManyArguments : public CommandError {
     public:
      /**
       * @brief Construct a new TooManyArguments error object
       */
      TooManyArguments() : CommandError("TooManyArguments", "Too many arguments provided") {}
    };

  }  // namespace CommandError

  namespace ParserError {

    /**
     * @brief Base Exception class for parsing based errors
     *
     * All custom parsing based errors are inherited from this class.
     */
    class ParserError : public Exception {
     public:
      /**
       * @brief Construct a new ParserError object
       * @param message The message for the error
       */
      ParserError(const std::string& message) : Exception("ParserError", message) {}

      void print() const override;
    };

    /**
     * @brief Type conversion error
     */
    class TypeConvertError : public ParserError {
     public:
      /**
       * @brief Construct a new TypeConvertError object
       * @param value The value that failed to convert
       * @param target_type The target typename the value failed to convert to
       */
      TypeConvertError(const std::string& value, const std::string& target_type)
          : ParserError("Failed to convert value '" + value + "' to type '" + target_type + "'") {}
    };

  }  // namespace ParserError

}  // namespace ChronoCLI

#endif