
#define BOOST_TEST_MODULE NativePythonCore Tests
#include <boost/test/unit_test.hpp>
#include <sstream>
#include <library.h>

// Hjelpefunksjon for å fange cout output
class cout_redirect {
    std::streambuf* old;
    std::stringstream stream;
public:
    cout_redirect() : old(std::cout.rdbuf(stream.rdbuf())) {}
    ~cout_redirect() { std::cout.rdbuf(old); }
    std::string get_output() { return stream.str(); }
};

BOOST_AUTO_TEST_SUITE(library_tests)

BOOST_AUTO_TEST_CASE(sanity_check)
{
    BOOST_TEST(true);
}

BOOST_AUTO_TEST_CASE(test_hello)
{
    cout_redirect redirect;
    hello();
    BOOST_TEST(redirect.get_output() == "Hello, World!\n");
}

BOOST_AUTO_TEST_SUITE_END()
