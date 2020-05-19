#include "exceptions.h"

#include <functional>

class A {
public:
  explicit A(int a) : a{a} {}
  ~A() {
    std::cout << "Dead A(" << a << ")  ";
  }
private:
  int a;

  friend std::ostream &operator<<(std::ostream &stream, const A &a);
};
std::ostream &operator<<(std::ostream &stream, const A &a) {
  stream << a.a;
  return stream;
}

static void throw_int(int val) {
  throw val;
}
template<typename Exc>
static void throw_exc(const std::string &err) {
  throw Exc(err);
}

static void t() {
  throw std::runtime_error("sfjsdkf");
}

static void check_my_exception() {
  try {
    throw_exc<my_exception_t>("Error");
  } catch (const std::exception &e) {
    std::cout << "Catch my_exception: " << e.what() << std::endl;
  }
  std::cout << "Hello" << std::endl;
}
static void check_int_exception() {
  try {
    throw_int(16);
  } catch (int err) {
    std::cout << "Catch int exception: " << err << std::endl;
  }
}
static void check_caught_any() {
  try {
    throw_exc<std::logic_error>("Logic error");
  } catch (...) {
    std::cout << "I'm caught something: " << std::endl;
  }
}
static void check_exception_inheritance() {
  try {
    throw_exc<std::range_error>("Range error");
  } catch (int a) {
    std::cout << "catch int" << std::endl;
  } catch (const std::runtime_error &e) {
    std::cout << "Caught runtime_error: " << e.what() << std::endl;
  } catch (const std::range_error &e) {
    std::cout << "Caught range_error:   " << e.what() << std::endl;
  }

  std::cout << "Hell" << std::endl;
}
template<typename Exc>
static void rethrow(const std::function<void()> &f) {
  int *a = new int(100);
  try {
    f();
  } catch (const Exc &e) {
    std::cout << "I caught: " << e.what() << ". Rethrow. ";
    delete a;
    throw;
  }
  //
  delete a;
}
static void check_caught_rethrow() {
  try {
    rethrow<std::runtime_error>([]() {
      throw_exc<std::runtime_error>("Wheeeee!!!");
    });
  } catch (const std::runtime_error &e) {
    std::cout << "I finally caught: " << e.what() << std::endl;
  }


}

static void context1() {
  A a(20);
  throw_exc<my_exception_t>("Fly!");
  std::cout << a << std::endl;
}
static void context2() {
  A a(30);
  context1();
  std::cout << a << std::endl;
}
static void context3() {
  A a(40);
  try {
    context2();
  } catch (std::exception e) { // Do NOT do like this!!! catch by reference
    std::cout << "Temp catch: " << e.what() << "  ";
    throw;  // rethrow original exception not 'e'
  }
  std::cout << a << std::endl;
}
static void context4() {
  try {
    context3();
  } catch (const std::exception &e) {
    std::cout << "Finally catch: " << e.what() << std::endl;
  }
}


void check_exceptions() {
  std::cout << "Start check exceptions" << std::endl;
  check_my_exception();
  check_int_exception();
  check_caught_any();
  check_exception_inheritance();
  check_caught_rethrow();
  context4();
  std::cout << std::endl;
}
