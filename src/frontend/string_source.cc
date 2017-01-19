//
// Created by austindevx on 1/18/17.
//

#include "string_source.h"

using namespace frontend;

StringSource::StringSource() : Source { new std::stringstream() } {}

StringSource::StringSource(std::string str) : Source { new std::istringstream(str) } {
  if(!stream->fail()) {
    readLine();
  }
}
