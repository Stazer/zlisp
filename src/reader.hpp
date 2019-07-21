#pragma once

#include "symbol.hpp"

#include <unordered_map>
#include <cstdio>
#include <memory>
#include <vector>

class expression;

class reader
{
public:
  static std::vector<std::shared_ptr<expression>> read(std::istream& is);
private:
  enum class token_kind : std::int8_t
  {
    L_Paren = '(',
    R_Paren = ')',

    Atom = 1,

    Undef = 0,
    EndOfFile = EOF
  };

  class token
  {
  public:
    token(token_kind kind, symbol data);

    token_kind kind;
    symbol data;
    // source_location loc;   // TODO
  };
private:
  reader(std::istream& is);

  template<typename T>
  T get() { static_assert(sizeof(T) >= 0, "unimplemented"); }
private:
  std::istream& is;
  std::string linebuf;

  std::size_t col;
  std::size_t row;
};

