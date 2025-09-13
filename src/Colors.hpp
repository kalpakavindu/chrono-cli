#ifndef CHRONOCLI_COLORS_HPP
#define CHRONOCLI_COLORS_HPP

#include <iostream>

namespace ChronoCLI {
  namespace Colors {
    template <class CharT, class Traits>
    constexpr std::basic_ostream<CharT, Traits>& reset(std::basic_ostream<CharT, Traits>& os) {
      return os << "\033[0m";
    }

    template <class CharT, class Traits>
    constexpr std::basic_ostream<CharT, Traits>& green(std::basic_ostream<CharT, Traits>& os) {
      return os << "\033[32m";
    }

    template <class CharT, class Traits>
    constexpr std::basic_ostream<CharT, Traits>& red(std::basic_ostream<CharT, Traits>& os) {
      return os << "\033[31m";
    }

    template <class CharT, class Traits>
    constexpr std::basic_ostream<CharT, Traits>& yellow(std::basic_ostream<CharT, Traits>& os) {
      return os << "\033[33m";
    }

    template <class CharT, class Traits>
    constexpr std::basic_ostream<CharT, Traits>& blue(std::basic_ostream<CharT, Traits>& os) {
      return os << "\033[34m";
    }

    const std::string green(const std::string& text) {
      return "\033[32m" + text + "\033[0m";
    }

    const std::string red(const std::string& text) {
      return "\033[31m" + text + "\033[0m";
    }

    const std::string yellow(const std::string& text) {
      return "\033[33m" + text + "\033[0m";
    }

    const std::string blue(const std::string& text) {
      return "\033[34m" + text + "\033[0m";
    }
  }  // namespace Colors

}  // namespace ChronoCLI

#endif
