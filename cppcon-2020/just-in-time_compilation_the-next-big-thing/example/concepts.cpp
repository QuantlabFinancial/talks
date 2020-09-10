#include <utility>
#include <concepts>
#include <cstddef>

template <class TIO>
concept readable_io =
  requires(TIO& io, std::byte* buffer, std::size_t size) {
    { io.read(buffer, size) } -> std::same_as<std::size_t>;
  };

struct my_readable_io {
  auto read(std::byte* buffer, std::size_t size) -> std::size_t;
};

auto not_readable_io = []{ struct not_readable_io{}; return not_readable_io{};};

static_assert(readable_io<my_readable_io>);
static_assert(not readable_io<decltype(not_readable_io)>);
