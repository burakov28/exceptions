#pragma once

#include <exception>
#include <iostream>
#include <string>

// THROW BY VALUE, CAUGHT BY REFERENCE!!!

class my_exception_t : public std::exception {
public:
  explicit my_exception_t(const std::string &text) :
    init_text{text},
    text{"My exception: '" + text + "'"} {}

  const char *what() const noexcept override {
    return text.c_str();
  }

private:
  std::string init_text;
  std::string text;
};

void check_exceptions();
