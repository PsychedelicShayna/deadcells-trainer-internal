#include "ap_infinite_jump.hpp"

APInfiniteJump::APInfiniteJump()
{

}

/*
 *
 * const std::vector<unsigned char>& PATTERN_BYTES {
    0xbd, 0x92, 0xcb, 0x2e, 0x66, 0xbe, 0xfa, 0x43, 0x42, 0x42, 0x42, 0xca, 0x07, 0x9d, 0xc9, 0x48, 0xc9, 0x0b, 0x4a, 0x12, 0x10, 0xbd, 0x13, 0x4e, 0xcb, 0x2e, 0x66, 0xbe, 0xc1, 0x86, 0x4a, 0xab,
    0x31, 0xbd, 0xbd, 0xbd, 0xc9, 0x17, 0x4a, 0xc9, 0xc0, 0xd2, 0x40, 0x42, 0x42, 0xcb, 0x07, 0xbe, 0x71, 0x8b, 0xcb, 0x0f, 0xb2, 0x79, 0x83, 0x4d, 0xc7, 0x50, 0x42, 0x42, 0x42, 0xb0, 0x4d, 0x52,
    0x67, 0xe6, 0x03, 0xf5, 0x43, 0xb0, 0x4d, 0x53, 0x27, 0x92, 0xab, 0x4f, 0x42, 0x42, 0x42, 0xb0, 0x4d, 0x52, 0x6f, 0xce, 0x01, 0xf5, 0x43, 0xb0, 0x4d, 0x53, 0x2f, 0x92, 0xc9, 0x0f, 0x4a, 0xc9,
    0x13, 0x12, 0xcb, 0x17, 0xb6, 0xc7, 0x90, 0x4d, 0xc7, 0x48, 0x42, 0x42, 0x42, 0x71, 0x82, 0xcb, 0x07, 0x8a, 0xab, 0x7b, 0x42, 0x42, 0x42, 0xc9, 0x0f, 0x4a, 0xc9, 0x13, 0x12, 0xcb, 0x17, 0xb6,
    0xc7, 0x90, 0x37, 0x4c, 0xc1, 0xae, 0x4a, 0xfa, 0x02, 0x78, 0x1f, 0x51, 0xbd, 0x92, 0xcb, 0x2e, 0x66, 0xbe, 0xc9, 0x00, 0x1e, 0xcb, 0x07, 0x86, 0xc7, 0x82, 0x37, 0x4c, 0xc1, 0xae, 0x4a, 0xfa,
    0x02, 0x78, 0x1f, 0x51, 0xbd, 0x92, 0xcb, 0x2e, 0x66, 0xbe, 0xc9, 0x0a, 0x1a, 0xcb, 0x0f, 0x8a, 0xc9, 0x17, 0x8a, 0xc7, 0x90, 0x37, 0x4c, 0xc1, 0xae, 0x4a, 0xfa, 0x02, 0x78, 0x1f, 0x51, 0xbd,
    0x92, 0xcb, 0x2e, 0x66, 0xbe, 0xc9, 0x00, 0x5a, 0xcb, 0x07, 0x8e, 0xc7, 0x82, 0x37, 0x4c, 0xc1, 0xae, 0x4a, 0xfa, 0x02, 0x78, 0x1f, 0x51, 0xbd, 0x92, 0xcb, 0x2e, 0x66, 0xbe, 0xc9, 0x4f, 0x72,
    0x03, 0x8f, 0x48, 0xcb, 0x0f, 0x82, 0x71, 0x90, 0xcb, 0x17, 0xfe, 0xc1, 0xae, 0x4e, 0x10, 0x13, 0x12, 0xaa, 0x68, 0xab, 0x06, 0x43, 0xcb, 0x2e, 0x66, 0xbe, 0xc1, 0x86, 0x5a, 0xca, 0x07, 0x9d,
    0xc6, 0x82, 0x4d, 0xc6, 0x7d, 0x42, 0x42, 0x42, 0xc9, 0x0f, 0x4a, 0xc9, 0xd3, 0x66, 0x40, 0x42, 0x42, 0xcb, 0x17, 0xfa, 0xc7, 0x90, 0x4d, 0xc6, 0x69, 0x42, 0x42, 0x42, 0xc9, 0xd3, 0x66, 0x40,
    0x42, 0x42, 0xcb, 0x17, 0xfa, 0xc7, 0x90, 0x37, 0x4c, 0xc1, 0xae, 0x4a, 0xfa, 0x02, 0x78, 0x1f, 0x51, 0xbd, 0x92, 0xcb, 0x2e, 0x66, 0xbe, 0xc1, 0xae, 0x46, 0x10, 0xaa, 0x92, 0xe7, 0xcd, 0x43,
    0xcb, 0x2e, 0x66, 0xbe, 0xc1, 0x86, 0x4a, 0xc9, 0x07, 0x4a, 0xc9, 0xca, 0xd2, 0x40, 0x42, 0x42, 0xcb, 0x0f, 0xbe, 0x03, 0xcb, 0x0f, 0xbe, 0xcb, 0xca, 0xd2, 0x40, 0x42, 0x42, 0x71, 0x90, 0xcb,
    0x17, 0xf6, 0xcb, 0xd2, 0x36, 0x43, 0x42, 0x42, 0xc9, 0x0a, 0x1a, 0xcb, 0x0f, 0xbe, 0xb0, 0x4d, 0x68, 0x83, 0xb0, 0x4d, 0x53, 0x07, 0xea, 0xb0, 0x4d, 0x52, 0x0a, 0x2a, 0xb0, 0x4d, 0x53, 0x0f,
    0xe2, 0xb0, 0x4d, 0x1a, 0x83, 0xb0, 0x4d, 0x53, 0x07, 0xea, 0xb0, 0x4d, 0x52, 0x4f, 0xb6, 0x03, 0xf5, 0x43, 0xb0, 0x4d, 0x53, 0x0f, 0xe2, 0xb0, 0x4d, 0x1b, 0x83, 0xb0, 0x4d, 0x53, 0x07, 0xea,
    0xb0, 0x4d, 0x53, 0xc2, 0x3a, 0x43, 0x42, 0x42, 0xb0, 0x4d, 0x52, 0xd2, 0xca, 0x42, 0x42, 0x42, 0xb0, 0x4d, 0x53, 0x17, 0xea, 0x24, 0x4d, 0x15, 0x8b, 0xb0, 0x4d, 0x53, 0x0f, 0xe2, 0x24, 0x4d,
    0x6d, 0x93, 0x39, 0x40, 0x71, 0x8b, 0x4d, 0xc1, 0x53, 0x42, 0x42, 0x42, 0x24, 0x4d, 0x15, 0xa6, 0xb0, 0x4d, 0x53, 0x27, 0xea, 0xb0, 0x4d, 0x53, 0xe2, 0xca, 0x42, 0x42, 0x42, 0xb0, 0x4d, 0x52,
    0x6f, 0xc6, 0x00, 0xf5, 0x43, 0xb0, 0x4d, 0x53, 0x2f, 0xea, 0x24, 0x4d, 0x15, 0xb4, 0xb0, 0x4d, 0x1e, 0xb7, 0xb0, 0x4d, 0x53, 0x37, 0xea, 0xb0, 0x4d, 0x52, 0x3f, 0x92, 0xb0, 0x4d, 0x1b, 0xb5,
    0xb0, 0x4d, 0x53, 0x37, 0xea, 0xc9, 0x07, 0x4a, 0xb0, 0x4d, 0x53, 0x32, 0x3a, 0xc9, 0xca, 0x1a, 0x43, 0x42, 0x42, 0xcb, 0x0f, 0xde, 0xc7, 0x8b, 0x37, 0x4c, 0xc1, 0xae, 0x4a, 0xfa, 0x02, 0x78,
    0x1f, 0x51, 0xbd, 0x92, 0xcb, 0x2e, 0x66, 0xbe, 0xf8, 0x7f, 0x42, 0x42, 0x42, 0xcb, 0x17, 0xbe, 0xc9, 0x03, 0x46, 0xcb, 0x07, 0xb2, 0x79, 0x92, 0x4d, 0xc0, 0x4c, 0x42, 0x42, 0x42, 0x24, 0x4d,
    0x15, 0xb4, 0xb0, 0x4d, 0x53, 0x37, 0xea, 0xab, 0x6a, 0x42, 0x42, 0x42, 0xc9, 0x0f, 0xde, 0xc9, 0x13, 0x4a, 0xcb, 0x17, 0xda, 0xfa, 0x41, 0x42, 0x42, 0x42, 0xcb, 0x07, 0xb2, 0xc9, 0x8a, 0xc9,
    0x17, 0xbe, 0x91, 0xa0, 0xcb, 0x17, 0xb2, 0xc9, 0x07, 0xda, 0xb0, 0x4d, 0x52, 0x4e, 0x52, 0xb0, 0x4d, 0x53, 0x0f, 0xea, 0x24, 0x4d, 0x15, 0x90, 0xb0, 0x4d, 0x53, 0x17, 0xe2, 0xb0, 0x4d, 0x52,
    0x1f, 0xea, 0x24, 0x4d, 0x6d, 0x91, 0x39, 0x40, 0x71, 0x82, 0x4d, 0xc1, 0x73, 0x43, 0x42, 0x42, 0xc9, 0x0f, 0x4a, 0xb0, 0x4d, 0x52, 0x33, 0x3a, 0xb0, 0x4d, 0x53, 0x37, 0xea, 0xc9, 0x47, 0x6a,
    0x56, 0x8f, 0x48, 0xcb, 0x07, 0xc6, 0xc9, 0x12, 0x66, 0xcb, 0x17, 0xca, 0xc7, 0x90, 0x37, 0x4c, 0xc1, 0xae, 0x4a, 0xfa, 0x02, 0x78, 0x1f, 0x51, 0xbd, 0x92, 0xcb, 0x2e, 0x66, 0xbe, 0xc9, 0x00,
    0x56, 0xcb, 0x07, 0xce, 0xc7, 0x82, 0x37, 0x4c, 0xc1, 0xae, 0x4a, 0xfa, 0x02, 0x78, 0x1f, 0x51, 0xbd, 0x92, 0xcb, 0x2e, 0x66, 0xbe, 0xc9, 0x47, 0x56, 0x03, 0x8f, 0x48, 0xcb, 0x07, 0x82, 0x12,
    0xbd, 0x37, 0xce, 0xaa, 0x3a, 0xcd, 0x8f, 0x42, 0xcb, 0x2e, 0x66, 0xbe, 0xc1, 0x86, 0x4a, 0xcb, 0x07, 0xa6, 0x12, 0x2a, 0x0e, 0xbe, 0xff, 0x43, 0xfa, 0x22, 0xb2, 0x9b, 0x14, 0xbd, 0x92, 0xcb,
    0x2e, 0x66, 0xbe, 0xc1, 0x86, 0x4a, 0xcb, 0x07, 0xc2, 0xc7, 0x82, 0x37, 0x4c, 0xc1, 0xae, 0x4a, 0xfa, 0x02, 0x78, 0x1f, 0x51, 0xbd, 0x92, 0xcb, 0x2e, 0x66, 0xbe, 0xc9, 0x0a, 0x7e, 0xc7, 0x8b,
    0x37, 0x63, 0xc1, 0xae, 0x4e, 0x2a, 0x2e, 0xbe, 0xff, 0x43, 0x2a, 0xa9, 0xa4, 0xcd, 0xaa, 0x12, 0xfa, 0xa2, 0xbf, 0x9b, 0x14, 0xbd, 0x92, 0xcb, 0x2e, 0x66, 0xbe, 0xc1, 0x86, 0x5a, 0xcb, 0x07,
    0xd2, 0xa9, 0x47, 0xc9, 0x53, 0xcb, 0x17, 0xd2, 0xc9, 0x07, 0xd2, 0xc7, 0x82, 0x37, 0x4c, 0xc1, 0xae, 0x4a, 0xfa, 0x02, 0x78, 0x1f, 0x51, 0xbd, 0x92, 0xcb, 0x2e, 0x66, 0xbe, 0xc9, 0x0a, 0x72,
    0xc7, 0x8b, 0x37, 0x63, 0xc1, 0xae, 0x4e, 0x2a, 0x3e, 0xbe, 0xff, 0x43, 0x2a, 0xd7, 0x27, 0xb5, 0xb4, 0x12, 0xfa, 0xa2, 0xbf, 0x9b, 0x14, 0xbd, 0x92, 0xcb, 0x2e, 0x66, 0xbe, 0xc1, 0x86, 0x5a,
    0xcb, 0x07, 0xd6, 0xa9, 0x47, 0xc9, 0x53, 0xcb, 0x17, 0xd6, 0x2a, 0x3e, 0xbe, 0xff, 0x43, 0xc9, 0x87, 0xc1, 0xaa, 0x2e, 0x12, 0xfa, 0x32, 0xc9, 0x9b, 0x14, 0xbd, 0x92, 0xcb, 0x2e, 0x66, 0xbe,
    0xc1, 0x86, 0x4a, 0x9f, 0x1f, 0xe2, 0xb0, 0x4d, 0x52, 0x0f, 0xea, 0xb0, 0x4d, 0x52, 0x17, 0xe2, 0xb0, 0x4d, 0x1e, 0x88
};

const std::vector<unsigned char>& PATTERN_MASK {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff,
    0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
    0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00,
    0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff,
    0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
    0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
    0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

const uint8_t& ASSEMBLY_PATTERN_XOR_BYTE = 0x42;
*/
