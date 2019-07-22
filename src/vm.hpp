#ifndef VM_HPP
#define VM_HPP

#include <iostream>
#include <iomanip>
#include <vector>
#include <bitset>
#include <cstdint>
#include <cmath>
#include <cassert>
#include <string>
#include <exception>

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
    bool empty() const;

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

bool memory::empty() const
{
    return data.empty();
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
    stack(class memory& memory);
    stack(class memory& memory, memory::iterator pointer);

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
    class memory& memory;
    memory::iterator pointer;

    void ensure(std::size_t n);
};

stack::stack(class memory& memory):
    memory(memory),
    pointer(std::begin(memory))
{
}

stack::stack(class memory& memory, memory::iterator pointer):
    memory(memory),
    pointer(pointer)
{
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

template <typename T>
void stack::print(std::ostream& output) const
{
    output << "[";

    if(!memory.empty())
    {
        for(auto it = std::begin(memory); it != std::end(memory) - sizeof(T); it += sizeof(T))
        {
            std::string prefix = "";

            if(it == pointer)
            {
                prefix = "->";
            }

            output << prefix << *reinterpret_cast<const T*>(&*it);

            if(it + sizeof(T) != std::end(memory) - sizeof(T))
            {
                output << " ";
            }
        }
    }

    output << "]";
}

void stack::ensure(std::size_t n)
{
    auto delta = std::distance(std::begin(memory), pointer);
    if(delta + n >= memory.size())
    {
        memory.resize(memory.size() + n);
        pointer = std::begin(memory) + delta;
    }
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

#endif
