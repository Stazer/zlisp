#include "ast.hpp"

void list::add(expression::ptr expr)
{
  elements.emplace_back(expr);
}

const std::vector<expression::ptr>& list::children() const
{
    return elements;
}

atom::atom(struct symbol data)
  : data(data)
{  }

const symbol& atom::symbol() const
{
    return data;
}
