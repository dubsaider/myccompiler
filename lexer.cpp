#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include "string"

class Lexeme {
 private:
  int lineLexeme{};
  int posLexeme{};
  std::string data;
  std::string type;
  std::string value;
 public:
  Lexeme() = default;
  Lexeme(int lineLexeme_, int pos_, std::string data_, std::string type_, std::string value_)
      : lineLexeme(lineLexeme_),
        posLexeme(pos_),
        data(std::move(data_)),
        type(std::move(type_)),
        value(std::move(value_)) {}
  int GetLine() const {
    return lineLexeme;
  }
  int GetPos() const {
    return posLexeme;
  }
  const std::string &GetValue() const {
    return value;
  }
  const std::string &GetType() const {
    return type;
  }
  const std::string &GetData() const {
    return data;
  }
  ~Lexeme() = default;
};

class Lexer {
 private:
  char buff[1024]{};
  size_t len = 0;
  int pos = 0;
  int posLexeme = 1;
  int lineLexeme = 1;
  int eof = 0;
  bool isPresenceLexeme = true;
  FILE *pathFile = nullptr;
  const std::vector<std::string> keyword = {
      "auto", "double", "int", "struct", "break", "else", "long", "switch", "case", "enum", "register", "typedef",
      "char", "extern", "return", "union", "const", "float", "short", "unsigned", "continue", "for", "signed",
      "void", "default", "goto", "sizeof", "volatile", "do", "if", "static", "while", "-1"};
  const std::vector<std::pair<std::string, std::string>> operators = {
      {"[", "LSBRACKET"}, {"]", "RSBRACKET"}, {"(", "LRBRACKET"}, {")", "RRBRACKET"}, {".", "DOT"}, {",", "COMMA"},
      {"?", "QUESTION"}, {":", "COLON"}, {"~", "TILDE"}, {"-", "SUB"}, {"+", "ADD"}, {"&", "BITAND"}, {"*", "MULT"},
      {"<", "LESS"}, {">", "MORE"}, {"=", "ASSING"}, {"|", "BITOP"}, {"!", "NOT"}, {"/", "DIV"}, {"%", "MOD"},
      {"^", "XOR"}, {";", "SEMICOLON"}, {"{", "LFBRACKET"}, {"}", "RFBRACKET"},
  };
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

  std::string defineType(const std::string &text) {
    std::string type;
    if (std::find(keyword.begin(), keyword.end(), text) != keyword.end()) {
      return "KEYWORD";
    }
    if (!isalnum(text[0])) {
      return "OPERATOR";
    }
    for (char i : text) {
      if (text[0] == '0' && text[1] == 'x') {
        break;
      }
      if (!isdigit(i)) {
        return "IDENTIFIER";
      }
    }
    return "INTEGER";
  }

  static std::string hexToDecimal(const std::string &text) {
    unsigned long long result = 0;
    for (char i : text) {
      result *= 16;
      int num = tolower(i);
      if (num >= '0' && num <= '9') {
        result += num - 48;
      } else if (num <= 'f' && num >= 'a') {
        result += num - 87;
      }
    }
    return std::to_string(result);
  }
  static std::string octToDecimal(const std::string &text) {
    int result = 0;
    for (char i : text) {
      result *= 8;
      result += i - 48;
    }
    return std::to_string(result);
  }
  std::string defineValue(const std::string &text, const std::string &type) {
    if (type == "INTEGER") {
      if (text[1] == 'x') {
        return hexToDecimal(text);
      }
      if (text[0] == '0') {
        return octToDecimal(text);
      }
    }
    if (type == "OPERATOR") {
      for (const auto &item: operators) {
        if (text == item.first) {
          return item.second;
        }
      }
    }
    return text;
  }

 public:
  explicit Lexer(FILE *file) : pathFile(file) {}

  Lexeme takeLexeme() {
    std::string text;
    std::string type;
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
      if (!isalnum(symbol)) {
        isPresenceLexeme = true;
        text += symbol;
      }
      if (symbol == '\n') {
        currentLineLexeme = lineLexeme++;
        posLexeme = 1;
      } else {
        posLexeme++;
      }
    }
    if (text[text.length() - 1] > 9 && text[text.length() - 1] < 13 || text[text.length() - 1] == 32
        || text[text.length() - 1] == -1) {
      text.pop_back();
    }
    type = defineType(text);
    Lexeme lexeme(currentLineLexeme, currentPosLexeme, text, type, defineValue(text, type));
    return lexeme;
    // TODO true value
  }
  int GetEof() const {
    return eof;
  }
  ~Lexer() = default;
};