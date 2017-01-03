//
// Created by austindevx on 1/2/17.
//

#ifndef CONTRA_LANG_SOURCE_H
#define CONTRA_LANG_SOURCE_H

#include <fstream>

namespace frontend {
  class Source {
    public:
      static char const S_EOL = '\n';
      static char const S_EOF = EOF;


      explicit Source(std::ifstream stream) {
        currentLineNumber = 0;
        currentPosition = -2;
        stream = std::move(stream);
      }

      /**
       * Return the character at the current position in the source
       *
       * @return The character at the current position
       */
      char currentCharacter() {
        // this is the first time the input stream is being read
        if(currentPosition == -2) {
          readLine();
          return nextCharacter();
        }
        // at the end of the file
        else if(stream.eof()) {
          return S_EOF;
        }
        // at the end of the line
        else if( (currentPosition == -1) || (currentPosition == currentLine.length()) ) {
          return S_EOL;
        }
        // advanced past the end of the line and need to read the next one
        else if(currentPosition > currentLine.length()) {
          readLine();
          return nextCharacter();
        }
        // read the current character
        else {
          return currentLine.at(currentPosition);
        }
      }

      /**
       * Return the next character in the source
       *
       * @return The next character in the source
       */
      char nextCharacter() {
        currentPosition++;
        return currentCharacter();
      }

      /**
       * Return the character at the next position in the source, without consuming
       * the current character
       *
       * @return The next character
       */
      char peekCharacter() {
        currentCharacter();
        if(currentLine == NULL) {
          return S_EOF;
        }

        int nextPosition = currentPosition + 1;
        return nextPosition < currentLine.length() ? currentLine.at(nextPosition) : S_EOL;
      }

      void readLine() {
        std::getline(stream, currentLine);

        if(stream.eof()) {
          currentLineNumber++;
        }
      }

      void close() {
        if(stream != NULL) {
          stream.close();
        }
      }

    private:
      std::ifstream stream;       // The stream from which the source is being read
      std::string currentLine;    // The current source line
      int currentLineNumber;      // The current line number in the source
      int currentPosition;        // The current position in the current line
  };
}
#endif //CONTRA_LANG_SOURCE_H
