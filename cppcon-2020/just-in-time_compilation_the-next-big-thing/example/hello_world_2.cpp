#include <iostream>

template<class TExpr>
[[clang::jit]] auto jit() -> void {
  TExpr{}();
}

int main(int argc, const char** argv) {
  jit<argv[1]>();
}
