#include <sstream>
#include <stack>

#include "vm.hpp"
#include "ast.hpp"
#include "reader.hpp"

class compiler
{
public:
    compiler(memory& memory);

    void compile(const std::vector<expression::ptr>& ast);

private:
    class memory& memory;
};

compiler::compiler(class memory& memory):
    memory(memory)
{
}

void compiler::compile(const std::vector<expression::ptr>& ast)
{
    std::stack<expression::ptr> stack;
    for(auto expr:ast)
    {
        stack.push(expr);
    }

    while(!stack.empty())
    {
        auto expression = stack.top();
        stack.pop();

        auto l = expression->as<list>();
        if(l)
        {
            auto operation = l->children()[0]->as<atom>();
            for(auto it = l->children().rbegin(); it != l->children().rend()-1; ++it)
            {
                auto atom = (*it)->as<::atom>();
                auto i = std::stoi(atom->symbol().get_string());
                memory << instruction_type::PUSH << integer(i);
            }

            for(int i = 1; i < l->children().size(); ++i)
            {
                memory << instruction_type::ADD;
            }
        }
    }
}

int main()
{
    std::stringstream ss("(+ 1 2 3 4)");
    auto ast = reader::read(ss);

    memory instruction_memory;
    memory stack_memory;
    stack stack(stack_memory);

    compiler compiler(instruction_memory);
    compiler.compile(ast);

    instruction_memory << instruction_type::DUMP
                       << instruction_type::HALT;

    executor e(stack, instruction_memory);

    e.main();

    return 0;
}
