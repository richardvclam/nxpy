#pragma once
#include <cstdint>

namespace nl {
	//Type of node data
	enum class nodetype : uint16_t {
		none = 0,
		integer = 1,
		real = 2,
		string = 3,
		vector = 4,
		bitmap = 5,
		audio = 6,
	};

#pragma pack(push, 1)
	struct nodedata {
		uint32_t const name;
		uint32_t const children;
		uint16_t const num;
		nodetype const type;
		union {
			int64_t const ireal;
			double const dreal;
			uint32_t const string;
			int32_t const vector[2];
			struct {
				uint32_t index;
				uint16_t width;
				uint16_t height;
			} const bitmap;
			struct {
				uint32_t index;
				uint32_t length;
			} const audio;
		};
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct fileheader {
		uint32_t const magic;
		uint32_t const node_count;
		uint64_t const node_offset;
		uint32_t const string_count;
		uint64_t const string_offset;
		uint32_t const bitmap_count;
		uint64_t const bitmap_offset;
		uint32_t const audio_count;
		uint64_t const audio_offset;
	};
#pragma pack(pop)

	struct filedata {
		void const * base = nullptr;
		nodedata const * node_table = nullptr;
		uint64_t const * string_table = nullptr;
		uint64_t const * bitmap_table = nullptr;
		uint64_t const * audio_table = nullptr;
		fileheader const * header = nullptr;
#ifdef _WIN32
		void * file_handle = nullptr;
		void * map = nullptr;
#else
		int file_handle = 0;
		size_t size = 0;
#endif
	};
}