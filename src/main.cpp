#include <sstream>

#include "vm.hpp"
#include "reader.hpp"

int main()
{
    memory instruction_memory;
    memory stack_memory;
    stack stack(stack_memory);

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
