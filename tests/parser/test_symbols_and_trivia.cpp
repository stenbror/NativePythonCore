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

BOOST_AUTO_TEST_SUITE(symbols_and_trivia_tests)

// Test newline Trivia /////////////////////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(test_newline_trivia_1)
{
    auto newline = std::make_shared<NewlineTrivia>(0, 1, true, false);

    BOOST_TEST(newline->GetStartIndex() == 0 );
    BOOST_TEST(newline->GetEndIndex() == 1 );
    BOOST_TEST(newline->IsCarriageReturn() == true );
    BOOST_TEST(newline->IsLineFeed() == false );
}

BOOST_AUTO_TEST_CASE(test_newline_trivia_2)
{
    auto newline = std::make_shared<NewlineTrivia>(0, 1, false, true);

    BOOST_TEST(newline->GetStartIndex() == 0 );
    BOOST_TEST(newline->GetEndIndex() == 1 );
    BOOST_TEST(newline->IsCarriageReturn() == false );
    BOOST_TEST(newline->IsLineFeed() == true );
}

BOOST_AUTO_TEST_CASE(test_newline_trivia_3)
{
    auto newline = std::make_shared<NewlineTrivia>(0, 2, true, true);

    BOOST_TEST(newline->GetStartIndex() == 0 );
    BOOST_TEST(newline->GetEndIndex() == 2 );
    BOOST_TEST(newline->IsCarriageReturn() == true );
    BOOST_TEST(newline->IsLineFeed() == true );
}

// Test whitespace trivia types ////////////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(test_whitespace_tabulator_trivia)
{
    auto whitespace = std::make_shared<WhitespaceTrivia>(0, 1, WhitespaceTrivia::WhitespaceType::Tabulator);

    BOOST_TEST(whitespace->GetStartIndex() == 0 );
    BOOST_TEST(whitespace->GetEndIndex() == 1 );
    BOOST_TEST(whitespace->IsTabulator() == true );
    BOOST_TEST(whitespace->IsLineContinuation() == false );
    BOOST_TEST(whitespace->IsSpace() == false );
}

BOOST_AUTO_TEST_CASE(test_whitespace_linecontinuation_trivia)
{
    auto whitespace = std::make_shared<WhitespaceTrivia>(0, 1, WhitespaceTrivia::WhitespaceType::LineContinuation);

    BOOST_TEST(whitespace->GetStartIndex() == 0 );
    BOOST_TEST(whitespace->GetEndIndex() == 1 );
    BOOST_TEST(whitespace->IsTabulator() == false );
    BOOST_TEST(whitespace->IsLineContinuation() == true );
    BOOST_TEST(whitespace->IsSpace() == false );
}

BOOST_AUTO_TEST_CASE(test_whitespace_space_trivia)
{
    auto whitespace = std::make_shared<WhitespaceTrivia>(0, 1, WhitespaceTrivia::WhitespaceType::Space);

    BOOST_TEST(whitespace->GetStartIndex() == 0 );
    BOOST_TEST(whitespace->GetEndIndex() == 1 );
    BOOST_TEST(whitespace->IsTabulator() == false );
    BOOST_TEST(whitespace->IsLineContinuation() == false );
    BOOST_TEST(whitespace->IsSpace() == true );
}

// Test comment trivia /////////////////////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(test_comment_trivia)
{
    auto comment = std::make_shared<CommentTrivia>(0, 15, u8"# Hello, World!");

    BOOST_TEST(comment->GetStartIndex() == 0);
    BOOST_TEST(comment->GetEndIndex() == 15);
    
    std::string expected(reinterpret_cast<const char*>(u8"# Hello, World!"));
    std::string actual(reinterpret_cast<const char*>(comment->GetComment().c_str()));
    BOOST_TEST(actual == expected);
}

// Simple test for literal symbol //////////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(Test_LiteralSymbol)
{
    auto symbol = std::make_shared<LiteralSymbol>(SymbolType::kw_identifier, 1, 1, 0, 8, u8"__init__", std::vector<std::shared_ptr<Trivia>>(), std::vector<std::shared_ptr<Trivia>>());

    BOOST_TEST(symbol->GetSymbolKind() == SymbolType::kw_identifier);
    BOOST_TEST(symbol->GetLine() == 1);
    BOOST_TEST(symbol->GetColumn() == 1);
    BOOST_TEST(symbol->GetStartIndex() == 0);
    BOOST_TEST(symbol->GetEndIndex() == 8);

    std::string expected(reinterpret_cast<const char*>(u8"__init__"));
    std::string actual(reinterpret_cast<const char*>(symbol->GetValue().c_str()));
    BOOST_TEST(actual == expected);

    BOOST_TEST(symbol->GetPrefix().empty());
    BOOST_TEST(symbol->GetTrailer().empty());
}

BOOST_AUTO_TEST_CASE(test_literal_symbol)
{
    std::vector<std::shared_ptr<Trivia>> prefix{};
    std::vector<std::shared_ptr<Trivia>> trailer{};
    
    auto literal = std::make_shared<LiteralSymbol>(
        SymbolType::kw_string,
        1,       // line
        1,       // column
        0,      // start_index
        11,      // end_index
        std::u8string(u8"Hello World"),
        prefix,
        trailer
    );

    BOOST_TEST(literal->GetSymbolKind() == SymbolType::kw_string);
    BOOST_TEST(literal->GetLine() == 1);
    BOOST_TEST(literal->GetColumn() == 1);
    BOOST_TEST(literal->GetStartIndex() == 0);
    BOOST_TEST(literal->GetEndIndex() == 11);
    
    std::string expected(reinterpret_cast<const char*>(u8"Hello World"));
    std::string actual(reinterpret_cast<const char*>(literal->GetValue().c_str()));
    BOOST_TEST(actual == expected);
    
    BOOST_TEST(literal->GetPrefix().empty());
    BOOST_TEST(literal->GetTrailer().empty());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE_END()