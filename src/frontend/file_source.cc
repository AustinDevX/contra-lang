//
// Created by austindevx on 1/16/17.
//
#include <fstream>
#include "file_source.h"

using namespace frontend;

// TODO :: Add exception for stream failing to open
FileSource::FileSource(std::string src_path): Source { new std::ifstream(src_path, std::ios::in) }{
  if(!static_cast<std::ifstream*>(stream)->is_open() || stream->fail()) {
    // stream opened successfully, read in the first line to get things started
    readLine();
  }
}

FileSource::~FileSource() { close(); }

void FileSource::readLine() {
  // reading from file sources that were already closed will not be allowed
  if(static_cast<std::ifstream*>(stream)->is_open()) {
    getline(*stream, currentLine);
    currentPosition = lineStart;
    currentLineNumber++;
  }
}

void FileSource::close() {
  if(static_cast<std::ifstream*>(stream)->is_open()) static_cast<std::ifstream*>(stream)->close();
}


