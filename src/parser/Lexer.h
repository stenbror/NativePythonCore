//
// Created by Richard Magnor Stenbro on 05/07/2025.
//

#ifndef LEXER_H
#define LEXER_H
#include <stack>
#include <vector>

#include "Symbol.h"

namespace NativePythonCore::Parser
{

    class Lexer {
        std::vector<std::shared_ptr<Symbol>> m_symbols;
        std::basic_string<char8_t> m_source_code;
        unsigned long m_tab_size;
        unsigned long m_symbol_index;
        unsigned long m_line;
        unsigned long m_column;
        unsigned long m_start_index;
        unsigned long m_end_index;
        std::vector<std::shared_ptr<Trivia>> m_prefix;
        std::vector<std::shared_ptr<Trivia>> m_trailer;
        std::stack<char8_t> m_Parenthesis_stack;
        std::stack<unsigned long> m_indent_stack;

    public:
        Lexer(std::basic_string<char8_t> source_code, unsigned long tab_size);

        std::shared_ptr<Symbol> GetNextSymbol();
        std::shared_ptr<Symbol> GetNextSymbol(unsigned long index);
        [[nodiscard]] unsigned long SymbolIndex() const;
        void Reset();

    private:
        void CollectSymbols();
    };

}

#endif //LEXER_H
