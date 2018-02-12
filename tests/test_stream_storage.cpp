#include <gtest/gtest.h>

#include <algorithm>
#include <sstream>
#include <vector>

#include <pods/stream_storage.h>

TEST(streamStorage, common)
{
    std::stringstream buffer;

    pods::WriteOnlyStreamStorage out(buffer);

    const bool e1 = false;
    const uint64_t e2 = 100;

    const size_t n = 1000;

    std::vector<uint64_t> e3;
    e3.reserve(n);

    uint64_t i = 0;
    std::generate_n(std::back_inserter(e3), n, [&i]() { return i++; });

    for (size_t j = 0; j < n; ++j)
    {
        EXPECT_EQ(out.put(e1), pods::Error::NoError);
        EXPECT_EQ(out.put(e2), pods::Error::NoError);
    }

    EXPECT_EQ(out.put(e3.data(), e3.size()), pods::Error::NoError);

    pods::ReadOnlyStreamStorage in(buffer);

    for (size_t j = 0; j < n; ++j)
    {
        bool a1 = true;
        EXPECT_EQ(in.get(a1), pods::Error::NoError);
        EXPECT_EQ(e1, a1);

        uint64_t a2 = 0;
        EXPECT_EQ(in.get(a2), pods::Error::NoError);
        EXPECT_EQ(e2, a2);
    }

    std::vector<uint64_t> a3;
    a3.resize(n);
    EXPECT_EQ(in.get(a3.data(), a3.size()), pods::Error::NoError);
    EXPECT_EQ(e3, a3);
}

TEST(streamStorage, flush)
{
    std::stringstream buffer;

    const uint16_t expected = 1;

    {
        pods::WriteOnlyStreamStorage out(buffer);
        EXPECT_EQ(out.put(expected), pods::Error::NoError);
    }

    uint16_t actual = 0;

    pods::ReadOnlyStreamStorage out(buffer);
    EXPECT_EQ(out.get(actual), pods::Error::NoError);
    EXPECT_EQ(expected, actual);
}
