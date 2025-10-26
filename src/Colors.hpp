#pragma once
#ifndef CHRONOCLI_COLORS_HPP
#define CHRONOCLI_COLORS_HPP

namespace ChronoCLI {

  namespace Colors {

    /**
     * @brief Resets the terminal color to default.
     */
    template <class CharT, class Traits>
    constexpr std::basic_ostream<CharT, Traits>& reset(std::basic_ostream<CharT, Traits>& os) {
      return os << "\033[0m";
    }

    /**
     * @brief Sets the terminal text color to green.
     */
    template <class CharT, class Traits>
    constexpr std::basic_ostream<CharT, Traits>& green(std::basic_ostream<CharT, Traits>& os) {
      return os << "\033[32m";
    }

    /**
     * @brief Sets the terminal text color to red.
     */
    template <class CharT, class Traits>
    constexpr std::basic_ostream<CharT, Traits>& red(std::basic_ostream<CharT, Traits>& os) {
      return os << "\033[31m";
    }

    /**
     * @brief Sets the terminal text color to yellow.
     */
    template <class CharT, class Traits>
    constexpr std::basic_ostream<CharT, Traits>& yellow(std::basic_ostream<CharT, Traits>& os) {
      return os << "\033[33m";
    }

    /**
     * @brief Sets the terminal text color to blue.
     */
    template <class CharT, class Traits>
    constexpr std::basic_ostream<CharT, Traits>& blue(std::basic_ostream<CharT, Traits>& os) {
      return os << "\033[34m";
    }

    /**
     * @brief Colorizes the given text in green.
     */
    std::string green(const std::string& text) {
      return "\033[32m" + text + "\033[0m";
    }

    /**
     * @brief Colorizes the given text in red.
     */
    std::string red(const std::string& text) {
      return "\033[31m" + text + "\033[0m";
    }

    /**
     * @brief Colorizes the given text in yellow.
     */
    std::string yellow(const std::string& text) {
      return "\033[33m" + text + "\033[0m";
    }

    /**
     * @brief Colorizes the given text in blue.
     */
    std::string blue(const std::string& text) {
      return "\033[34m" + text + "\033[0m";
    }

  }  // namespace Colors

}  // namespace ChronoCLI

#endif
