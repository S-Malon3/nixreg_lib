#include <boost/test/unit_test.hpp>
#include "nixreg/NixieDigitMap.hpp"

using namespace nixreg;

BOOST_AUTO_TEST_SUITE(nixiedigitmap_tests)

// Scattered_NixieDigitMap initializes_without_error
BOOST_AUTO_TEST_CASE(scattered_initializes_without_error) {
	BOOST_CHECK_NO_THROW(NixieDigitMap::scattered({1,3,5,7,9,11,13,15,17,19}));
}

// Contiguous NixieDigitmap initializes without error
BOOST_AUTO_TEST_CASE(contiguous_initializes_without_error) {
	BOOST_CHECK_NO_THROW(NixieDigitMap::contiguous(0));
}

// Scattered_NixieDigitMap initializes with decimal without_error
BOOST_AUTO_TEST_CASE(scattered_initializes_with_decimal_without_error) {
	BOOST_CHECK_NO_THROW(NixieDigitMap::scattered({1,3,5,7,9,11,13,15,17,19}, {.decimal = 21}));
}

// Contiguous NixieDigitmap initializes with decimal without error
BOOST_AUTO_TEST_CASE(contiguous_initializes_with_decimal_without_error) {
	BOOST_CHECK_NO_THROW(NixieDigitMap::contiguous(0, {.decimal = 10}));
}

BOOST_AUTO_TEST_CASE(scattered_reads_back_correct_pins) {
	NixieDigitMap digit = NixieDigitMap::scattered({4,7,2,15,8,1,22,11,6,19});
	BOOST_TEST(digit.pin_for(0) == 19);
}

BOOST_AUTO_TEST_CASE(contiguous_reads_back_correct_pins) {
	NixieDigitMap digit = NixieDigitMap::contiguous(0);
	BOOST_TEST(digit.pin_for(0) == 9);
}

BOOST_AUTO_TEST_CASE(querying_out_of_range_throws) {
	NixieDigitMap digit = NixieDigitMap::contiguous(0);
	BOOST_CHECK_THROW(digit.pin_for(10), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(decimal_reads_back_when_set) {
	NixieDigitMap digit = NixieDigitMap::contiguous(0, {.decimal = 10});
	BOOST_TEST(digit.pin_for_decimal() == 10);
}

BOOST_AUTO_TEST_CASE(decimal_throws_when_not_assigned) {
	NixieDigitMap digit = NixieDigitMap::contiguous(0);
	BOOST_CHECK_THROW(digit.pin_for_decimal(), std::logic_error);
}

BOOST_AUTO_TEST_CASE(has_decimal_true_when_assigned) {
	NixieDigitMap digit = NixieDigitMap::contiguous(0, {.decimal = 10});
	BOOST_TEST(digit.has_decimal());
}

BOOST_AUTO_TEST_CASE(has_decimal_false_when_not_assigned) {
	NixieDigitMap digit = NixieDigitMap::contiguous(0);
	BOOST_TEST(!digit.has_decimal());
}

BOOST_AUTO_TEST_SUITE_END()
