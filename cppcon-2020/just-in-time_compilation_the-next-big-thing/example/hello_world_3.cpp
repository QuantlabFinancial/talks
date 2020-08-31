#include <iostream>

template<auto Expr>
[[clang::jit]] auto jit() -> void {
  Expr();
}

int main(int argc, const char** argv) {
  jit<argv[1]>();
}
