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

BOOST_AUTO_TEST_SUITE_END()
