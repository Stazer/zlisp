#pragma once

#include <memory>
#include <vector>

class expression
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
  atom(const void* data);
private:
  const void* data;
};

