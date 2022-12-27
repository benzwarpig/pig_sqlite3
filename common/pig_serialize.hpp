#pragma once

#include <cstring>  // std::memcpy
#include <iostream>
#include <type_traits>
#include <vector>

namespace pig_util {
namespace pig_serialize {

/**********************************************************
 * 该序列化库用于打通vector<char>和vector<T>之间的转换
 * 由于sqlite只支持存储 vector<char> ,所以只考虑该类型
 **********************************************************/
template <class DataType>
class PigSerialize {
public:
    PigSerialize() {
        static_assert(k_copyable, "DataType must be copyable !!!");
    }
    ~PigSerialize() = default;

    std::vector<char> serializeToVector(
        const std::vector<DataType>& source) noexcept {
        std::vector<char> ret;
        for (const auto& data : source) {
            for (int i = 0; i < k_size; i++) {
                ret.emplace_back(getByte(data, i));
            }
        }
        return ret;
    }

    std::vector<DataType> unserializeToVector(
        const std::vector<char>& source) noexcept {
        std::vector<DataType> ret;
        for (int i = 0; i < source.size() / k_size; i++) {
            const char* p = &source.at(0) + i * k_size;
            ret.emplace_back(getData(p));
        }
        return ret;
    }

private:
    char getByte(DataType data, int index) noexcept {
        char ret = *(reinterpret_cast<char*>(&data) + index);
        return ret;
    }

    DataType getData(const char* p) {
        DataType ret;
        std::memcpy((char*)&ret, p, k_size);
        return ret;
    }

private:
    static const constexpr int k_size = sizeof(DataType);

    static const constexpr bool k_copyable =
        std::is_trivially_copyable<DataType>::value;
};

};  // namespace pig_serialize
};  // namespace pig_util
