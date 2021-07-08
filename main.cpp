#include <iostream>
#include <cstdio>
#include "lexer.cpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

void testBody(){

}

TEST_CASE("Empty file") {
  FILE *inFile = fopen("parser/1.in", "r");
  Lexer lexer(inFile);
  std::vector<Lexeme> lexemes;
  std::ofstream outFile;
  while (!lexer.GetEof()) {
    Lexeme lexeme = lexer.takeLexeme();
    REQUIRE(lexeme.GetLine() == 1);
    REQUIRE(lexeme.GetPos() == 1);
    REQUIRE(lexeme.GetType() == "OPERATOR");
    REQUIRE(lexeme.GetValue().empty());
    REQUIRE(lexeme.GetData().empty());
  }
}
TEST_CASE("File with space") {
  FILE *inFile = fopen("parser/2.in", "r");
  Lexer lexer(inFile);
  std::vector<Lexeme> lexemes;
  std::ofstream outFile;
  while (!lexer.GetEof()) {
    Lexeme lexeme = lexer.takeLexeme();
    REQUIRE(lexeme.GetLine() == 1);
    REQUIRE(lexeme.GetPos() == 1);
    REQUIRE(lexeme.GetType() == "OPERATOR");
    REQUIRE(lexeme.GetValue().empty());
    REQUIRE(lexeme.GetData().empty());
  }
}
TEST_CASE("File with keyword") {
  FILE *inFile = fopen("parser/3.in", "r");
  Lexer lexer(inFile);
  std::vector<Lexeme> lexemes;
  std::fstream outFile("parser/3.out");
  while (!lexer.GetEof()) {
    int line, pos;
    std::string value, type, data;
    Lexeme lexeme = lexer.takeLexeme();
    if (lexeme.GetData().length() != 0) {
      outFile >> line >> pos >> type >> value >> data;
      REQUIRE(lexeme.GetLine() == line);
      REQUIRE(lexeme.GetPos() == pos);
      REQUIRE(lexeme.GetType() == type);
      REQUIRE(lexeme.GetValue() == value);
      REQUIRE(lexeme.GetData() == data);
    }
  }
}
TEST_CASE("File with operator") {
  FILE *inFile = fopen("parser/4.in", "r");
  Lexer lexer(inFile);
  std::vector<Lexeme> lexemes;
  std::fstream outFile("parser/4.out");
  while (!lexer.GetEof()) {
    int line, pos;
    std::string value, type, data;
    Lexeme lexeme = lexer.takeLexeme();
    if (lexeme.GetData().length() != 0) {
      outFile >> line >> pos >> type >> value >> data;
      REQUIRE(lexeme.GetLine() == line);
      REQUIRE(lexeme.GetPos() == pos);
      REQUIRE(lexeme.GetType() == type);
      REQUIRE(lexeme.GetValue() == value);
      REQUIRE(lexeme.GetData() == data);
    }
  }
}
TEST_CASE("File with hexNum") {
  FILE *inFile = fopen("parser/5.in", "r");
  Lexer lexer(inFile);
  std::vector<Lexeme> lexemes;
  std::fstream outFile("parser/5.out");
  while (!lexer.GetEof()) {
    int line, pos;
    std::string value, type, data;
    Lexeme lexeme = lexer.takeLexeme();
    if (lexeme.GetData().length() != 0) {
      outFile >> line >> pos >> type >> value >> data;
      REQUIRE(lexeme.GetLine() == line);
      REQUIRE(lexeme.GetPos() == pos);
      REQUIRE(lexeme.GetType() == type);
      REQUIRE(lexeme.GetValue() == value);
      REQUIRE(lexeme.GetData() == data);
    }
  }
}

TEST_CASE("File with octalNum") {
  FILE *inFile = fopen("parser/6.in", "r");
  Lexer lexer(inFile);
  std::vector<Lexeme> lexemes;
  std::fstream outFile("parser/6.out");
  while (!lexer.GetEof()) {
    int line, pos;
    std::string value, type, data;
    Lexeme lexeme = lexer.takeLexeme();
    if (lexeme.GetData().length() != 0) {
      outFile >> line >> pos >> type >> value >> data;
      REQUIRE(lexeme.GetLine() == line);
      REQUIRE(lexeme.GetPos() == pos);
      REQUIRE(lexeme.GetType() == type);
      REQUIRE(lexeme.GetValue() == value);
      REQUIRE(lexeme.GetData() == data);
    }
  }
}
TEST_CASE("File with identifierNum") {
  FILE *inFile = fopen("parser/7.in", "r");
  Lexer lexer(inFile);
  std::vector<Lexeme> lexemes;
  std::fstream outFile("parser/7.out");
  while (!lexer.GetEof()) {
    int line, pos;
    std::string value, type, data;
    Lexeme lexeme = lexer.takeLexeme();
    if (lexeme.GetData().length() != 0) {
      outFile >> line >> pos >> type >> value >> data;
      REQUIRE(lexeme.GetLine() == line);
      REQUIRE(lexeme.GetPos() == pos);
      REQUIRE(lexeme.GetType() == type);
      REQUIRE(lexeme.GetValue() == value);
      REQUIRE(lexeme.GetData() == data);
    }
  }
}
TEST_CASE("File with identifierAlpha") {
  FILE *inFile = fopen("parser/8.in", "r");
  Lexer lexer(inFile);
  std::vector<Lexeme> lexemes;
  std::fstream outFile("parser/8.out");
  while (!lexer.GetEof()) {
    int line, pos;
    std::string value, type, data;
    Lexeme lexeme = lexer.takeLexeme();
    if (lexeme.GetData().length() != 0) {
      outFile >> line >> pos >> type >> value >> data;
      REQUIRE(lexeme.GetLine() == line);
      REQUIRE(lexeme.GetPos() == pos);
      REQUIRE(lexeme.GetType() == type);
      REQUIRE(lexeme.GetValue() == value);
      REQUIRE(lexeme.GetData() == data);
    }
  }
}

//int main(int argc, char *argv[]) {
//
//  FILE *file = nullptr;
//
//  std::cout << argv[1] << std::endl;
//
//  if (argc < 4) {
//    file = fopen(argv[1], "r");
//  }
//
//  std::cout << file << '\n';
//
//  Lexer lexer(file);
//
//  std::vector<Lexeme> lexemes;
//
//  while (!lexer.GetEof()) {
//    Lexeme lexeme = lexer.takeLexeme();
//    if (lexeme.GetData().length() != 0) {
//      lexemes.push_back(lexeme);
//      std::cout << lexeme.GetLine() << ' ' << lexeme.GetPos() << ' ' << lexeme.GetType() << ' '
//                << lexeme.GetValue() << ' ' << lexeme.GetData() << "\n";
//    }
//  }
//  return 0;
//}