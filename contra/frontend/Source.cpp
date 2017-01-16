//
// Created by austindevx on 1/16/17.
//
#include <fstream>
#include "Source.h"

namespace frontend {
  char const Source::S_EOL = '\n';
  const char Source::S_EOF = EOF;

  Source::Source(std::string src_path) {
    stream.open(src_path, std::ios::in);
    currentLineNumber = 0;
    currentPosition = START_OF_FILE;

    // read in the first line to get things started
    readLine();
  }

  Source::~Source() { close(); }

  /**
   * Return the character at the current position in the source
   *
   * @return The character at the current position
  */
  char Source::getCurrentCharacter() {
    // if called before we start reading the current line then return the first character in the line
    if(currentPosition == START_OF_LINE) {
      return getNextCharacter();
    } else if(currentPosition == currentLine.length()) {
      // if stream.eof is true then we have reached the end of the input stream on the last read, when the characters
      // in the currentLine buffer are exhausted then return S_EOF to indicate the file stream has been exhausted as well
      // else we have just read the full line and the S_EOL before the next line is returned
      return stream.eof() ? S_EOF : S_EOL;
    } else if(currentPosition > currentLine.length()) {
      if(!stream.eof()) {
        // we have advanced past the end of the line so read in the next one
        readLine();
        return getNextCharacter();
      } else {
        return S_EOF;
      }
    } else {
      return currentLine.at(currentPosition);
    }
  }

  /**
   * Return the next character in the source
   *
   * @return The next character in the source
   */
  char Source::getNextCharacter() {
    currentPosition++;
    return getCurrentCharacter();
  }

  /**
   * Return the character at the next position in the source, without consuming
   * the current character
   *
   * @return The next character
   */
  char Source::peekNextCharacter() {
    if(char c = getCurrentCharacter() == S_EOF) {
      return S_EOF;
    }

    int nextPosition = currentPosition + 1;
    return nextPosition < currentLine.length() ? currentLine.at(nextPosition) : S_EOL;
  }

  void Source::readLine() {
    if(!stream.eof()) {
      std::getline(stream, currentLine);
      currentPosition = START_OF_LINE;
      currentLineNumber++;
    }
  }

  int Source::getCurrentLineNumber() {
    return currentLineNumber;
  }

  int Source::getCurrentPosition() {
    return currentPosition;
  }

  void Source::close() {
    if(stream.is_open()) stream.close();
  }
}


