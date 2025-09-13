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
    explicit Exception(const std::string& message) : error_message(message), error_type("Argument Error") {}
    Exception(const std::string& type, const std::string& message) : error_message(message), error_type(type) {}

    const char* what() const noexcept override {
      full_message = error_type + ": " + error_message;
      return full_message.c_str();
    }

    void print() const;
  };

  namespace Error {
    class UnknownOption : public Exception {
     public:
      UnknownOption(const std::string& option) : Exception("Unknown Option", "The option '" + option + "' is not recognized") {}
    };

    class UnknownCommand : public Exception {
     public:
      UnknownCommand(const std::string& command) : Exception("Unknown Command", "The command '" + command + "' is not recognized") {}
    };

    class InvalidOption : public Exception {
     public:
      InvalidOption(const std::string& option) : Exception("Invalid Option", "The option '" + option + "' is invalid") {}
    };

    class InvalidArgument : public Exception {
     public:
      InvalidArgument(const std::string& argument, const std::string& reason)
          : Exception("Invalid Argument", "Argument '" + argument + "' is invalid: " + reason) {}
    };

    class MissingArgument : public Exception {
     public:
      MissingArgument(const std::string& argument) : Exception("Missing Argument", "Required argument '" + argument + "' is missing") {}
    };

    class TooManyArguments : public Exception {
     public:
      TooManyArguments() : Exception("Too Many Arguments", "Too many arguments provided") {}
    };

    class RuntimeError : public Exception {
     public:
      RuntimeError(const std::string& message) : Exception("Runtime Error", message) {}
    };

  }  // namespace Error
}  // namespace ChronoCLI

#endif