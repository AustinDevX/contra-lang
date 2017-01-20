//
// Created by austindevx on 1/18/17.
//
#include "source.h"

using namespace frontend;

char const Source::S_EOL = '\n';
const char Source::S_EOS = '\0';
const char Source::S_SOS = '\1';
const int Source::lineStart = -1;
const int Source::streamStart = -2;

Source::Source(std::istream *stream) : stream{ stream }{
  currentLineNumber = 0;
  // mark the stream as unread
  currentPosition = streamStart;
  // read in the first line of the source. This will populate the currentLine member variable
  // without adjusting the current position.
  std::getline(*stream, currentLine);
  isExhausted = false;
};

char Source::getCurrentCharacter() {
  if(currentPosition == streamStart) {
    return S_SOS;
  } else if(currentPosition == lineStart) {
    return getNextCharacter();
  } else if(currentPosition >= 0 && currentPosition < currentLine.length()) {
    return currentLine.at(currentPosition);
  } else if(currentPosition == currentLine.length()) {
    // if all characters in the current line have been consumed and the stream has no
    // remaining characters to be read then the source is exhausted
    if(stream->eof()) {
      isExhausted = true;
      return S_EOS;
    } else {
      return S_EOL;
    }
  } else { //current position > currentLine.length()
    if(isExhausted) {
      return S_EOS;
    } else if(stream->eof()) {
      // if the end of line character's position was skipped over using advanceReadPosition
      // but the source has no more characters in its underlying stream return the end of source character
      isExhausted = true;
      return S_EOS;
    } else {
      readLine();
      return getNextCharacter();
    }
  }
}

char Source::getNextCharacter() {
  advanceReadPosition();
  return getCurrentCharacter();
}

char Source::peekNextCharacter() {
  auto nextPosition = currentPosition + 1;
  if(nextPosition == lineStart) {
    if(currentLine.length() == 0) { // an empty line
      return stream->eof() ? S_EOS : S_EOL;
    } else {
      return currentLine.at(0);
    }
  }

  if(nextPosition < currentLine.length()) return currentLine.at(nextPosition);

  auto currentCharacter = getCurrentCharacter();
  // cant peek past the end of the line or stream
  if(currentCharacter == S_EOL || currentCharacter == S_EOS) {
    return currentCharacter;
  }
}

void Source::readLine() {
  if(!stream->eof() && !stream->bad()) {
    std::getline(*stream, currentLine);
    currentPosition = lineStart;
    currentLineNumber++;
  }
}

