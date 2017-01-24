//
// Created by austindevx on 1/21/17.
//

#include "string_token.h"
#include "exceptions.h"

/**
 * Extracts the text between a pair of " or '
 *
 * @throws frontend::UnexpectedEndOfSource
 */
void frontend::StringToken::extract() {
  // get the open quote used can be ' or "
  char initial_quote = getCurrentCharacter();
  // consume the opening quote
  auto cc = getNextCharacter();
  // extract characters until the corresponding closing quote is found
  while(cc != initial_quote){
    if(cc == Source::S_EOS) throw UnexpectedEndOfSource();
    text.push_back(cc);
  };
  type = STRING_T;
  // consume the closing quote
  getNextCharacter();
}
