//
// Created by austindevx on 1/19/17.
//
#include <vector>
#include <string>
#include "gmock/gmock.h"
#include "../../src/frontend/word_token.h"

using namespace testing;

TEST(WordToken_Extract, ExtractsValidKeywords) {
  auto test_strings = std::vector<std::string>{"def", "return", "if", "else"};
  for(auto test_string : test_strings) {
  }
}

TEST(WordToken_Extract, SetsCorrectTokenTypeOnExtractedKeywords) {}

TEST(WordToken_Extract, SetsTokenTypeAsIdentifierForNonKeywordWordTokens) {}

TEST(WordToken_Extract, ExtractsUpToButNotIncludingTheFirstNonValidWordCharacter) {}

