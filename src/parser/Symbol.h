//
// Created by Richard Magnor Stenbro on 05/07/2025.
//

#ifndef SYMBOL_H
#define SYMBOL_H

#include <vector>
#include <memory>
#include <string>

// Enum token for each symbol type
enum class SymbolType {
    kw_eof,
    kw_newline,
    kw_indent,
    kw_dedent,
    kw_false,
    kw_none,
    kw_true,
    kw_and,
    kw_as,
    kw_assert,
    kw_async,
    kw_await,
    kw_break,
    kw_class,
    kw_continue,
    kw_def,
    kw_del,
    kw_elif,
    kw_else,
    kw_except,
    kw_finally,
    kw_for,
    kw_from,
    kw_global,
    kw_if,
    kw_import,
    kw_in,
    kw_is,
    kw_lambda,
    kw_nonlocal,
    kw_not,
    kw_or,
    kw_pass,
    kw_raise,
    kw_return,
    kw_try,
    kw_while,
    kw_with,
    kw_yield,
    kw_identifier,
    kw_integer,
    kw_float,
    kw_string,
    kw_comment,
    kw_plus,
    kw_minus,
    kw_star,
    kw_power,
    kw_slash,
    kw_slash_slash,
    kw_modulo,
    kw_matrice,
    kw_shift_left,
    kw_shift_right,
    kw_bit_and,
    kw_bit_or,
    kw_bit_xor,
    kw_bit_not,
    kw_colon_assign,
    kw_less,
    kw_less_equal,
    kw_greater,
    kw_greater_equal,
    kw_equal,
    kw_not_equal,
    kw_start_parenthesis,
    kw_end_parenthesis,
    kw_start_bracket,
    kw_end_bracket,
    kw_start_brace,
    kw_end_brace,
    kw_comma,
    kw_colon,
    kw_bang,
    kw_dot,
    kw_semicolon,
    kw_assign,
    kw_arrow,
    kw_plus_assign,
    kw_minus_assign,
    kw_star_assign,
    kw_slash_assign,
    kw_slash_slash_assign,
    kw_modulo_assign,
    kw_matrice_assign,
    kw_power_assign,
    kw_shift_left_assign,
    kw_shift_right_assign,
    kw_bit_and_assign,
    kw_bit_or_assign,
    kw_bit_xor_assign
};

// Base class for trivia structures
class Trivia {
    unsigned long m_start_index;
    unsigned long m_end_index;

public:
    Trivia(unsigned long start_index, unsigned long end_index);
    [[nodiscard]] unsigned long GetStartIndex() const;
    [[nodiscard]] unsigned long GetEndIndex() const;
};

// Symbol data structure
class Symbol {
    SymbolType m_symbol;
    unsigned long m_line;
    unsigned long m_column;
    unsigned long m_start_index;
    unsigned long m_end_index;
    std::vector<std::shared_ptr<Trivia>> m_prefix;
    std::vector<std::shared_ptr<Trivia>> m_trailer;

public:
    Symbol(SymbolType symbol, unsigned long line, unsigned long column, unsigned long start_index, unsigned long end_index, std::vector<std::shared_ptr<Trivia>> prefix = {}, std::vector<std::shared_ptr<Trivia>> trailer = {});

    [[nodiscard]] SymbolType GetSymbolKind() const;
    [[nodiscard]] unsigned long GetLine() const;
    [[nodiscard]] unsigned long GetColumn() const;
    [[nodiscard]] unsigned long GetStartIndex() const;
    [[nodiscard]] unsigned long GetEndIndex() const;
    std::vector<std::shared_ptr<Trivia>> GetPrefix();
    std::vector<std::shared_ptr<Trivia>> GetTrailer();
};

// Extension to symbol for literals
class LiteralSymbol : public Symbol {
    std::basic_string<char8_t> m_value;

public:
    LiteralSymbol(SymbolType symbol, unsigned long line, unsigned long column, unsigned long start_index, unsigned long end_index, std::basic_string<char8_t> value);

    std::basic_string<char8_t> GetValue();
};

#endif //SYMBOL_H
