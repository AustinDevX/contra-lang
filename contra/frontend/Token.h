#ifndef CONTRA_LANG_TOKEN_H
#define CONTRA_LANG_TOKEN_H

#include <string>
#include <string>
#include <unordered_map>

#include "Source.h"

namespace frontend {
  enum TokenType {
    // symbols
    NEWLINE = 1, SPACE, TAB, L_PAREN, R_PAREN, L_BRACE, R_BRACE, L_ANGLE_BRACKET, R_ANGLE_BRACKET,
    DOT, COMMA, STAR, DOT_DOT, PLUS, MINUS, SLASH, MOD, EQUALS, SEMICOLON, COLON, QUOTE, DOUBLE_SLASH, ARROW,
    L_BRACKET, R_BRACKET, BIT_AND, BIT_OR, BIT_NOT, BIT_XOR,

    // keywords
    DEF, RETURN, STRING_T, CHAR_T, I32_T, I64_T, U32_T, U64_T, F64_T, BOOL_T, IF, ELSE, ELIF, SWITCH, FOR, WHILE, IN, AND,
    PTR, ADDR, TRY, CATCH, FINALLY, GOTO, TRUE, FALSE,

    IDENTIFIER, INTEGER, FLOAT, BOOLEAN, END_OF_FILE,
  };

  inline std::unordered_map<std::string, TokenType> createSymbolsMap() {
    std::unordered_map<std::string, TokenType> symbols {{"\n", NEWLINE}, {" ", SPACE}, {"\t", TAB}, {"[", L_PAREN},
      {"]", R_PAREN}, {"{", L_BRACE}, {"}", R_BRACE}, {"[", L_BRACKET}, {"]", R_BRACKET}, {"<", L_ANGLE_BRACKET},
      {">", R_ANGLE_BRACKET}, {".", DOT}, {",", COMMA}, {"*", STAR}, {"..", DOT_DOT}, {"+", PLUS}, {"-", MINUS},
      {"/", SLASH}, {"%", MOD}, {"=", EQUALS}, {";", SEMICOLON}, {":", COLON}, {"\"", QUOTE}, {"//", DOUBLE_SLASH},
      {"->", ARROW}, {"&", BIT_AND}, {"|", BIT_OR}, {"~", BIT_NOT}, {"^", BIT_XOR}};
    return symbols;
  };

  inline std::unordered_map<std::string, TokenType> createKeywordsMap() {
    std::unordered_map<std::string, TokenType> keywords;
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

    static const std::unordered_map<std::string, TokenType> SYMBOLS;
    static const std::unordered_map<std::string, TokenType> KEYWORDS;

    /**
     * @Constructor
     *
     * @param  source The source from where to fetch the token
     * @throws std::Exception
     */
    explicit Token(frontend::Source* source) : source{ source } {
      this->position = source->getCurrentPosition();
      this->lineNumber = source->getCurrentLineNumber();
    }

    /**
     * Extract a one character token from the source
     *
     * After extracting the token, the current source line postion will be one
     * beyond that of the last token character.
     * * @throws std::Exception */
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
