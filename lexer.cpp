#include <cstdio>
#include <iostream>
#include "string"

class Lexeme {
 private:
  int lineLexeme{};
  int pos{};
  std::string data;
 public:
  Lexeme() = default;
  Lexeme(int lineLexeme_, int pos_, std::string data_)
      : lineLexeme(lineLexeme_), pos(pos_), data(std::move(data_)) {}
  int GetLine() const {
    return lineLexeme;
  }
  int GetPos() const {
    return pos;
  }
//  int GetValue() const {
//    return value;
//  }
//  const std::string &GetType() const {
//    return type;
//  }
  const std::string &GetData() const {
    return data;
  }
  ~Lexeme() = default;
};

class Lexer {
 private:
  char buff[1024]{};
  int len = 0;
  int pos = 0;
  int posLexeme = 1;
  int lineLexeme = 1;
  int eof = 0;
  bool isPresenceLexeme = true;
  FILE *pathFile = nullptr;

  char _fgetc() {
    if (pos == len) {
      pos = 0;
      len = fread(buff, 1, 1024, pathFile);
      if (len == 0) {
        eof = EOF;
        return EOF;
      }
    }
    return buff[pos++];
  }

 public:
  explicit Lexer(FILE *file) : pathFile(file) {}

  Lexeme takeLexeme() {
    std::string text;
    isPresenceLexeme = false;
    char symbol;
    int currentPosLexeme = posLexeme;
    int currentLineLexeme = lineLexeme;
    while (!isPresenceLexeme) {
      symbol = _fgetc();
      while (isalnum(symbol)) {
        isPresenceLexeme = true;
        text += symbol;
        symbol = _fgetc();
        posLexeme++;
      }
      if (!isalnum(symbol) && symbol != '\n') {
        isPresenceLexeme = true;
        text += symbol;
      }
      if (symbol == '\n' || symbol == -1) {
        currentLineLexeme = lineLexeme++;
        posLexeme = 1;
      } else {
        posLexeme++;
      }
    }
//    while (true) {
//      symbol = _fgetc();
//      if (isalnum(symbol)) {
//        text += symbol;
//        symbol = _fgetc();
//        posLexeme++;
//      } else if (symbol > 8 && symbol < 13 || symbol == 32){
//        symbol = _fgetc();
//        symbol == 10 ? posLexeme = 1, currentLineLexeme = lineLexeme++ : posLexeme++;
//      }
//    }
    Lexeme lexeme(currentLineLexeme, currentPosLexeme, text);
    return lexeme;
    // TODO type, true value, operators
  }
  int GetEof() const {
    return eof;
  }
  ~Lexer() = default;
};