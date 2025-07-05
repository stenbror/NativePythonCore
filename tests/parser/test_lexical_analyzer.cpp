//
// Created by Richard Magnor Stenbro on 05/07/2025.
//

#include <boost/test/unit_test.hpp>
#include <parser/Symbol.h>

#include "parser/Lexer.h"

using NativePythonCore::Parser::SymbolType;
using NativePythonCore::Parser::Trivia;
using NativePythonCore::Parser::NewlineTrivia;
using NativePythonCore::Parser::CommentTrivia;
using NativePythonCore::Parser::WhitespaceTrivia;
using NativePythonCore::Parser::Symbol;
using NativePythonCore::Parser::LiteralSymbol;
using NativePythonCore::Parser::Lexer;

BOOST_AUTO_TEST_SUITE(lexical_analyzer_tests)

BOOST_AUTO_TEST_CASE(test_lexer_empty_source_code)
{
    auto lexer = new NativePythonCore::Parser::Lexer(u8"", 8);

    BOOST_TEST(lexer->GetNextSymbol()->GetSymbolKind() == SymbolType::kw_eof);
    BOOST_TEST(lexer->SymbolIndex() == 0);
}

BOOST_AUTO_TEST_CASE(test_lexer_empty_source_code_with_index)
{
    auto lexer = new NativePythonCore::Parser::Lexer(u8"", 8);

    BOOST_TEST(lexer->GetNextSymbol(5)->GetSymbolKind() == SymbolType::kw_eof);
    BOOST_TEST(lexer->SymbolIndex() == 0);
}

BOOST_AUTO_TEST_CASE(test_operator_plus_assign) {
    auto lex = new Lexer(u8"+=", 8);
    auto symbol = lex->GetNextSymbol();

    BOOST_TEST(symbol->GetSymbolKind() == SymbolType::kw_plus_assign);
    BOOST_TEST(symbol->GetLine() == 1);
    BOOST_TEST(symbol->GetColumn() == 1);
    BOOST_TEST(symbol->GetStartIndex() == 0);
    BOOST_TEST(symbol->GetEndIndex() == 2);
}

BOOST_AUTO_TEST_CASE(test_operator_plus) {
    auto lex = new Lexer(u8"+", 8);
    auto symbol = lex->GetNextSymbol();

    BOOST_TEST(symbol->GetSymbolKind() == SymbolType::kw_plus);
    BOOST_TEST(symbol->GetLine() == 1);
    BOOST_TEST(symbol->GetColumn() == 1);
    BOOST_TEST(symbol->GetStartIndex() == 0);
    BOOST_TEST(symbol->GetEndIndex() == 1);
}

BOOST_AUTO_TEST_CASE(test_operator_minus_assign) {
    const auto lex = new Lexer(u8"-=", 8);
    const auto symbol = lex->GetNextSymbol();

    BOOST_TEST(symbol->GetSymbolKind() == SymbolType::kw_minus_assign);
    BOOST_TEST(symbol->GetLine() == 1);
    BOOST_TEST(symbol->GetColumn() == 1);
    BOOST_TEST(symbol->GetStartIndex() == 0);
    BOOST_TEST(symbol->GetEndIndex() == 2);
}

BOOST_AUTO_TEST_CASE(test_operator_arrow) {
    auto lex = new Lexer(u8"->", 8);
    auto symbol = lex->GetNextSymbol();

    BOOST_TEST(symbol->GetSymbolKind() == SymbolType::kw_arrow);
    BOOST_TEST(symbol->GetLine() == 1);
    BOOST_TEST(symbol->GetColumn() == 1);
    BOOST_TEST(symbol->GetStartIndex() == 0);
    BOOST_TEST(symbol->GetEndIndex() == 2);
}

BOOST_AUTO_TEST_CASE(test_operator_minus) {
    auto lex = new Lexer(u8"-", 8);
    auto symbol = lex->GetNextSymbol();

    BOOST_TEST(symbol->GetSymbolKind() == SymbolType::kw_minus);
    BOOST_TEST(symbol->GetLine() == 1);
    BOOST_TEST(symbol->GetColumn() == 1);
    BOOST_TEST(symbol->GetStartIndex() == 0);
    BOOST_TEST(symbol->GetEndIndex() == 1);
}

BOOST_AUTO_TEST_CASE(test_operator_power_assign) {
    const auto lex = new Lexer(u8"**=", 8);
    const auto symbol = lex->GetNextSymbol();

    BOOST_TEST(symbol->GetSymbolKind() == SymbolType::kw_power_assign);
    BOOST_TEST(symbol->GetLine() == 1);
    BOOST_TEST(symbol->GetColumn() == 1);
    BOOST_TEST(symbol->GetStartIndex() == 0);
    BOOST_TEST(symbol->GetEndIndex() == 3);
}

