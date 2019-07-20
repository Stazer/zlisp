#include <iostream>
#include <iomanip>
#include <vector>
#include <bitset>
#include <cstdint>
#include <cmath>
#include <cassert>
#include <string>
#include <exception>
#include <fstream>
#include <sstream>
#include <memory>
#include <queue>

#include "vm.hpp"

class expression;

class reader
{
public:
  static std::vector<std::shared_ptr<expression>> read(std::istream& is);
};

enum class TokenKind : std::uint8_t
{
  L_Paren,
  R_Paren,

  Atom
};

class Token
{
public:
  Token(TokenKind kind, const std::string& data);

  const TokenKind kind;
  const std::string data;
};

Token::Token(TokenKind kind, const std::string& data)
  : kind(kind), data(data)
{  }

class expression
{
public:
  virtual ~expression() = default;
};

class list : public expression
{
public:
  void add(std::shared_ptr<expression> expr);

private:
  std::vector<std::shared_ptr<expression>> elements;
};

void list::add(std::shared_ptr<expression> expr)
{
  elements.emplace_back(expr);
}

class atom : public expression
{
public:
  atom(const std::string& data);
private:
  std::string data;
};

atom::atom(const std::string& data)
  : data(data)
{  }

std::vector<std::shared_ptr<expression>> reader::read(std::istream& is)
{
  ///////
  /// Broken stuff, remove it, but leave it here for later use
  ////////// examples where it breaks:
  ///////////////////// "abc def"
  ///////////////////// () ")"
  //Tokenize
  /*std::vector<Token> toks;
  for(std::string line; std::getline(is, line); )
  {
    std::size_t atm_beg = 0;
    for(std::size_t i = 0; i < line.size(); ++i)
    {
      if(line[i] == '(')
      {
        if(atm_beg < i)
          toks.push_back(Token(TokenKind::Atom, line.substr(atm_beg, i - atm_beg)));
        toks.push_back(Token(TokenKind::L_Paren, "("));
        ++atm_beg;
      }
      else if(line[i] == ')')
      {
        if(atm_beg < i)
          toks.push_back(Token(TokenKind::Atom, line.substr(atm_beg, i - atm_beg)));
        toks.push_back(Token(TokenKind::R_Paren, ")"));
        ++atm_beg;
      }
      else if(line[i] == ' ')
      {
        if(atm_beg < i)
          toks.push_back(Token(TokenKind::Atom, line.substr(atm_beg, i - atm_beg)));
        ++atm_beg;
      }
    }
  }
  //Parse
  */std::vector<std::shared_ptr<expression>> ast;/*
  std::queue<std::shared_ptr<list>> lists;
  for(auto& t : toks)
  {
    switch(t.kind)
    {
    case TokenKind::L_Paren:
      {
        if(lists.empty())
        {
          auto l = std::make_shared<list>();
          ast.push_back(l);
          lists.push(l);
        }
        else
        {
          auto l = std::make_shared<list>();
          lists.front()->add(l);
          lists.push(l);
        }
      } break;

    case TokenKind::R_Paren:
      {
        if(lists.empty())
        {
          // parse error, what do?
          assert(false);
        }    
        else
        {
          lists.pop();
        }
      } break;

    case TokenKind::Atom:
      {
        if(lists.empty())
        {
          ast.push_back(std::make_shared<atom>(t.data));
        }
        else
        {
          lists.front()->add(std::make_shared<atom>(t.data));
        }
      } break;
    }
  }
                                                 */
  return ast;
}

int main()
{
    class memory instruction_memory;
    class memory stack_memory;
    class stack stack(stack_memory);

    instruction_memory << instruction_type::PUSH << integer(42)
                       << instruction_type::PUSH << integer(28)
                       << instruction_type::ADD
                       << instruction_type::DUMP;

    instruction_memory << instruction_type::HALT;

    executor e(stack, instruction_memory);

    e.main();

    std::stringstream ss("((((() ()) >)\"abc\" x )() () () (()()) ) 42");
    auto ast = reader::read(ss);

    return 0;
}
