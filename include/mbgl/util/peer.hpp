#pragma once

#include <memory>
#include <type_traits>
#include <utility>

namespace mbgl {
namespace util {

class peer {
public:
    peer() noexcept = default;

    template <class T>
    peer(T&& value) noexcept : ptr(new DataHolder<T>(std::forward<T>(value))) {}

    bool has_value() const noexcept { return static_cast<bool>(ptr); }

    void reset() noexcept { ptr = nullptr; }

    template <class T>
    T& get() noexcept {
        return static_cast<DataHolder<T>*>(ptr.get())->data;
    }
private:
    struct DataHolderBase {
        virtual ~DataHolderBase() noexcept = default;
    };

    template <typename T>
    struct DataHolder final : public DataHolderBase {
        DataHolder(T&& data_) noexcept : data(std::forward<T>(data_)) {}
        typename std::decay<T>::type data;
    };
    std::unique_ptr<DataHolderBase> ptr;
};

} // namespace util
} // namespace mbgl
