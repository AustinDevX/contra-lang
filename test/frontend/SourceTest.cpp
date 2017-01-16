//
// Created by austindevx on 1/16/17.
//
#include <string>
#include <fstream>
#include <iostream>
#include "gmock/gmock.h"
#include "../../contra/frontend/Source.h"

using namespace testing;
// all paths are relative to the build directory
const std::string empty_source_file_path = "../test/frontend/test_source_empty.txt";
const std::string simple_source_file_path = "../test/frontend/test_source_simple.txt";
const std::string multi_line_source_file1_path = "../test/frontend/test_source_multiline1.txt";

class SourceFixture: public testing::Test {
public:
  frontend::Source *emptySource = new frontend::Source(empty_source_file_path);
  frontend::Source *simpleSource = new frontend::Source(simple_source_file_path);
  frontend::Source *multilineSource1 = new frontend::Source(multi_line_source_file1_path);
};

TEST_F(SourceFixture, AlwaysReturnsEofWhenReadingEmptyFile) {
  EXPECT_EQ(emptySource->getCurrentCharacter(), frontend::Source::S_EOF);
  EXPECT_EQ(emptySource->getNextCharacter(), frontend::Source::S_EOF);
}

TEST_F(SourceFixture, StartsAtTheFirstCharacterInTheFile) {
  ASSERT_EQ(simpleSource->getCurrentCharacter(), 'T');
}

TEST_F(SourceFixture, CallingGetNextCharacterOnAnUnreadFileReturnsTheFirstCharacterInTheFile) {
  ASSERT_EQ(simpleSource->getNextCharacter(), 'T');
}

TEST_F(SourceFixture, GetNextCharacterReturnsTheNextCharacter) {
  // read the first character
  simpleSource->getCurrentCharacter();
  ASSERT_EQ(simpleSource->getNextCharacter(), 'h');
  ASSERT_EQ(simpleSource->getNextCharacter(), 'i');
}

TEST_F(SourceFixture, GetNextCharacterAtTheEndOfLineReturnsTheFirstCharacterOnTheNextLine) {
  // consume the current empty line up to the eol
  ASSERT_EQ(multilineSource1->getCurrentCharacter(), frontend::Source::S_EOL);
  ASSERT_EQ(multilineSource1->getNextCharacter(), 'n');
}

TEST_F(SourceFixture, GetCurrentCharacterAtTheEndOfLineReturnsTheEolCharacter) {
  ASSERT_EQ(multilineSource1->getCurrentCharacter(), frontend::Source::S_EOL);
}
//TEST_F(SourceFixture, ReturnsTheSecondCharacterWhenGetNextCharacterIsCalled) {
//  ASSERT_THAT(simpleSource->getNextCharacter(), Eq('h'));
//}

