#pragma once
#ifndef CHRONOCLI_COLORS_HPP
#define CHRONOCLI_COLORS_HPP

#include <string>

namespace ChronoCLI {

  /**
   * @enum ChronoCLI::FG
   * @brief Foreground colors
   *
   * This enum specifies the text color. Use attributes ending with `2` for high intensive colors.
   */
  enum class FG {
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    PURPLE,
    CYAN,
    WHITE,
    BLACK2,
    RED2,
    GREEN2,
    YELLOW2,
    BLUE2,
    PURPLE2,
    CYAN2,
    WHITE2,
    DEFAULT
  };

  /**
   * @enum ChronoCLI::BG
   * @brief Background colors
   *
   * This enum specifies the background color of the text. Use attributes ending with `2` for high intensive colors.
   */
  enum class BG {
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    PURPLE,
    CYAN,
    WHITE,
    BLACK2,
    RED2,
    GREEN2,
    YELLOW2,
    BLUE2,
    PURPLE2,
    CYAN2,
    WHITE2,
    DEFAULT
  };

  /**
   * @enum ChronoCLI::TEXT
   * @brief Text styles
   *
   * This enum specifies the text style.
   */
  enum class TEXT {
    REGULAR,
    BOLD,
    THIN,
    ITALIC,
    UNDERLINE
  };

  /**
   * @class ChronoCLI::Style
   * @brief Text styling class
   *
   * Apply stylings for console text using ANSI escape codes.
   */
  class Style {
   private:
    const std::string _st[5] = {"0", "1", "2", "3", "4"};
    const std::string _tx[16] = {"30", "31", "32", "33", "34", "35", "36", "37", "90", "91", "92", "93", "94", "95", "96", "97"};
    const std::string _bg[16] = {"40", "41", "42", "43", "44", "45", "46", "47", "100", "101", "102", "103", "104", "105", "106", "107"};
    std::string _pref = "\e[";
    const std::string _reset = "\e[0m";

   public:
    /**
     * @brief Constructor for Style class
     *
     * @param s Text style. Defaults to ChronoCLI::TEXT::REGULAR
     * @param cf Foreground color. Defaults to ChronoCLI::FG::DEFAULT
     * @param cb Background color. Defaults to ChronoCLI::BG::DEFAULT
     */
    Style(TEXT s = TEXT::REGULAR, FG cf = FG::DEFAULT, BG cb = BG::DEFAULT) {
      _pref += _st[static_cast<int>(s)];

      if (cf != FG::DEFAULT) {
        _pref += ";" + _tx[static_cast<int>(cf)];
      }
      if (cb != BG::DEFAULT) {
        _pref += ";" + _bg[static_cast<int>(cb)];
      }
      _pref += "m";
    }

    /**
     * @brief Constructor for Style class with only colors
     *
     * @param cf Foreground color. Defaults to ChronoCLI::FG::DEFAULT
     * @param cb Background color. Defaults to ChronoCLI::BG::DEFAULT
     */
    Style(FG cf = FG::DEFAULT, BG cb = BG::DEFAULT) {
      _pref += _st[0];

      if (cf != FG::DEFAULT) {
        _pref += ";" + _tx[static_cast<int>(cf)];
      }
      if (cb != BG::DEFAULT) {
        _pref += ";" + _bg[static_cast<int>(cb)];
      }
      _pref += "m";
    }

    /**
     * @brief Constructor for Style class with only background color
     *
     * @param cb Background color. Defaults to ChronoCLI::BG::DEFAULT
     */
    Style(BG cb = BG::DEFAULT) {
      _pref += _st[0];

      if (cb != BG::DEFAULT) {
        _pref += ";" + _bg[static_cast<int>(cb)];
      }
      _pref += "m";
    }

    /**
     * @brief Apply the style to a given string
     *
     * @param str The string to style
     */
    std::string set(const std::string& str) const {
      return _pref + str + _reset;
    }
  };

}  // namespace ChronoCLI

#endif
