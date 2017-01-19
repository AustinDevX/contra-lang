//
// Created by austindevx on 1/18/17.
//

#ifndef CONTRA_LANG_STRING_SOURCE_H
#define CONTRA_LANG_STRING_SOURCE_H

#include <sstream>
#include <string>
#include "source.h"

namespace frontend {
  class StringSource : public Source {
  public:
    /**
     * @constructor
     */
    StringSource();

    /**
     * @constructor
     * @param str The string to be read
     */
    StringSource(std::string str);
  };
}
#endif //CONTRA_LANG_STRING_SOURCE_H
