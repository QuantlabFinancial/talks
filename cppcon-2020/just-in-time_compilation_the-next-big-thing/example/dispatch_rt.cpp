#include <cstdio>
#include <string>
#include <unordered_map>

struct foo { static constexpr auto on(auto event) { std::puts("foo"); } };
struct bar { static constexpr auto on(auto event) { std::puts("bar"); } };

struct e1 { static constexpr auto id = 1; };
struct e2 { static constexpr auto id = 2; };
struct e3 { static constexpr auto id = 3; };

auto join(const auto& map, auto expr, auto separator) {
  std::string result{};
  auto first = true;
  for (const auto& e : map) {
    result += std::string(first ? "" : separator) + expr(e);
    first = false;
  }
  return result;
}

constexpr auto make_dispatcher(const auto& mappings) {
  return R"([](auto id) {
    switch(id) { default: assert(false); break;)" +
      join(mappings, [](const auto& mapping) {
        const auto [ event, handler ] = mapping;
        return "case " + event + "::id:" + handler + "::on(" + event + "{}); break;";
      }, "") +
    "}};";
}

template<auto Dispatch>
[[clang::jit]] auto dispatch(auto id) -> void {
  Dispatch(id);
}

int main(int argc, const char** argv) {
  std::unordered_map<std::string, std::string> mappings = {
    { "e1", "foo" },
    { "e2", "bar" }
  };

  dispatch<make_dispatcher(mappings)>(std::stoi(argv[1]));
}
