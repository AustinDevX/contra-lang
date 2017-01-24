//
// Created by austindevx on 1/23/17.
//

#ifndef CONTRA_LANG_EXCEPTIONS_H
#define CONTRA_LANG_EXCEPTIONS_H

#include <stdexcept>

namespace frontend {
  class UnexpectedEndOfSource : public std::runtime_error {
  public:
    UnexpectedEndOfSource(): runtime_error("Unexpectedly reached the end of the source") {};
  };
}
#endif //CONTRA_LANG_EXCEPTIONS_H
