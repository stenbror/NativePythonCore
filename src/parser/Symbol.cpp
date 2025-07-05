//
// Created by Richard Magnor Stenbro on 05/07/2025.
//

#include "Symbol.h"

#include <utility>

// Base symbol class methods and constructors //////////////////////////////////////////////////////////////////////////
Symbol::Symbol(
        SymbolType symbol,
        unsigned long line,
        unsigned long column,
        unsigned long start_index,
        unsigned long end_index,
        std::vector<std::shared_ptr<Trivia>> prefix,
        std::vector<std::shared_ptr<Trivia>> trailer) {

    m_line = line;
    m_column = column;
    m_start_index = start_index;
    m_end_index = end_index;
    m_prefix = std::move(prefix);
    m_trailer = std::move(trailer);
}

SymbolType Symbol::GetSymbolKind() const {
    return m_symbol;
}

unsigned long Symbol::GetLine() const {
    return m_line;
}

unsigned long Symbol::GetColumn() const {
    return m_column;
}

unsigned long Symbol::GetStartIndex() const {
    return m_start_index;
}

unsigned long Symbol::GetEndIndex() const {
    return m_end_index;
}

std::vector<std::shared_ptr<Trivia>> Symbol::GetPrefix() {
    return m_prefix;
}

std::vector<std::shared_ptr<Trivia>> Symbol::GetTrailer() {
    return m_trailer;
}

// Literal symbol class methods and constructor ////////////////////////////////////////////////////////////////////////
LiteralSymbol::LiteralSymbol(
        SymbolType symbol,
        unsigned long line,
        unsigned long column,
        unsigned long start_index,
        unsigned long end_index,
        std::basic_string<char8_t> value)
            : Symbol(symbol, line, column, start_index, end_index) {
    m_value = std::move(value);
}

std::basic_string<char8_t> LiteralSymbol::GetValue() {
    return m_value;   
}