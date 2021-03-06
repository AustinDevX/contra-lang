//
// Created by austindevx on 1/16/17.
//
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "gmock/gmock.h"
#include "../../src/frontend/source.h"

using namespace testing;

TEST(Source_GetCurrentCharacter, ReturnsTheStartOfSourceCharacterIfSourceIsYetUnread) {
  auto test_strings = std::vector<std::string>{"", " ", "\n", "test", " test"};
  for(auto test_string : test_strings) {
    auto source = frontend::Source(new std::istringstream(test_string));
    ASSERT_EQ(source.getCurrentCharacter(), frontend::Source::S_SOS);
  }
}

TEST(Source_GetCurrentCharacter, ReturnsTheEndOfSourceCharacterIfSourceIsExhausted) {
  auto source = frontend::Source(new std::istringstream());
  // skip the start of source character
  source.advanceReadPosition();
  // exhaust the Source, should now return end of stream character
  ASSERT_EQ(source.getCurrentCharacter(), frontend::Source::S_EOS);
  source.advanceReadPosition();
  // subsequent reads to exhausted Source should also return the end of stream character
  ASSERT_EQ(source.getCurrentCharacter(), frontend::Source::S_EOS);
}

TEST(Source_GetCurrentCharacter, ReturnsTheEndOfLineCharacterIfAllCharactersInTheCurrentLineHaveBeenReadAndStreamIsNotExhausted) {
  auto source = new frontend::Source(new std::istringstream("k\nk"));
  source->getNextCharacter(); // read in the first character
  source->getNextCharacter();
  ASSERT_EQ(source->getCurrentCharacter(), frontend::Source::S_EOL);
}

TEST(Source_GetCurrentCharacter, ReturnsTheFirstCharacterOfTheNextLineIfTheEndOfLineCharacterOnTheCurrentLineIsConsumed){
  auto source = frontend::Source(new std::istringstream("k\nk"));
  // consume the start of stream character
  source.advanceReadPosition();
  // consume the end of line character
  source.advanceReadPosition();
  // should be at the first character on the next line
  EXPECT_EQ(source.getCurrentCharacter(), 'k');
}

TEST(Source_GetCurrentCharacter, ReturnsTheCharacterAtTheCurrentReadPosition) {
  auto source = frontend::Source(new std::istringstream("test"));
  EXPECT_EQ(source.getCurrentCharacter(), frontend::Source::S_SOS);
  source.advanceReadPosition();
  EXPECT_EQ(source.getCurrentCharacter(), 't');
  source.advanceReadPosition();
  EXPECT_EQ(source.getCurrentCharacter(), 'e');
  source.advanceReadPosition();
  EXPECT_EQ(source.getCurrentCharacter(), 's');
  source.advanceReadPosition();
  EXPECT_EQ(source.getCurrentCharacter(), 't');
}


TEST(Source_NextCharacter, ReturnsTheFirstCharacterInTheUnderlyingStreamIfCalledOnAnUnreadSource) {
  auto source = new frontend::Source(new std::istringstream("test"));
  ASSERT_EQ(source->getNextCharacter(), 't');
}

TEST(Source_GetNextCharacter, ReturnsTheCharacterAtTheNextPositionInTheSource) {
  auto source = frontend::Source(new std::istringstream("test"));
  EXPECT_EQ(source.getNextCharacter(), 't');
  EXPECT_EQ(source.getNextCharacter(), 'e');
  EXPECT_EQ(source.getNextCharacter(), 's');
  EXPECT_EQ(source.getNextCharacter(), 't');
}

TEST(Source_GetNextCharacter, ReturnsTheEndOfStreamCharacterIfSourceIsExhausted) {
  auto source = frontend::Source(new std::istringstream());
  source.getCurrentCharacter(); // consume the start-of-stream character
  EXPECT_EQ(source.getNextCharacter(), frontend::Source::S_EOS);
  EXPECT_EQ(source.getNextCharacter(), frontend::Source::S_EOS);
}

TEST(Source_GetNextCharacter, ReturnsTheFirstCharacterOnTheNextLineIfAllCharactersOnTheCurrentLineAreConsumed) {
  auto source = frontend::Source(new std::istringstream("hi\nbye"));
  // consume the start of stream character
  source.getNextCharacter();
  // read up to the new line
  source.getNextCharacter();
  source.getNextCharacter();
  EXPECT_EQ(source.getNextCharacter(), 'b');
}


TEST(Source_PeekNextCharacter, ReturnsTheNextCharacterInTheSource) {
  auto source = frontend::Source(new std::istringstream("test"));
  EXPECT_EQ(source.peekNextCharacter(), 't');
}

TEST(Source_PeekNextCharacter, DoesNotAlterReadPosition) {
  auto source = frontend::Source(new std::istringstream("test"));
  auto current = source.getCurrentCharacter();
  source.peekNextCharacter();
  EXPECT_EQ(source.getCurrentCharacter(), current);
}


TEST(Source_GetNextCharacter, ReturnsTheFirstCharacterOnTheNextLineIfCurrentCharacterIsTheEndOfLineCharacter) {
  auto source = frontend::Source(new std::istringstream("\nn"));
  // consume the start of stream character
  source.getNextCharacter();
  // confirm that we are at the end of the line and check the first char on the next line
  ASSERT_EQ(source.getCurrentCharacter(), frontend::Source::S_EOL);
  ASSERT_EQ(source.getNextCharacter(), 'n');
}


