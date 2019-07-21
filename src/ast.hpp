#pragma once

#include "symbol.hpp"
#include "tmp.hpp"
#include <memory>
#include <vector>

class expression : public runtime_cast<expression>
{
public:
  using ptr = std::shared_ptr<expression>;

  virtual ~expression() = default;
};

class list : public expression
{
public:
  void add(expression::ptr expr);

private:
  std::vector<expression::ptr> elements;
};

class atom : public expression
{
public:
  atom(symbol data);
private:
  symbol data;
};

