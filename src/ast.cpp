#include "ast.hpp"

expression::expression(source_range range)
  : loc(range)
{  }

source_range expression::location() const
{
  return loc;
}

void expression::change_location(source_range range)
{
  loc = range;
}

list::list(source_range range)
  : expression(range), elements()
{  }

void list::add(expression::ptr expr)
{
  elements.emplace_back(expr);
}

const std::vector<expression::ptr>& list::children() const
{
  return elements;
}

atom::atom(source_range loc, symbol data)
  : expression(loc), data(data)
{  }

symbol atom::to_symbol() const
{
  return data;
}
