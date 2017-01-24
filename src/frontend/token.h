#ifndef CONTRA_LANG_TOKEN_H
#define CONTRA_LANG_TOKEN_H

#include <string>
#include <string>
#include <map>

#include "source.h"

namespace frontend {
  enum TokenType {
    // symbols
    EOL = 1, L_PAREN, R_PAREN, L_BRACE, R_BRACE, L_ANGLE_BRACKET, R_ANGLE_BRACKET,
    DOT, COMMA, STAR, PLUS, MINUS, SLASH, MOD, EQUALS, SEMICOLON, COLON, QUOTE, DOUBLE_SLASH, NOT_EQUALS,
    L_BRACKET, R_BRACKET, BIT_AND, BIT_OR, BIT_NOT, BIT_XOR, LOGICAL_AND, LOGICAL_OR, LOGICAL_NOT,ASSIGNMENT,
    // keywords
    DEF, RETURN, STRING_T, CHAR_T, I32_T, I64_T, U32_T, U64_T, F64_T, BOOL_T, IF, ELSE, ELIF, SWITCH, FOR, WHILE, IN, AND,
    PTR, ADDR, TRY, CATCH, FINALLY, GOTO, TRUE, FALSE,

    IDENTIFIER, INTEGER, REAL, BOOLEAN, END_OF_FILE, ERROR,
  };

  inline std::map<char const*, TokenType> createSymbolsMap() {
    std::map<char*, TokenType> symbols {{"(", L_PAREN}, {")", R_PAREN}, {"{", L_BRACE}, {"}", R_BRACE},
      {"[", L_BRACKET}, {"]", R_BRACKET}, {"<", L_ANGLE_BRACKET}, {"&&", LOGICAL_AND}, {"||", LOGICAL_OR}, {"!", LOGICAL_NOT},
      {">", R_ANGLE_BRACKET}, {".", DOT}, {",", COMMA}, {"*", STAR}, {"+", PLUS}, {"-", MINUS},
      {"/", SLASH}, {"%", MOD}, {"=", ASSIGNMENT}, {";", SEMICOLON}, {":", COLON}, {"\"", QUOTE}, {"//", DOUBLE_SLASH},
      {"&", BIT_AND}, {"|", BIT_OR}, {"~", BIT_NOT}, {"^", BIT_XOR}, {"==", EQUALS}, {"!=", NOT_EQUALS}};
    return symbols;
  };

  inline std::map<std::string, TokenType> createKeywordsMap() {
    std::map<std::string, TokenType> keywords;
    keywords["def"] = DEF; keywords["return"] = RETURN; keywords["string"] = STRING_T; keywords["char"] = CHAR_T;
    keywords["i32"] =  I32_T; keywords["i64"] = I64_T; keywords["u32"] = U32_T; keywords["u64"] = U64_T;
    keywords["f64"] = F64_T; keywords["bool"] = BOOL_T; keywords["if"] = IF; keywords["else"] = ELSE; keywords["elif"] = ELIF;
    keywords["switch"] = SWITCH; keywords["for"] = FOR; keywords["while"] = WHILE; keywords["in"] = IN; keywords["and"] = AND;
    keywords["ptr"] = PTR; keywords["addr"] = ADDR; keywords["try"] = TRY; keywords["catch"] = CATCH; keywords["finally"] = FINALLY;
    keywords["goto"] = GOTO; keywords["true"] = TRUE; keywords["false"] = FALSE;
    return keywords;
  };

  class Token {
    public:
    // The special symbols defined by contra lang
    static const std::map<char const*, TokenType> SYMBOLS;
    // The keywords defined by contra lang
    static const std::map<std::string, TokenType> KEYWORDS;

    /**
     * @Constructor
     *
     * @param  source The source to extract the token from
     *
     * @throws std::Exception
     */
    explicit Token(frontend::Source* source) : source{ source } {
      this->position = source->getCurrentPosition();
      this->lineNumber = source->getCurrentLineNumber();
    }

    /**
     * Extract the token from the source
     *
     * This base method extracts a single character from the source. All subclasses that implement this method
     * after extracting the token must leave the current source line position one beyond that of the last character
     * of the source.
     *
     * @throws std::Exception
     **/
    virtual void extract() {
      text = std::string(1, getCurrentCharacter()); // fills string of len 1 w/ currentChar
      getNextCharacter();
    }

    /**
     * Get the current character from the source
     *
     * @return The current character from the source
     * @throws std::Exception
     */
    char getCurrentCharacter() {
      return source->getCurrentCharacter();
    }

    /**
     * Get the next character from the source
     *
     * @return The next character from the source
     * @throws std::Exception
     */
    char getNextCharacter() {
      return source->getNextCharacter();
    }

    /**
     * Get the next character from the source without advancing the read position
     *
     * @return The next character from the source
     * @throws std::Exception
     */
    char peekNextCharacter() {
      return source->peekNextCharacter();
    }

    TokenType getType() {
      return type;
    }

    std::string getText() {
      return text;
    }
    protected:
    int position;           // the position of the first character in the token
    int lineNumber;         // the source code line where the token is found
    std::string text;       // the source code represenation of the token
    TokenType type;    // the type of the token e.g conditional, operator etc
    frontend::Source* source;// the source object from which the token is read
  };

}

#endif
