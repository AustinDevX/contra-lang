//
// Created by austindevx on 1/19/17.
//

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "gmock/gmock.h"
#include "../../src/frontend/string_source.h"

using namespace testing;

TEST(StringSource_GetCurrentCharacter, ReturnsTheStartOfSourceCharacterIfSourceIsYetUnread) {
  auto test_strings = std::vector<std::string>{"", " ", "\n", "test", " test"};
  for(auto test_string : test_strings) {
    auto source = frontend::StringSource(test_string);
    ASSERT_EQ(source.getCurrentCharacter(), frontend::Source::S_SOS);
  }
}

TEST(StringSource_GetCurrentCharacter, ReturnsTheEndOfSourceCharacterIfSourceIsExhausted) {
  auto source = frontend::StringSource();
  // skip the start of source character
  source.advanceReadPosition();
  // exhaust the Source, should now return end of stream character
  ASSERT_EQ(source.getCurrentCharacter(), frontend::Source::S_EOS);
  source.advanceReadPosition();
  // subsequent reads to exhausted Source should also return the end of stream character
  ASSERT_EQ(source.getCurrentCharacter(), frontend::Source::S_EOS);
}

TEST(StringSource_GetCurrentCharacter, ReturnsTheEndOfLineCharacterIfAllCharactersInTheCurrentLineHaveBeenReadAndStreamIsNotExhausted) {
  auto source = new frontend::StringSource("k\nk");
  source->getNextCharacter(); // read in the first character
  source->getNextCharacter();
  ASSERT_EQ(source->getCurrentCharacter(), frontend::Source::S_EOL);
}

TEST(StringSource_GetCurrentCharacter, ReturnsTheFirstCharacterOfTheNextLineIfTheEndOfLineCharacterOnTheCurrentLineIsConsumed){
  auto source = frontend::StringSource("k\nk");
  // consume the start of stream character
  source.advanceReadPosition();
  // consume the end of line character
  source.advanceReadPosition();
  // should be at the first character on the next line
  EXPECT_EQ(source.getCurrentCharacter(), 'k');
}

TEST(StringSource_GetCurrentCharacter, ReturnsTheCharacterAtTheCurrentReadPosition) {
  auto source = frontend::StringSource("test");
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


TEST(StringSource_NextCharacter, ReturnsTheFirstCharacterInTheUnderlyingStreamIfCalledOnAnUnreadSource) {
  auto source = new frontend::StringSource("test");
  ASSERT_EQ(source->getNextCharacter(), 't');
}

TEST(StringSource_GetNextCharacter, ReturnsTheCharacterAtTheNextPositionInTheSource) {
  auto source = frontend::StringSource("test");
  EXPECT_EQ(source.getNextCharacter(), 't');
  EXPECT_EQ(source.getNextCharacter(), 'e');
  EXPECT_EQ(source.getNextCharacter(), 's');
  EXPECT_EQ(source.getNextCharacter(), 't');
}

TEST(StringSource_GetNextCharacter, ReturnsTheEndOfStreamCharacterIfSourceIsExhausted) {
  auto source = frontend::StringSource();
  source.getCurrentCharacter(); // consume the start-of-stream character
  EXPECT_EQ(source.getNextCharacter(), frontend::Source::S_EOS);
  EXPECT_EQ(source.getNextCharacter(), frontend::Source::S_EOS);
}

TEST(StringSource_GetNextCharacter, ReturnsTheFirstCharacterOnTheNextLineIfAllCharactersOnTheCurrentLineAreConsumed) {
  auto source = frontend::StringSource("hi\nbye");
  // consume the start of stream character
  source.getNextCharacter();
  // read up to the new line
  source.getNextCharacter();
  source.getNextCharacter();
  EXPECT_EQ(source.getNextCharacter(), 'b');
}


TEST(StringSource_PeekNextCharacter, ReturnsTheNextCharacterInTheSource) {
  auto source = frontend::StringSource("test");
  EXPECT_EQ(source.peekNextCharacter(), 't');
}

TEST(StringSource_PeekNextCharacter, DoesNotAlterReadPosition) {
  auto source = frontend::StringSource("test");
  auto current = source.getCurrentCharacter();
  source.peekNextCharacter();
  EXPECT_EQ(source.getCurrentCharacter(), current);
}


TEST(StringSource_GetNextCharacter, ReturnsTheFirstCharacterOnTheNextLineIfCurrentCharacterIsTheEndOfLineCharacter) {
  auto source = frontend::StringSource("\nn");
  // consume the start of stream character
  source.getNextCharacter();
  // confirm that we are at the end of the line and check the first char on the next line
  ASSERT_EQ(source.getCurrentCharacter(), frontend::Source::S_EOL);
  ASSERT_EQ(source.getNextCharacter(), 'n');
}

