#include <iostream>

template<class TExpr>
[[clang::jit]] auto jit() -> void {
  TExpr{}();
}

int main(int argc, const char** argv) {
  jit<R"(decltype([] { std::cout << std::getenv("USER");}))">();
}
