//
// Created by Richard Magnor Stenbro on 05/07/2025.
//

#ifndef LEXER_H
#define LEXER_H
#include <map>
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

        const std::map<std::basic_string<char8_t>, SymbolType> m_keywords = {
            { u8"False", SymbolType::kw_false },
            { u8"None", SymbolType::kw_none },
            { u8"True", SymbolType::kw_true },
            { u8"and", SymbolType::kw_and },
            { u8"as", SymbolType::kw_as },
            { u8"assert", SymbolType::kw_assert },
            { u8"async", SymbolType::kw_async },
            { u8"await", SymbolType::kw_await },
            { u8"break", SymbolType::kw_break },
            { u8"class", SymbolType::kw_class },
            { u8"continue", SymbolType::kw_continue },
            { u8"def", SymbolType::kw_def },
            { u8"del", SymbolType::kw_del },
            { u8"elif", SymbolType::kw_elif },
            { u8"else", SymbolType::kw_else },
            { u8"except", SymbolType::kw_except },
            { u8"finally", SymbolType::kw_finally },
            { u8"for", SymbolType::kw_for },
            { u8"from", SymbolType::kw_from },
            { u8"global", SymbolType::kw_global },
            { u8"if", SymbolType::kw_if },
            { u8"import", SymbolType::kw_import },
            { u8"in", SymbolType::kw_in },
            { u8"is", SymbolType::kw_is },
            { u8"lambda", SymbolType::kw_lambda },
            { u8"nonlocal", SymbolType::kw_nonlocal },
            { u8"not", SymbolType::kw_not },
            { u8"or", SymbolType::kw_or },
            { u8"pass", SymbolType::kw_pass },
            { u8"raise", SymbolType::kw_raise },
            { u8"return", SymbolType::kw_return },
            { u8"try", SymbolType::kw_try },
            { u8"while", SymbolType::kw_while },
            { u8"with", SymbolType::kw_with },
            { u8"yield", SymbolType::kw_yield },
        };

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
