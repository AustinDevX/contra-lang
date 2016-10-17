package contra.frontend;

import java.io.BufferedReader;
import java.io.IOException;

/**
 * Source
 *
 * The framework class that represents the source program.
 *
 */
public class Source{
  public static final char EOL = '\n';      // End-Of-Line character
  public static final char EOF = (char) 0;  // End-Of-File character

  private BufferedReader reader;  // reader for the source program
  private String currentline;     // the contents of the current line
  private int currentlineNum;     // the current line number
  private int currentPos;         // the current postion in the current line

  /**
   * @Constructor
   *
   * @param  reader       The buffered reader for the source program
   * @throws IOException
   */
  public Source(BufferedReader reader) throws IOException{
    this.reader  = reader;
    this.currrentlineNum = 0;
    this.currentPos = -2;   // -2 indicates that the current line needs to be read in
  }

  /**
   * Return the source character at the current position.
   *
   * @return  The source character at the current position
   * @throws  Exception
   */
  public char currentChar() throws Exception {
    // First read of the source program?
    if(currentPos == -2) {
      // read in the first line and extract the first character
      readLine();
      return nextChar();
    }
    // End of the source program?
    else if(currentLine == null) {
      return EOF;
    }
    // End of the current line?
    else if((currentPos == -1) || (currentPos == currentLine.length())) {
      return EOL;
    }
    // Need to read the next line
    else if(currentPos > currentLine.length()) {
      readline();
      return nextChar();
    }
    // return the character at the current position
    else {
      return line.charAt(currentPos);
    }
  }

  /**
   * Consume the current character and return the next source character
   *
   * @return [description]
   */
  public char nextChar() throws Exception {
    ++currentPos;
    return currentChar();
  }

  /**
   * Return the source character following the current character
   * without consuming the current character.
   *
   * @return  The following character
   * @throws  Exception
   */
  public char peekChar() throws Exception {
    currentChar();
    if(line == null) {
      return EOF;
    }
  }

  /**
   * Read the next source line
   *
   * @throws IOException
   */
  private void readLine() throws IOException {
    line = reader.readLine();   // null at eof
    currentPos = -1;

    if(line != null) {
      ++lineNum;
    }
  }

  /**
   * Close the source
   *
   * @throws IOException
   */
   private void close() throws Exception {
     if(reader != null) {
       try {
         reader.close();
       } catch (IOException e){
         e.printStackTrace();
         throw ex;
       }
     }
   }
}
