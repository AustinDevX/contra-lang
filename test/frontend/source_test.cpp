//
// Created by austindevx on 1/16/17.
//
#include <iostream>
#include <string>
#include <sstream>
#include "gmock/gmock.h"
#include "../../src/frontend/string_source.h"

using namespace testing;

TEST(Source_GetCurrentCharacter, ReturnsTheStartOfSourceCharacterIfSourceIsYetUnread) {
  auto source = frontend::Source(new std::istringstream("test"));
  ASSERT_EQ(source.getCurrentCharacter(), frontend::Source::S_SOS);
}

TEST(Source_NextCharacter, ReturnsTheFirstCharacterInTheUnderlyingStreamIfCalledOnAnUnreadSource) {
  auto source = new frontend::StringSource("test");
  ASSERT_EQ(source->getNextCharacter(), 't');
}

TEST(Source_GetNextCharacter, ReturnsTheCharacterAtTheNextPositionInTheSource) {
  auto source = frontend::Source(new std::istringstream("test"));
  EXPECT_EQ(source.getNextCharacter(), 't');
  EXPECT_EQ(source.getNextCharacter(), 'e');
  EXPECT_EQ(source.getNextCharacter(), 's');
  EXPECT_EQ(source.getNextCharacter(), 't');
}

TEST(Source_GetCurrentCharacter, ReturnsTheCharacterAtTheCurrentReadPosition) {
  auto source = frontend::Source(new std::istringstream("test"));
  EXPECT_EQ(source.getCurrentCharacter(), frontend::Source::S_SOS);
  source.getNextCharacter();
  EXPECT_EQ(source.getCurrentCharacter(), 't');
  source.getNextCharacter();
  EXPECT_EQ(source.getCurrentCharacter(), 'e');
  source.getNextCharacter();
  EXPECT_EQ(source.getCurrentCharacter(), 's');
  source.getNextCharacter();
  EXPECT_EQ(source.getCurrentCharacter(), 't');
  source.getNextCharacter();
}

TEST(Source_GetCurrentCharacter, GetCurrentCharacterAtTheEndOfLineReturnsTheEolCharacter) {
  auto source = new frontend::Source(new std::istringstream("k\nk"));
  source->getNextCharacter(); // read in the first character
  source->getNextCharacter();
  ASSERT_EQ(source->getCurrentCharacter(), frontend::Source::S_EOL);
}

// TODO:: Add test to confirm that newline character is returned if at the end of the current line
//        and not end of stream
TEST(Source_GetNextCharacter, ReturnsTheEndOfStreamCharacterIfAllCharactersHaveBeenConsumed) {
  auto source = frontend::Source(new std::istringstream());
  source.getCurrentCharacter(); // consume the start-of-stream character
  EXPECT_EQ(source.getNextCharacter(), frontend::Source::S_EOS);
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


