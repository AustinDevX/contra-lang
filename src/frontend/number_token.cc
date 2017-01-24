//
// Created by austindevx on 1/21/17.
//

#include "number_token.h"
#include <cctype>
#include <cstdlib>
#include <string>


frontend::NumberToken::NumberToken(Source *source) : Token { source } { extract(); }

/**
 * Extract the number literal from the source
 */
void frontend::NumberToken::extract() {
  std::string integerDigits, fractionalDigits;
  // default to the integer type
  type = INTEGER;
  integerDigits = extractIntegerLiteral();
  // examine the character right after the integer literal
  char cc = getCurrentCharacter();
  if(cc == '.') {
    if(!isdigit(peekNextCharacter())) {
      // treat this as an integer literal followed by a dot token
      return;
    } else {
      // number is a real number so consume the decimal point and extract the fraction
      type = REAL;
      getNextCharacter();
      fractionalDigits = extractIntegerLiteral();
    }
  }

  if(fractionalDigits == "") {
    value = parseRealLiteralToValue(integerDigits, fractionalDigits);
  } else {
    value = parseIntegerLiteralToValue(integerDigits);
  }
}

/**
 * Extract a integer literal from the source. Advances past the last digit of the literal.
 *
 * @return The integer literal
 */
std::string frontend::NumberToken::extractIntegerLiteral() {
  std::string text;

  do{
    text.push_back(getCurrentCharacter());
  } while(isdigit(getNextCharacter()));

  return text;
}


double frontend::NumberToken::parseIntegerLiteralToValue(std::string literal) { std::stod(literal); }


double frontend::NumberToken::parseRealLiteralToValue(std::string integer, std::string fractional) {
  std::string literal = integer + "." + fractional;
  return std::stod(literal);
}


