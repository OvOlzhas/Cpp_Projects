#pragma once

#include <string.h>

#include <iostream>
#include <vector>

class String {
 public:
  String();

  String(size_t size, char character);

  String(const char* new_data);

  String(const String& other);
  String& operator=(const String& other);

  ~String();

  void Clear();

  void PushBack(char character);

  void PopBack();

  void Resize(size_t new_size);

  void Resize(size_t new_size, char character);

  void Reserve(size_t new_cap);

  void ShrinkToFit();

  void Swap(String& other);

  char operator[](size_t index) const;

  char& operator[](size_t index);

  [[nodiscard]] const char& Front() const;

  [[nodiscard]] char& Front();

  [[nodiscard]] const char& Back() const;

  [[nodiscard]] char& Back();

  [[nodiscard]] bool Empty() const;

  [[nodiscard]] size_t Size() const;

  [[nodiscard]] size_t Capacity() const;

  [[nodiscard]] const char* Data() const;

  String& operator+=(const String& other);

  String& operator*=(int n);

  [[nodiscard]] std::vector<String> Split(const String& delim = " ") const;

  [[nodiscard]] String Join(const std::vector<String>& strings) const;

 private:
  size_t size_;
  size_t capacity_;
  char* data_;
};

std::ostream& operator<<(std::ostream& out, const String& str);

std::istream& operator>>(std::istream& in, String& str);

String operator+(const String& first, const String& second);

String operator*(const String& str, int n);

bool operator<(const String& first, const String& second);

bool operator>(const String& first, const String& second);

bool operator<=(const String& first, const String& second);

bool operator>=(const String& first, const String& second);

bool operator==(const String& first, const String& second);

bool operator!=(const String& first, const String& second);
