#include <iostream>
#include <cstdio>
#include "lexer.cpp"

int main(int argc, char *argv[]) {

  FILE *file = nullptr;

  std::cout << argv[1] << std::endl;

  if (argc < 4) {
    file = fopen(argv[1], "r");
  }

  std::cout << file << '\n';

  Lexer lexer(file);

  while (!lexer.GetEof()) {
    Lexeme lexeme = lexer.takeLexeme();
    std::cout << '(' << lexeme.GetLine() << ':' << lexeme.GetPos() << ") " << lexeme.GetData() << "\n";
  }

  return 0;
}