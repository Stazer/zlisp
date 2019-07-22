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

    const std::vector<expression::ptr>& children() const;

private:
  std::vector<expression::ptr> elements;
};

class atom : public expression
{
public:
    atom(struct symbol data);

    const symbol& symbol() const;

private:
    struct symbol data;
};

