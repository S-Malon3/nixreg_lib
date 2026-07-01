#include <boost/test/unit_test.hpp>
#include <bitset>
#include "nixreg/bitbuffer.hpp"

using namespace nixreg;

BOOST_AUTO_TEST_SUITE(bitbuffer_tests)

// Test initialization without error
BOOST_AUTO_TEST_CASE(buffer_initializes_without_error) {
	std::bitset<64> data;
	BOOST_CHECK_NO_THROW(BitBuffer buf(data, 0, 32));
}

// Test initialization where size and offset make the final bit of the buffer
// the final bit of the data, without error
BOOST_AUTO_TEST_CASE(buffer_initializes_final_half_without_error) {
	std::bitset<64> data;
	BOOST_CHECK_NO_THROW(BitBuffer buf(data, 32, 32));
}

// Test buffer is usable after initialization
BOOST_AUTO_TEST_CASE(bitbuffer_initializes_and_is_usable) {
	std::bitset<64> data;
	BitBuffer buf(data, 0, 32);
	BOOST_TEST(buf.get_bit(0) == false); // default initialized bitset is all zeros
}

// Test setting 0th bit to 1
BOOST_AUTO_TEST_CASE(set_and_get_single_bit) {
	std::bitset<64> data;
	BitBuffer buf(data, 0, 32);

	buf.set_bit(0, true);
	BOOST_TEST(buf.get_bit(0));
}

// Test offset writes to correct position in data
BOOST_AUTO_TEST_CASE(offset_writes_to_correct_position) {
	std::bitset<64> data;
	BitBuffer buf(data, 32, 32);

	buf.set_bit(0, true);
	BOOST_TEST(data[32]);
}

// writing to index 32 throws in a 32 width buffer throws error
BOOST_AUTO_TEST_CASE(set_bit_out_of_range_throws) {
	std::bitset<64> data;
	BitBuffer buf(data, 0, 32);

	BOOST_CHECK_THROW(buf.set_bit(32, true), std::out_of_range);
}

// Making a bit buffer bigger than the data throws std::invalid_argument
BOOST_AUTO_TEST_CASE(buffer_larger_than_bitset_throws) {
	std::bitset<16> data;

	BOOST_CHECK_THROW(BitBuffer buf(data, 0, 32), std::invalid_argument);
}

// read and write bits to buffer
BOOST_AUTO_TEST_CASE(write_and_read_bits) {
	std::bitset<64> data;
	BitBuffer buf(data, 0, 32);

	buf.write_bits(0b1010, 4);
	BOOST_TEST(buf.read_bits(4) == 0b1010);
}

// read and write hex to buffer
BOOST_AUTO_TEST_CASE(read_and_write_hex) {
	std::bitset<16> data;
	BitBuffer buf(data, 0, 8);

	buf.write_bits(0xAF, 8);
	BOOST_TEST(buf.read_bits(8) == 0xAF);
}

//write to multiple buffers in one bitset
BOOST_AUTO_TEST_CASE(multiple_buffers_independent_ranges) {
	std::bitset<64> data;
	BitBuffer buf1(data, 0, 32);
	BitBuffer buf2(data, 32, 32);

	buf1.write_bits(0xFF, 8);
	buf2.write_bits(0xAA, 8);

	BOOST_TEST(buf1.read_bits(8) == 0xFF);
	BOOST_TEST(buf2.read_bits(8) == 0xAA);
}

//writing a size bigger than buffer throws error
BOOST_AUTO_TEST_CASE(write_exceeding_width_throws) {
	std::bitset<64> data;
	BitBuffer buf(data, 0, 8);

	BOOST_CHECK_THROW(buf.write_bits(0xFFFF, 16), std::out_of_range);
}

//read bits using []
BOOST_AUTO_TEST_CASE(subscript_operator_reads_bit) {
	std::bitset<64> data;
	BitBuffer buf(data, 0, 32);
	buf.write_bits(0b1010, 4);
	BOOST_TEST(buf[0] == false);
	BOOST_TEST(buf[1] == true);
}

//write and read to buffer using =
BOOST_AUTO_TEST_CASE(assignment_operator_reads_writes_value) {
	std::bitset<64> data;
	BitBuffer buf(data, 0, 32);
	buf = 0xDEADBEEF;

	BOOST_TEST(static_cast<size_t>(buf) == 0xDEADBEEF);
}

BOOST_AUTO_TEST_SUITE_END()
