#include <accel/stream>

#include <iostream>
#include <cassert>
#include <string>

using namespace accel;

int main(int argc, char* argv[])
{
	{
		stream::file_output_stream stream("test.bin", stream::file_modes::binary);
		for (std::size_t i = 0; i < 30; i++)
			stream << 3;
	}

	{
		stream::file_input_stream stream("test.bin", stream::file_modes::binary);

		for (std::size_t i = 0; i < 30; i++)
		{
			int value = 0;
			stream >> value;
			assert(value == 3);			
		}
	}

	{
		char test[4] = { 0x01, 0x00, 0x03, 0x00 };
		stream::memory_input_stream stream(test);

		std::uint16_t a = 0;
		std::uint16_t b = 0;
		stream.read_object_le(a);
		stream.read_object_le(b);
		assert(a == 1);
		assert(b == 3);
	}

	{
		char test[6];
		stream::memory_output_stream stream(test);

		std::uint16_t a = 0x0001;
		std::uint16_t b = 0x0002;
		stream.write_object_be(a);
		stream.write_object_be(b);

		auto data = stream.get_data();
		assert(data[0] == 0);
		assert(data[1] == 1);
		assert(data[2] == 0);
		assert(data[3] == 2);

		stream.seek_write(2, stream::seek_references::begining);
		stream.write_object_le(4);

		data = stream.get_data();
		assert(data[0] == 0);
		assert(data[1] == 1);
		assert(data[2] == 4);
		assert(data[3] == 0);
		assert(data[4] == 0);
		assert(data[5] == 0);
	}

	{
		std::uint16_t a = 0x0001;
		std::uint16_t b = 0x0002;
		stream::dynamic_output_stream stream;
		stream.write_object_be(a);
		stream.write_object_be(b);
		auto data = stream.get_data();
		assert(stream.get_size() == 4);
		assert(data[0] == 0);
		assert(data[1] == 1);
		assert(data[2] == 0);
		assert(data[3] == 2);
		stream.write_object_le(b);
		stream.write_object_le(a);

		data = stream.get_data();
		assert(stream.get_size() == 8);
		assert(data[0] == 0);
		assert(data[1] == 1);
		assert(data[2] == 0);
		assert(data[3] == 2);
		assert(data[4] == 2);
		assert(data[5] == 0);
		assert(data[6] == 1);
		assert(data[7] == 0);
	}

	std::cout << "All tests completed sucessfully.";
	return 0;
}