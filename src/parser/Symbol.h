//
// Created by Richard Magnor Stenbro on 05/07/2025.
//

#ifndef SYMBOL_H
#define SYMBOL_H

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

// Symbol data structure
class Symbol {
    SymbolType m_symbol = SymbolType::kw_eof;
};

// Extension to symbol for literals
class LiteralSymbol : public Symbol {

};

#endif //SYMBOL_H
