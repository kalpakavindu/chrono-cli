#ifndef CHRONOCLI_EXCEPTION_HPP
#define CHRONOCLI_EXCEPTION_HPP

#include <exception>
#include <string>

namespace ChronoCLI {
  class Exception : public std::exception {
   private:
    std::string error_message;
    std::string error_type;
    mutable std::string full_message;

   public:
    explicit Exception(const std::string& message) : error_message(message), error_type("Runtime Error") {}
    Exception(const std::string& type, const std::string& message) : error_message(message), error_type(type) {}

    const char* what() const noexcept override {
      full_message = error_type + ": " + error_message;
      return full_message.c_str();
    }

    virtual void print() const;
  };

  // Basic command input errors
  namespace CommandError {
    class CommandError : public Exception {
     public:
      CommandError(const std::string& type, const std::string& message) : Exception(type, message) {}

      void print() const override;
    };

    class UnknownOption : public CommandError {
     public:
      UnknownOption(const std::string& option) : CommandError("Unknown Option", "The option '" + option + "' is not recognized") {}
    };

    class UnknownCommand : public CommandError {
     public:
      UnknownCommand(const std::string& command) : CommandError("Unknown Command", "The command '" + command + "' is not recognized") {}
    };

    class InvalidOption : public CommandError {
     public:
      InvalidOption(const std::string& option) : CommandError("Invalid Option", "The option '" + option + "' is invalid") {}
    };

    class InvalidArgument : public CommandError {
     public:
      InvalidArgument(const std::string& argument, const std::string& reason)
          : CommandError("Invalid Argument", "Argument '" + argument + "' is invalid: " + reason) {}
    };

    class MissingArgument : public CommandError {
     public:
      MissingArgument(const std::string& argument) : CommandError("Missing Argument", "Required argument '" + argument + "' is missing") {}
    };

    class TooManyArguments : public CommandError {
     public:
      TooManyArguments() : CommandError("Too Many Arguments", "Too many arguments provided") {}
    };

  }  // namespace CommandError

  namespace ParserError {

    class ParserError : public Exception {
     public:
      ParserError(const std::string& message) : Exception("Parser Error", message) {}

      void print() const override;
    };

    class TypeConvertError : public ParserError {
     public:
      TypeConvertError(const std::string& value, const std::string& target_type)
          : ParserError("Failed to convert value '" + value + "' to type '" + target_type + "'") {}
    };

  }  // namespace ParserError

}  // namespace ChronoCLI

#endif