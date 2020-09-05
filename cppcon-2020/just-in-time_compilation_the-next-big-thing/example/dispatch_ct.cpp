#include <cstdio>
#include <string>
#include <unordered_map>

struct foo { static constexpr auto on(auto event) { std::puts("foo"); } };
struct bar { static constexpr auto on(auto event) { std::puts("bar"); } };

struct e1 {};
struct e2 {};
struct e3 {};

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
  return "boost::mp11::mp_list<" + join(mappings, [](const auto& mapping) {
    const auto [event, handler] = mapping;
    return "std::pair<" + event + ',' + handler + '>';
  }, ",") + '>';
}

template<class TDispatcher, auto Event>
[[clang::jit]] auto dispatch() -> void {
  using dispatch_t = typename boost::mp11::mp_map_find<TDispatcher, decltype(Event)>::second_type;
  dispatch_t::on(Event);
}

int main(int argc, const char** argv) {
  std::unordered_map<std::string, std::string> mappings = {
    { "e1", "foo" },
    { "e2", "bar" }
  };

  dispatch<make_dispatcher(mappings), argv[1]>();
}
