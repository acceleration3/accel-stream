#include <accel/stream>

#include <iostream>
#include <cassert>
#include <string>

using namespace accel;

int main(int argc, char* argv[])
{
	// File output stream
	{
		stream::file_output_stream stream("test.bin", stream::file_mode::binary);
		for (std::size_t i = 0; i < 30; i++)
			stream << 3;

		stream << "This is a test string.";
	}

	// File input stream
	{
		stream::file_input_stream stream("test.bin", stream::file_mode::binary);

		for (std::size_t i = 0; i < 30; i++)
		{
			int value = 0;
			stream >> value;
			assert(value == 3);			
		}

		std::string test;
		stream >> test;
		assert(test == "This is a test string.");
	}


	// Memory input stream
	{
		std::vector<char> test = { 0x01, 0x00, 0x03, 0x00 };
		stream::memory_input_stream<> stream(test);

		std::uint16_t a = 0;
		std::uint16_t b = 0;
		stream.read_object_le(a);
		stream.read_object_le(b);
		assert(a == 1);
		assert(b == 3);
	}

	{
		stream::memory_output_stream<> stream;

		std::uint16_t a = 0x0001;
		std::uint16_t b = 0x0002;
		stream.write_object_le(a);
		stream.write_object_le(b);

		auto data = stream.data();
		assert(data[0] == 1);
		assert(data[1] == 0);
		assert(data[2] == 2);
		assert(data[3] == 0);
	}


	std::cout << "All tests completed sucessfully.";
	return 0;
}