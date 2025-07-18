//
// Created by Richard Magnor Stenbro on 05/07/2025.
//

#include "Symbol.h"

#include <utility>

using NativePythonCore::Parser::SymbolType;
using NativePythonCore::Parser::Trivia;
using NativePythonCore::Parser::NewlineTrivia;
using NativePythonCore::Parser::CommentTrivia;
using NativePythonCore::Parser::WhitespaceTrivia;
using NativePythonCore::Parser::Symbol;
using NativePythonCore::Parser::LiteralSymbol;

// Base class for Trivia structure /////////////////////////////////////////////////////////////////////////////////////
Trivia::Trivia(unsigned long start_index, unsigned long end_index) {
    m_start_index = start_index;
    m_end_index = end_index;
}

unsigned long Trivia::GetStartIndex() const {
    return m_start_index;
}

unsigned long Trivia::GetEndIndex() const {
    return m_end_index;
}

// Newline trivia methods //////////////////////////////////////////////////////////////////////////////////////////////
NewlineTrivia::NewlineTrivia(
        unsigned long start_index,
        unsigned long end_index,
        bool is_carriage_return,
        bool is_line_feed)
            : Trivia(start_index, end_index) {

    m_is_carriage_return = is_carriage_return;
    m_is_line_feed = is_line_feed;
}

bool NewlineTrivia::IsCarriageReturn() const {
    return m_is_carriage_return;
}

bool NewlineTrivia::IsLineFeed() const {
    return m_is_line_feed;
}

// Comment trivia methods //////////////////////////////////////////////////////////////////////////////////////////////
CommentTrivia::CommentTrivia(
        unsigned long start_index,
        unsigned long end_index,
        std::basic_string<char8_t> comment)
            : Trivia(start_index, end_index) {

    m_comment = std::move(comment);
}

std::basic_string<char8_t> CommentTrivia::GetComment() {
    return m_comment;
}

// Whitespace trivia methods ///////////////////////////////////////////////////////////////////////////////////////////
WhitespaceTrivia::WhitespaceTrivia(
        unsigned long start_index,
        unsigned long end_index,
        const WhitespaceType type)
            : Trivia(start_index, end_index) {

    m_type = type;
}

bool WhitespaceTrivia::IsTabulator() const {
    return m_type == WhitespaceType::Tabulator;
}

bool WhitespaceTrivia::IsLineContinuation() const {
    return m_type == WhitespaceType::LineContinuation;
}

bool WhitespaceTrivia::IsSpace() const {
    return m_type == WhitespaceType::Space;
}

// Base symbol class methods and constructors //////////////////////////////////////////////////////////////////////////
Symbol::Symbol(
        SymbolType symbol,
        unsigned long line,
        unsigned long column,
        unsigned long start_index,
        unsigned long end_index,
        std::vector<std::shared_ptr<Trivia>> prefix,
        std::vector<std::shared_ptr<Trivia>> trailer) {

    m_symbol = symbol;
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
        const unsigned long line,
        const unsigned long column,
        const unsigned long start_index,
        const unsigned long end_index,
        std::basic_string<char8_t> value,
        std::vector<std::shared_ptr<Trivia>> prefix,
        std::vector<std::shared_ptr<Trivia>> trailer)
            : Symbol(symbol, line, column, start_index, end_index, std::move(prefix), std::move(trailer)) {
    m_value = std::move(value);
}

std::basic_string<char8_t> LiteralSymbol::GetValue() {
    return m_value;
}