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

class memory
{
public:
    using data_type = std::vector<std::uint8_t>;
    using iterator = data_type::iterator;
    using const_iterator = data_type::const_iterator;
    using reverse_iterator = data_type::reverse_iterator;
    using const_reverse_iterator = data_type::const_reverse_iterator;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    reverse_iterator rbegin();
    reverse_iterator rend();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

    std::size_t size() const;

    void resize(std::size_t n);
    void ensure(std::size_t location, std::size_t bytes);

    template <typename T>
    void write(T data);

    template <typename T>
    void write(std::size_t location, T data);

    template <typename T>
    void write(iterator location, T data);

    template <typename T>
    memory& operator<<(T data);

    template <typename T>
    void read(std::size_t location, T& data) const;

    template <typename T>
    void read(iterator location, T& data) const;

    template <typename T>
    T read(std::size_t location) const;

    template <typename T>
    T read(iterator location) const;

private:
    data_type data;
};

typename memory::iterator memory::begin()
{
    return data.begin();
}
typename memory::iterator memory::end()
{
    return data.end();
}
typename memory::const_iterator memory::begin() const
{
    return data.begin();
}
typename memory::const_iterator memory::end() const
{
    return data.end();
}
typename memory::const_iterator memory::cbegin() const
{
    return data.cbegin();
}
typename memory::const_iterator memory::cend() const
{
    return data.cend();
}

typename memory::reverse_iterator memory::rbegin()
{
    return data.rbegin();
}
typename memory::reverse_iterator memory::rend()
{
    return data.rend();
}
typename memory::const_reverse_iterator memory::rbegin() const
{
    return data.rbegin();
}
typename memory::const_reverse_iterator memory::rend() const
{
    return data.rend();
}
typename memory::const_reverse_iterator memory::crbegin() const
{
    return data.crbegin();
}
typename memory::const_reverse_iterator memory::crend() const
{
    return data.crend();
}

std::size_t memory::size() const
{
    return data.size();
}

void memory::resize(std::size_t n)
{
    data.resize(n);
}

void memory::ensure(std::size_t location, std::size_t bytes)
{
    auto sum = location + bytes;
    if(sum >= size())
    {
        resize(sum);
    }
}

template <typename T>
void memory::write(T data)
{
    write(size(), data);
}

template <typename T>
void memory::write(std::size_t location, T data)
{
    ensure(location, sizeof(T));

    new (&this->data[location]) T (data);
}

template <typename T>
void memory::write(iterator location, T data)
{
    write(std::distance(begin(), location), data);
}

template <typename T>
memory& memory::operator<<(T data)
{
    write(data);

    return *this;
}

template <typename T>
void memory::read(std::size_t location, T& data) const
{
    read(begin() + location, data);
}

template <typename T>
void memory::read(iterator location, T& data) const
{
    data = *reinterpret_cast<T*>(&*location);
}

template <typename T>
T memory::read(std::size_t location) const
{
    return read<T>(begin() + location);
}

template <typename T>
T memory::read(iterator location) const
{
    T data;
    read(location, data);

    return data;
}

class stack
{
public:
    using data_type = memory;
    using iterator = data_type::iterator;
    using const_iterator = data_type::const_iterator;
    using reverse_iterator = data_type::reverse_iterator;
    using const_reverse_iterator = data_type::const_reverse_iterator;

    stack();

    stack(const stack& s);
    stack& operator=(const stack& s);

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    reverse_iterator rbegin();
    reverse_iterator rend();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

    void up(std::size_t amount);
    void down(std::size_t amount);

    template <typename T>
    void top(T value);

    template <typename T>
    T& top();

    template <typename T>
    void peek(T& value);

    template <typename T>
    T peek();

    template <typename T>
    void push(T value);

    template <typename T>
    void pop(T& value);

    template <typename T>
    T pop();

    template <typename T>
    void print(std::ostream& output) const;

private:
    void ensure(std::size_t n);

    data_type data;
    data_type::iterator pointer;
};

stack::stack()
{
    pointer = data.begin();
}

stack::stack(const stack& s)
{
    data = s.data;
    pointer = data.begin() + std::distance(s.data.begin(), data_type::const_iterator(s.pointer));
}
stack& stack::operator=(const stack& s)
{
    data = s.data;
    pointer = data.begin() + std::distance(s.data.begin(), data_type::const_iterator(s.pointer));

    return *this;
}

typename stack::iterator stack::begin()
{
    return data.begin();
}
typename stack::iterator stack::end()
{
    return data.end();
}
typename stack::const_iterator stack::begin() const
{
    return data.begin();
}
typename stack::const_iterator stack::end() const
{
    return data.end();
}
typename stack::const_iterator stack::cbegin() const
{
    return data.cbegin();
}
typename stack::const_iterator stack::cend() const
{
    return data.cend();
}

