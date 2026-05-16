#include <gtest/gtest.h>
#include <random>
#include "base85ed.h"

using namespace base85;

static std::vector<uint8_t> cstr2v(const char* s) {
    return std::vector<uint8_t>(s, s + std::string(s).size());
}

TEST(Base85Test, EmptyString) {
    EXPECT_TRUE(encode({}).empty());
    EXPECT_TRUE(decode({}).empty());
    EXPECT_EQ(encodeToString(""), "");
    EXPECT_EQ(decodeToString(""), "");
}

TEST(Base85Test, ShortCases) {
    struct TestCase {
        const char* encoded;
        const char* decoded;
    };
    
    std::vector<TestCase> cases = {
        {"", ""},
        {"5l", "A"},
        {"5l>", "AB"},
        {"5l>h", "ABC"},
        {"5l>h?", "ABCD"},
        {"87cURDZ", "Hello"},
        {"<~OuLrB>~", "Test"},
        {"F)kW", "1234"},
        {"F)}j", "123"},
        {"F){", "12"},
        {"F#", "1"},
    };
    
    for (const auto& tc : cases) {
        EXPECT_EQ(encode(cstr2v(tc.decoded)), cstr2v(tc.encoded));
        EXPECT_EQ(decode(cstr2v(tc.encoded)), cstr2v(tc.decoded));
    }
}

TEST(Base85Test, AllBytes) {
    std::vector<uint8_t> allBytes;
    for (int i = 0; i < 256; ++i) {
        allBytes.push_back(static_cast<uint8_t>(i));
    }
    
    auto encoded = encode(allBytes);
    auto decoded = decode(encoded);
    EXPECT_EQ(allBytes, decoded);
}

TEST(Base85Test, Zeros) {
    std::vector<uint8_t> zeros(4, 0);
    EXPECT_EQ(encode(zeros), cstr2v("00000"));
    EXPECT_EQ(decode(cstr2v("00000")), zeros);
}

TEST(Base85Test, MaxBytes) {
    std::vector<uint8_t> maxBytes = {0xFF, 0xFF, 0xFF, 0xFF};
    EXPECT_EQ(encode(maxBytes), cstr2v("|NsC0"));
    EXPECT_EQ(decode(cstr2v("|NsC0")), maxBytes);
}

TEST(Base85Test, WhitespaceTolerance) {
    const char* clean = "F)kW";
    const char* messy = " \n F \r ) \t k \n W \t ";
    
    EXPECT_EQ(decode(cstr2v(clean)), decode(cstr2v(messy)));
    EXPECT_EQ(decodeToString(messy), "1234");
}

TEST(Base85Test, InvalidCharactersThrow) {
    EXPECT_THROW(decode(cstr2v("F)ыkW")), std::invalid_argument);
    EXPECT_THROW(decode(cstr2v("F),kW")), std::invalid_argument);
    EXPECT_THROW(decode(cstr2v("Hello\xFFWorld")), std::invalid_argument);
}

TEST(Base85Test, InvalidLengthThrow) {
    EXPECT_THROW(decode(cstr2v("F")), std::invalid_argument);
    EXPECT_THROW(decode(cstr2v("FF")), std::invalid_argument);
    EXPECT_THROW(decode(cstr2v("FFF")), std::invalid_argument);
    EXPECT_THROW(decode(cstr2v("FFFF")), std::invalid_argument);
    EXPECT_THROW(decode(cstr2v("FFFFFF")), std::invalid_argument);
}

TEST(Base85Test, OverflowThrow) {
    EXPECT_THROW(decode(cstr2v("~~~~~")), std::invalid_argument);
}

TEST(Base85Test, RandomData) {
    std::mt19937 rng(12345);
    std::uniform_int_distribution<size_t> sizeDist(0, 5000);
    std::uniform_int_distribution<uint8_t> byteDist(0, 255);
    
    for (int test = 0; test < 50; ++test) {
        size_t size = sizeDist(rng);
        std::vector<uint8_t> original(size);
        for (auto& b : original) {
            b = byteDist(rng);
        }
        
        auto encoded = encode(original);
        auto decoded = decode(encoded);
        EXPECT_EQ(original, decoded);
        
        std::string strEncoded(encoded.begin(), encoded.end());
        auto strDecoded = decodeToString(strEncoded);
        EXPECT_EQ(std::string(original.begin(), original.end()), strDecoded);
    }
}

TEST(Base85Test, EdgeLengths) {
    for (int len = 0; len <= 20; ++len) {
        std::vector<uint8_t> data(len, static_cast<uint8_t>(len));
        auto encoded = encode(data);
        auto decoded = decode(encoded);
        EXPECT_EQ(data, decoded);
    }
}

TEST(Base85Test, LargeData) {
    std::vector<uint8_t> large(100000, 0x55);
    auto encoded = encode(large);
    auto decoded = decode(encoded);
    EXPECT_EQ(large, decoded);
    EXPECT_EQ(encoded.size(), (large.size() + 3) / 4 * 5);
}

TEST(Base85Test, RoundtripString) {
    std::vector<std::string> tests = {
        "",
        "A",
        "Hello World!",
        "1234567890",
        "!@#$%^&*()",
        std::string(100, 'X'),
        "The quick brown fox jumps over the lazy dog"
    };
    
    for (const auto& test : tests) {
        std::string encoded = encodeToString(test);
        std::string decoded = decodeToString(encoded);
        EXPECT_EQ(test, decoded);
        EXPECT_TRUE(encoded.length() == 0 || encoded.length() % 5 == 0);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}