//
// Created by austindevx on 1/18/17.
//
#ifndef CONTRA_LANG_SOURCE_H
#define CONTRA_LANG_SOURCE_H

#include <istream>

namespace frontend {
/**
 * The interface of a source object. It represents an input stream from which contra source code may be read.
 *
 * Any source must follow a few behaviours when reading:
 *  - The first character in the stream is the start-of-source character.
 *  - The last character in the stream in the end-of-source character.
 *  - A source is an empty source if its underlying stream contains no characters. i.e The source contains
 *    a start-of-source character directly followed by an end-of-source character
 *  - A source is unread if no characters from the source have been consumed. i.e getNextCharacter has not been called.
 *  - A source is exhausted if all character have been read from the underlying stream.
 *  - Calling getNextCharacter on an empty stream always returns the end-of-stream character
 *  - Calling getNextCharacter on an exhausted stream always returns the end-of-stream character
 *  - Calling getCurrentCharacter before any read methods [excluding peekNextCharacter]
 *    always returns the start of stream character
 *  - The newline character '\n' is replaced by the end-of-line character when reading from a source.
 */
  class Source {
  public:
    static char const S_EOL;  // Source defined end of line character
    static char const S_EOS;  // Source defined end of stream character
    static char const S_SOS;  // Source defined start of stream character
    static int const lineStart;   // Source defined start of line position
    static int const streamStart;   // Source defined start of stream position

    /**
     * @constructor
     * @param stream The input stream to be read from
     */
    Source(std::istream *stream);

    /**
     * @destructor
     */
    virtual ~Source() {};

    /**
     * Return the character at the current position in the source
     *
     * @return The character at the current position
    */
    virtual char getCurrentCharacter();

    /**
     * Return the next character in the source
     *
     * @return The next character in the source
     */
    virtual char getNextCharacter();

    /**
     * Return the character at the next position in the source, without consuming
     * the current character
     *
     * @return The next character
     */
    virtual char peekNextCharacter();

    /**
     * Read the next line from the stream
     */
    virtual void readLine();

    /**
     * Return the number of the line currently being read.
     * @return int
     */
    int getCurrentLineNumber() { return currentLineNumber; };

    /**
     * Return the current read position within the current line.
     * @return int
     */
    int getCurrentPosition() { return currentPosition; };

  protected:
    std::istream *stream;       // The stream from which the source is being read
    std::string currentLine;    // The current source line
    int currentLineNumber;      // The current line number in the source
    int currentPosition;        // The current position in the current line
  };
}

#endif //CONTRA_LANG_SOURCE_H