typename stack::reverse_iterator stack::rbegin()
{
    return data.rbegin();
}
typename stack::reverse_iterator stack::rend()
{
    return data.rend();
}
typename stack::const_reverse_iterator stack::rbegin() const
{
    return data.rbegin();
}
typename stack::const_reverse_iterator stack::rend() const
{
    return data.rend();
}
typename stack::const_reverse_iterator stack::crbegin() const
{
    return data.crbegin();
}
typename stack::const_reverse_iterator stack::crend() const
{
    return data.crend();
}

void stack::up(std::size_t amount)
{
    ensure(amount);
    pointer += amount;
}
void stack::down(std::size_t amount)
{
    pointer -= amount;
}

template <typename T>
void stack::top(T value)
{
    top<T>() = value;
}

template <typename T>
T& stack::top()
{
    ensure(sizeof(T));
    return *reinterpret_cast<T*>(&*(pointer - sizeof(T)));
}

template <typename T>
void stack::peek(T& value)
{
    value = peek<T>();
}

template <typename T>
T stack::peek()
{
    return *reinterpret_cast<T*>(&*(pointer-sizeof(T)));
}

template <typename T>
void stack::push(T value)
{
    up(sizeof(value));

    new (&*(pointer-sizeof(T))) T(value);
}

template <typename T>
void stack::pop(T& value)
{
    value = pop<T>();
}

template <typename T>
T stack::pop()
{
    down(sizeof(T));
    return *reinterpret_cast<T*>(&*pointer);
}

void stack::ensure(std::size_t n)
{
    auto delta = std::distance(std::begin(data), pointer);
    if(delta + n >= data.size())
    {
        data.resize(data.size() + n);
        pointer = std::begin(data) + delta;
    }
}

template <typename T>
void stack::print(std::ostream& output) const
{
    output << "[";

    for(auto it = data.begin(); it != data.end() - sizeof(T); it += sizeof(T))
    {
        output << *reinterpret_cast<const T*>(&*it);

        if(it + sizeof(T) != data.end() - sizeof(T))
        {
            output << " ";
        }
    }

    output << "]";
}

enum class instruction_type : std::uint8_t
{
    NO_OPERATION = 0,
    HALT,

    DUMP,

    PUSH,
    POP,

    ADD,
    SUBTRACT,

    UNKNOWN
};

class instruction_reader
{
public:
    instruction_reader(const class memory& memory);

    instruction_type instruction();

    template <typename T>
    void read(T& data);

    template <typename T>
    T read();

    template <typename T>
    instruction_reader& operator>>(T& data);

private:
    const class memory& memory;
    memory::const_iterator counter;
};

instruction_reader::instruction_reader(const class memory& memory):
    memory(memory)
{
    counter = memory.begin();
}

instruction_type instruction_reader::instruction()
{
    if(counter != memory.end())
    {
        const instruction_type type = static_cast<instruction_type>(*counter);
        ++counter;

        if(type < instruction_type::UNKNOWN)
        {
            return type;
        }
    }

    throw std::runtime_error("fetched unknown instruction");
}

template <typename T>
void instruction_reader::read(T& data)
{
    data = *reinterpret_cast<const T*>(&*counter);
    counter += sizeof(T);
}

template <typename T>
T instruction_reader::read()
{
    T data;
    read(data);

    return data;
}

using integer = std::int64_t;

template <typename T>
instruction_reader& instruction_reader::operator>>(T& data)
{
    read(data);

    return *this;
}

class executor
{
public:
    executor(class stack& stack, const class memory& memory);

    void main();

private:
    class stack& stack;
    instruction_reader reader;
};

executor::executor(class stack& stack, const class memory& memory):
    stack(stack),
    reader(memory)
{
}

void executor::main()
{
    for(bool running = true; running;)
    {
        auto instruction_type = reader.instruction();

        switch(instruction_type)
        {
        case instruction_type::NO_OPERATION:
            break;

        case instruction_type::HALT:
            running = false;

            break;

        case instruction_type::DUMP:
            stack.print<integer>(std::cout);
            break;

        case instruction_type::PUSH:
        {
            integer b;
            reader >> b;
            stack.push(b);

            break;
        }

        case instruction_type::ADD:
        {
            auto b = stack.pop<integer>();
            stack.top<integer>() += b;

            break;
        }

        case instruction_type::SUBTRACT:
        {
            auto b = stack.pop<integer>();
            stack.top<integer>() -= b;

            break;
        }

        case instruction_type::UNKNOWN:
        default:
            std::cerr << "Fetched unknown instruction! VM was halted.\n";
            running = false;

            break;
        }
    }
}

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
  /*
  //Tokenize
  std::vector<Token> toks;
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
  std::vector<std::shared_ptr<expression>> ast;
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

  return ast;
  */
}

int main()
{
    class memory memory;
    class stack stack;

    memory << instruction_type::PUSH << integer(42)
           << instruction_type::PUSH << integer(28)
           << instruction_type::ADD
           << instruction_type::DUMP;

    memory << instruction_type::HALT;

    executor e(stack, memory);

    e.main();


    std::stringstream ss("((((() ()) >)\"abc\" x )() () () (()()) ) 42");
    auto ast = reader::read(ss);

    return 0;
}