BOOST_AUTO_TEST_CASE(test_operator_power) {
    const auto lex = new Lexer(u8"**", 8);
    const auto symbol = lex->GetNextSymbol();

    BOOST_TEST(symbol->GetSymbolKind() == SymbolType::kw_power);
    BOOST_TEST(symbol->GetLine() == 1);
    BOOST_TEST(symbol->GetColumn() == 1);
    BOOST_TEST(symbol->GetStartIndex() == 0);
    BOOST_TEST(symbol->GetEndIndex() == 2);
}

BOOST_AUTO_TEST_CASE(test_operator_star_assign) {
    const auto lex = new Lexer(u8"*=", 8);
    const auto symbol = lex->GetNextSymbol();

    BOOST_TEST(symbol->GetSymbolKind() == SymbolType::kw_star_assign);
    BOOST_TEST(symbol->GetLine() == 1);
    BOOST_TEST(symbol->GetColumn() == 1);
    BOOST_TEST(symbol->GetStartIndex() == 0);
    BOOST_TEST(symbol->GetEndIndex() == 2);
}

BOOST_AUTO_TEST_CASE(test_operator_star) {
    const auto lex = new Lexer(u8"*", 8);
    const auto symbol = lex->GetNextSymbol();

    BOOST_TEST(symbol->GetSymbolKind() == SymbolType::kw_star);
    BOOST_TEST(symbol->GetLine() == 1);
    BOOST_TEST(symbol->GetColumn() == 1);
    BOOST_TEST(symbol->GetStartIndex() == 0);
    BOOST_TEST(symbol->GetEndIndex() == 1);
}

BOOST_AUTO_TEST_CASE(test_operator_slash_slash_assign) {
    const auto lex = new Lexer(u8"//=", 8);
    const auto symbol = lex->GetNextSymbol();

    BOOST_TEST(symbol->GetSymbolKind() == SymbolType::kw_slash_slash_assign);
    BOOST_TEST(symbol->GetLine() == 1);
    BOOST_TEST(symbol->GetColumn() == 1);
    BOOST_TEST(symbol->GetStartIndex() == 0);
    BOOST_TEST(symbol->GetEndIndex() == 3);
}

BOOST_AUTO_TEST_CASE(test_operator_slash_slash) {
    const auto lex = new Lexer(u8"//", 8);
    const auto symbol = lex->GetNextSymbol();

    BOOST_TEST(symbol->GetSymbolKind() == SymbolType::kw_slash_slash);
    BOOST_TEST(symbol->GetLine() == 1);
    BOOST_TEST(symbol->GetColumn() == 1);
    BOOST_TEST(symbol->GetStartIndex() == 0);
    BOOST_TEST(symbol->GetEndIndex() == 2);
}

BOOST_AUTO_TEST_CASE(test_operator_slash_assign) {
    const auto lex = new Lexer(u8"/=", 8);
    const auto symbol = lex->GetNextSymbol();

    BOOST_TEST(symbol->GetSymbolKind() == SymbolType::kw_slash_assign);
    BOOST_TEST(symbol->GetLine() == 1);
    BOOST_TEST(symbol->GetColumn() == 1);
    BOOST_TEST(symbol->GetStartIndex() == 0);
    BOOST_TEST(symbol->GetEndIndex() == 2);
}

BOOST_AUTO_TEST_CASE(test_operator_slash) {
    const auto lex = new Lexer(u8"/", 8);
    const auto symbol = lex->GetNextSymbol();

    BOOST_TEST(symbol->GetSymbolKind() == SymbolType::kw_slash);
    BOOST_TEST(symbol->GetLine() == 1);
    BOOST_TEST(symbol->GetColumn() == 1);
    BOOST_TEST(symbol->GetStartIndex() == 0);
    BOOST_TEST(symbol->GetEndIndex() == 1);
}

BOOST_AUTO_TEST_CASE(test_operator_modulo_assign) {
    auto lex = new Lexer(u8"%=", 8);
    auto symbol = lex->GetNextSymbol();

    BOOST_TEST(symbol->GetSymbolKind() == SymbolType::kw_modulo_assign);
    BOOST_TEST(symbol->GetLine() == 1);
    BOOST_TEST(symbol->GetColumn() == 1);
    BOOST_TEST(symbol->GetStartIndex() == 0);
    BOOST_TEST(symbol->GetEndIndex() == 2);
}

BOOST_AUTO_TEST_CASE(test_operator_modulo) {
    auto lex = new Lexer(u8"%", 8);
    auto symbol = lex->GetNextSymbol();

    BOOST_TEST(symbol->GetSymbolKind() == SymbolType::kw_modulo);
    BOOST_TEST(symbol->GetLine() == 1);
    BOOST_TEST(symbol->GetColumn() == 1);
    BOOST_TEST(symbol->GetStartIndex() == 0);
    BOOST_TEST(symbol->GetEndIndex() == 1);
}

BOOST_AUTO_TEST_SUITE_END()
