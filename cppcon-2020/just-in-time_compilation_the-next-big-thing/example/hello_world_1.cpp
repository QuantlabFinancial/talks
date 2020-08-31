#include <iostream>
#include <typeinfo>

template<class T>
[[clang::jit]] auto jit() -> void {
  std::cout << typeid(T).name() << '\n';
}

int main(int argc, const char** argv) {
  jit<argv[1]>();
}
