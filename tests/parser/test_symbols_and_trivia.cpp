//
// Created by Richard Magnor Stenbro on 05/07/2025.
//

#include <boost/test/unit_test.hpp>
#include <parser/Symbol.h>

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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE_END()
