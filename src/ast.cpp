#include "ast.hpp"

void list::add(expression::ptr expr)
{
  elements.emplace_back(expr);
}

atom::atom(symbol data)
  : data(data)
{  }

