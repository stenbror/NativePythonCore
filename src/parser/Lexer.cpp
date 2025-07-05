//
// Created by Richard Magnor Stenbro on 05/07/2025.
//

#include "Lexer.h"

#include <utility>
#include <ranges>


using NativePythonCore::Parser::Lexer;

// Public constructor and methods //////////////////////////////////////////////////////////////////////////////////////

Lexer::Lexer(std::basic_string<char8_t> source_code, const unsigned long tab_size) {
    m_source_code = std::move(source_code);
    m_tab_size = tab_size;
    m_symbol_index = 0;
    m_line = 1;
    m_column = 0;
    m_start_index = 0;
    m_end_index = 0;
    m_prefix = std::vector<std::shared_ptr<Trivia>>();
    m_trailer = std::vector<std::shared_ptr<Trivia>>();

    CollectSymbols();
}

std::shared_ptr<NativePythonCore::Parser::Symbol> Lexer::GetNextSymbol() {
    return m_symbol_index < m_symbols.size() ?
        m_symbols[m_symbol_index++]
        : std::make_shared<Symbol>(SymbolType::kw_eof, m_line, m_column, m_start_index, m_end_index, m_prefix, m_trailer);
}

std::shared_ptr<NativePythonCore::Parser::Symbol> Lexer::GetNextSymbol(const unsigned long index) {
    return index <  m_symbols.size() ?
        m_symbols[index]
        : std::make_shared<Symbol>(SymbolType::kw_eof, m_line, m_column, m_start_index, m_end_index, m_prefix, m_trailer);
}

unsigned long Lexer::SymbolIndex() const
{
    return m_symbol_index;
}

void Lexer::Reset() {
    m_symbol_index = 0;
    m_line = 1;
    m_column = 0;
    m_start_index = 0;
    m_end_index = 0;
    m_prefix = std::vector<std::shared_ptr<Trivia>>();
    m_trailer = std::vector<std::shared_ptr<Trivia>>();
    m_Parenthesis_stack = std::stack<char8_t>();
    m_indent_stack = std::stack<unsigned long>();
}

void Lexer::CollectSymbols()
{


}