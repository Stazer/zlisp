#pragma once

#include "source_range.hpp"
#include "symbol.hpp"
#include "tmp.hpp"
#include <memory>
#include <vector>

class expression : public runtime_cast<expression>
{
public:
  using ptr = std::shared_ptr<expression>;

  expression(source_range range);

  virtual ~expression() = default;

  source_range location() const;
  void change_location(source_range range);

private:
  source_range loc;
};

class list : public expression
{
public:
  list(source_range range);

  void add(expression::ptr expr);

  const std::vector<expression::ptr>& children() const;

private:
  std::vector<expression::ptr> elements;
};

class atom : public expression
{
public:
  atom(source_range range, symbol data);

  symbol to_symbol() const;

private:
  struct symbol data;
};

