//
// Created by austindevx on 1/2/17.
//
#ifndef CONTRA_LANG_SOURCE_H
#define CONTRA_LANG_SOURCE_H

#include <fstream>
#include <iostream>

int const START_OF_LINE = -1;
int const START_OF_FILE = -2;

namespace frontend {

  class Source {
  public:
    static char const S_EOL;  // Source defined end of line character
    static char const S_EOF;  // Source defined end of file character

    Source(std::string src_path);
    ~Source();
    char getCurrentCharacter();
    char getNextCharacter();
    char peekNextCharacter();
    void readLine();
    int getCurrentLineNumber();
    int getCurrentPosition();
    void close();

    private:
      std::ifstream stream;       // The stream from which the source is being read
      std::string currentLine;    // The current source line
      int currentLineNumber;      // The current line number in the source
      int currentPosition;        // The current position in the current line
  };
}
#endif //CONTRA_LANG_SOURCE_H
