#include <iostream>
#include <string>

struct foo { static constexpr auto on(auto event) { std::cout << "foo"; } };
struct bar { static constexpr auto on(auto event) { std::cout << "bar"; } };

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

constexpr auto make_dispatcher(const auto& dispatcher) {
  return "boost::mp11::mp_list<" + join(dispatcher, [](const auto& e) { return "std::pair<" + e.first + ',' + e.second + '>'; }, ",") + '>';
}

template<class TDispatcher, class TEvent>
[[clang::jit]] auto dispatch() -> void {
  using dispatch_t = typename boost::mp11::mp_map_find<TDispatcher, decltype(TEvent{}())>::second_type;
  dispatch_t::on(TEvent{}());
}

int main(int argc, const char** argv) {
  std::unordered_map<std::string, std::string> dispatcher = {
    { "e1", "foo" },
    { "e2", "bar" }
  };

  dispatch<make_dispatcher(dispatcher), argv[1]>();
}
