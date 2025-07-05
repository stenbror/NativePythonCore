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
    m_column = 1;
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
    m_column = 1;
    m_start_index = 0;
    m_end_index = 0;
    m_prefix = std::vector<std::shared_ptr<Trivia>>();
    m_trailer = std::vector<std::shared_ptr<Trivia>>();
    m_Parenthesis_stack = std::stack<char8_t>();
    m_indent_stack = std::stack<unsigned long>();
}

void Lexer::CollectSymbols()
{
    auto it = m_source_code.cbegin();
    const auto end = m_source_code.end();

    SymbolType symbol = SymbolType::kw_eof;
    unsigned long move_index = 0;

    while (it != end) {


        m_start_index = it - m_source_code.cbegin(); /* Save start position for symbol */

        auto [codepoint, next] = DecodeUTF8(it, end);




        switch (codepoint) {
            case '+': {
                it = next;
                if (auto [codepoint, next] = DecodeUTF8(it, end); codepoint == '=') {
                    it = next;
                    m_end_index = it - m_source_code.cbegin();
                    move_index = 2;
                    symbol = SymbolType::kw_plus_assign;
                }
                else {
                    m_end_index = it - m_source_code.cbegin();
                    move_index = 1;
                    symbol = SymbolType::kw_plus;
                }
                break;
            }
            case '-': {
                it = next;
                if (auto [codepoint, next] = DecodeUTF8(it, end); codepoint == '=') {
                    it = next;
                    m_end_index = it - m_source_code.cbegin();
                    move_index = 2;
                    symbol = SymbolType::kw_minus_assign;
                }
                else if (auto [codepoint, next] = DecodeUTF8(it, end); codepoint == '>') {
                    it = next;
                    m_end_index = it - m_source_code.cbegin();
                    move_index = 2;
                    symbol = SymbolType::kw_arrow;
                }
                else {
                    m_end_index = it - m_source_code.cbegin();
                    move_index = 1;
                    symbol = SymbolType::kw_minus;
                }
                break;
            }
            case '*': {
                it = next;
                if (auto [codepoint, next] = DecodeUTF8(it, end); codepoint == '*') {
                    it = next;
                    if (auto [codepoint, next] = DecodeUTF8(it, end); codepoint == '=') {
                        it = next;
                        m_end_index = it - m_source_code.cbegin();
                        move_index = 3;
                        symbol = SymbolType::kw_power_assign;
                    }
                    else {
                        m_end_index = it - m_source_code.cbegin();
                        move_index = 2;
                        symbol = SymbolType::kw_power;
                    }
                }
                else if (auto [codepoint, next] = DecodeUTF8(it, end); codepoint == '=') {
                    it = next;
                    m_end_index = it - m_source_code.cbegin();
                    move_index = 2;
                    symbol = SymbolType::kw_star_assign;
                }
                else {
                    m_end_index = it - m_source_code.cbegin();
                    move_index = 1;
                    symbol = SymbolType::kw_star;
                }
                break;
            }
            case '/': {
                it = next;
                if (auto [codepoint, next] = DecodeUTF8(it, end); codepoint == '/') {
                    it = next;
                    if (auto [codepoint, next] = DecodeUTF8(it, end); codepoint == '=') {
                        it = next;
                        m_end_index = it - m_source_code.cbegin();
                        move_index = 3;
                        symbol = SymbolType::kw_slash_slash_assign;
                    }
                    else {
                        m_end_index = it - m_source_code.cbegin();
                        move_index = 2;
                        symbol = SymbolType::kw_slash_slash;
                    }
                }
                else if (auto [codepoint, next] = DecodeUTF8(it, end); codepoint == '=') {
                    it = next;
                    m_end_index = it - m_source_code.cbegin();
                    move_index = 2;
                    symbol = SymbolType::kw_slash_assign;
                }
                else {
                    m_end_index = it - m_source_code.cbegin();
                    move_index = 1;
                    symbol = SymbolType::kw_slash;
                }
                break;
            }
            case '%': {
                it = next;
                if (auto [codepoint, next] = DecodeUTF8(it, end); codepoint == '=') {
                    it = next;
                    m_end_index = it - m_source_code.cbegin();
                    move_index = 2;
                    symbol = SymbolType::kw_modulo_assign;
                }
                else {
                    m_end_index = it - m_source_code.cbegin();
                    move_index = 1;
                    symbol = SymbolType::kw_modulo;
                }
                break;
            }
            case '@': {
                it = next;
                if (auto [codepoint, next] = DecodeUTF8(it, end); codepoint == '=') {
                    it = next;
                    m_end_index = it - m_source_code.cbegin();
                    move_index = 2;
                    symbol = SymbolType::kw_matrice_assign;
                }
                else {
                    m_end_index = it - m_source_code.cbegin();
                    move_index = 1;
                    symbol = SymbolType::kw_matrice;
                }
                break;
            }
            case '&': {
                it = next;
                if (auto [codepoint, next] = DecodeUTF8(it, end); codepoint == '=') {
                    it = next;
                    m_end_index = it - m_source_code.cbegin();
                    move_index = 2;
                    symbol = SymbolType::kw_bit_and_assign;
                }
                else {
                    m_end_index = it - m_source_code.cbegin();
                    move_index = 1;
                    symbol = SymbolType::kw_bit_and;
                }
                break;
            }
            case '|': {
                it = next;
                if (auto [codepoint, next] = DecodeUTF8(it, end); codepoint == '=') {
                    it = next;
                    m_end_index = it - m_source_code.cbegin();
                    move_index = 2;
                    symbol = SymbolType::kw_bit_or_assign;
                }
                else {
                    m_end_index = it - m_source_code.cbegin();
                    move_index = 1;
                    symbol = SymbolType::kw_bit_or;
                }
                break;
            }
            case '^': {
                it = next;
                if (auto [codepoint, next] = DecodeUTF8(it, end); codepoint == '=') {
                    it = next;
                    m_end_index = it - m_source_code.cbegin();
                    move_index = 2;
                    symbol = SymbolType::kw_bit_xor_assign;
                }
                else {
                    m_end_index = it - m_source_code.cbegin();
                    move_index = 1;
                    symbol = SymbolType::kw_bit_xor;
                }
                break;
            }
            case '<': {
                it = next;
                if (auto [codepoint, next] = DecodeUTF8(it, end); codepoint == '<') {
                    it = next;
                    if (auto [codepoint, next] = DecodeUTF8(it, end); codepoint == '=') {
                        it = next;
                        m_end_index = it - m_source_code.cbegin();
                        move_index = 3;
                        symbol = SymbolType::kw_shift_left_assign;
                    }
                    else {
                        m_end_index = it - m_source_code.cbegin();
                        move_index = 2;
                        symbol = SymbolType::kw_shift_left;
                    }
                }
                else if (auto [codepoint, next] = DecodeUTF8(it, end); codepoint == '=') {
                    it = next;
                    m_end_index = it - m_source_code.cbegin();
                    move_index = 2;
                    symbol = SymbolType::kw_less_equal;
                }
                else {
                    m_end_index = it - m_source_code.cbegin();
                    move_index = 1;
                    symbol = SymbolType::kw_less;
                }
                break;
            }
            case '>': {
                it = next;
                if (auto [codepoint, next] = DecodeUTF8(it, end); codepoint == '>') {
                    it = next;
                    if (auto [codepoint, next] = DecodeUTF8(it, end); codepoint == '=') {
                        it = next;
                        m_end_index = it - m_source_code.cbegin();
                        move_index = 3;
                        symbol = SymbolType::kw_shift_right_assign;
                    }
                    else {
                        m_end_index = it - m_source_code.cbegin();
                        move_index = 2;
                        symbol = SymbolType::kw_shift_right;
                    }
                }
                else if (auto [codepoint, next] = DecodeUTF8(it, end); codepoint == '=') {
                    it = next;
                    m_end_index = it - m_source_code.cbegin();
                    move_index = 2;
                    symbol = SymbolType::kw_greater_equal;
                }
                else {
                    m_end_index = it - m_source_code.cbegin();
                    move_index = 1;
                    symbol = SymbolType::kw_greater;
                }
                break;
            }
            case '=': {
                it = next;
                if (auto [codepoint, next] = DecodeUTF8(it, end); codepoint == '=') {
                    it = next;
                    m_end_index = it - m_source_code.cbegin();
                    move_index = 2;
                    symbol = SymbolType::kw_equal;
                }
                else {
                    m_end_index = it - m_source_code.cbegin();
                    move_index = 1;
                    symbol = SymbolType::kw_assign;
                }
                break;
            }
            case ':': {
                it = next;
                if (auto [codepoint, next] = DecodeUTF8(it, end); codepoint == '=') {
                    it = next;
                    m_end_index = it - m_source_code.cbegin();
                    move_index = 2;
                    symbol = SymbolType::kw_colon_assign;
                }
                else {
                    m_end_index = it - m_source_code.cbegin();
                    move_index = 1;
                    symbol = SymbolType::kw_colon;
                }
                break;
            }
            case '!': {
                it = next;
                if (auto [codepoint, next] = DecodeUTF8(it, end); codepoint == '=') {
                    it = next;
                    m_end_index = it - m_source_code.cbegin();
                    move_index = 2;
                    symbol = SymbolType::kw_not_equal;
                }
                else {
                    m_end_index = it - m_source_code.cbegin();
                    move_index = 1;
                    symbol = SymbolType::kw_bang;
                }
                break;
            }
            case '~': {
                it = next;
                m_end_index = it - m_source_code.cbegin();
                move_index = 1;
                symbol = SymbolType::kw_bit_not;
                break;
            }
            case ',': {
                it = next;
                m_end_index = it - m_source_code.cbegin();
                move_index = 1;
                symbol = SymbolType::kw_comma;
                break;
            }
            case ';': {
                it = next;
                m_end_index = it - m_source_code.cbegin();
                move_index = 1;
                symbol = SymbolType::kw_semicolon;
                break;
            }
            case '(': {
                it = next;
                m_end_index = it - m_source_code.cbegin();
                move_index = 1;
                symbol = SymbolType::kw_start_parenthesis;
                m_Parenthesis_stack.push(')');
                break;
            }
            case '[': {
                it = next;
                m_end_index = it - m_source_code.cbegin();
                move_index = 1;
                symbol = SymbolType::kw_start_bracket;
                m_Parenthesis_stack.push(']');
                break;
            }
            case '{': {
                it = next;
                m_end_index = it - m_source_code.cbegin();
                move_index = 1;
                symbol = SymbolType::kw_start_brace;
                m_Parenthesis_stack.push('}');
                break;
            }



            default:
                break;
        }

        m_symbols.push_back(
            std::make_shared<Symbol>(
                symbol,
                m_line,
                m_column,
                m_start_index,
                m_end_index,
                m_prefix,
                m_trailer));

        m_column += move_index;
    }
}