//
// Created by austindevx on 1/2/17.
//
#ifndef CONTRA_LANG_FILE_SOURCE_H
#define CONTRA_LANG_FILE_SOURCE_H

#include <fstream>
#include "source.h"

namespace frontend {
  class FileSource: public Source {
  public:
    /**
     * @constructor
     * @param src_path The path of the source file to be used
     */
    FileSource(std::string src_path);

    /**
     * @destructor
     */
    ~FileSource();

    /**
     * Read the next line from the file stream
     */
    void readLine() override;

    /**
     * Close the file stream being read.
     */
    void close();
  };
}
#endif //CONTRA_LANG_CONTRA_SOURCE_H
