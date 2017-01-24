//
// Created by austindevx on 1/21/17.
//

#ifndef CONTRA_LANG_NUMBER_TOKEN_H
#define CONTRA_LANG_NUMBER_TOKEN_H

#include "token.h"
#include "source.h"

namespace frontend {
  /**
   * Represents a number token derived from a number literal. Can be either an integer or a real number [double]
   */
  class NumberToken : public Token {
  public:
    /**
     * @constructor
     * @param source The source to read the token from
     */
    explicit NumberToken(Source *source);

    /**
     * Extract a number token from the source
     */
    void extract() override;

    /**
     * Extract an unsigned integer from the source
     * @return An unsigned integer literal
     */
    std::string extractIntegerLiteral();

    /**
     * Return the value of an integer literal
     * @return The value
     */
    double parseIntegerLiteralToValue(std::string literal);

    /**
     * Return the value of a real number literal
     * @param literal The real number literal
     * @return The value of the real
     */
    double parseRealLiteralToValue(std::string, std::string);

    /**
     * Return the numeric value of the number token
     *
     * @return the numeric value
     */
    double getValue() { return value; }

  private:
    double value;
  };
}


#endif //CONTRA_LANG_NUMBER_TOKEN_H
