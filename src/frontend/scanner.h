//
// Created by austindevx on 1/2/17.
//

#ifndef CONTRA_LANG_SCANNER_H
#define CONTRA_LANG_SCANNER_H

#include <ctype.h>
#include <iostream> // for testing please remove

#include "source.h"
#include "token.h"
#include "word_token.h"

namespace frontend {

  class Scanner {
  public:

    /**
     * @Constructor
     *
     * @param src The source to extract tokens from
     */
    explicit Scanner(Source* src) : source{src}, currentToken{nullptr} {};

    /**
     * Return the last read token from the source
     *
     * @return Token*
     */
    Token* getCurrentToken() const { return currentToken; }

    /**
     * Return the next token from the source
     *
     * @return Token*
     */
    Token* getNextToken() {
      currentToken = extractToken();
      return currentToken;
    }

    /**
     * Extract the next token from the source
     * @return
     */
    Token* extractToken() {
      skipWhiteSpaceAndComments();

      Token* token = nullptr;
      char currentCharacter = getCurrentCharacter();

//

      return token;
    }

    /**
     * Return the current character
     *
     * @return
     */
    char getCurrentCharacter() {
      return source->getCurrentCharacter();
    }

    /**
     * Return the next character from the source
     *
     * @return
     */
    char getNextCharacter() {
      return source->getNextCharacter();
    }

  private:
    Source* source;
    Token*  currentToken;

    /**
     * Skips all upcoming characters in the source which are considered white space or are a part of a comment
     * until a token is reached.
     */
    void skipWhiteSpaceAndComments() {
      char currentCharacter = getCurrentCharacter();
      while(isspace(currentCharacter)) {
        currentCharacter = getNextCharacter();
      }
    }
  };
}
#endif //CONTRA_LANG_SCANNER_H
