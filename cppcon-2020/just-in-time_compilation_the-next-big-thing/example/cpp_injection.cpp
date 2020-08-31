#include <iostream>
#include <string>

template<class TExpr>
[[clang::jit]] auto jit() -> void {
  TExpr{}();
}

int main(int argc, const char** argv) {
  using std::literals::string_literals::operator""s;
  jit<"decltype([] { std::cout << \""s + std::getenv("USER") + "\"; })"s>();
}
