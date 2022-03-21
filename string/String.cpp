#include "String.hpp"

String::String() {
  data_ = (char*)calloc(1, sizeof(char));
  size_ = 0;
  capacity_ = 1;
}

String::String(size_t size, char character) {
  data_ = (char*)calloc(size + 1, sizeof(char));
  size_ = size;
  capacity_ = size + 1;
  memset(data_, character, size);
}

String::String(const char* new_data) {
  size_ = strlen(new_data);
  data_ = (char*)calloc(size_ + 1, sizeof(char));
  data_[size_] = '\0';
  capacity_ = size_ + 1;
  memcpy(data_, new_data, size_);
}

String::String(const String& other) {
  size_ = other.size_;
  capacity_ = other.capacity_;
  data_ = (char*)calloc(capacity_, sizeof(char));
  memcpy(data_, other.data_, capacity_);
}

String& String::operator=(const String& other) {
  if (this != &other) {
    free(data_);
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = (char*)calloc(capacity_, sizeof(char));
    memcpy(data_, other.data_, capacity_);
  }
  return *this;
}

String::~String() { free(data_); }

void String::Clear() {
  memset(data_, 0, size_);
  size_ = 0;
}

void String::PushBack(char character) {
  if (size_ == capacity_ - 1) {
    if (capacity_ != 1) {
      Reserve((capacity_ - 1) * 2);
    } else {
      Reserve(1);
    }
  }
  data_[size_++] = character;
}

void String::PopBack() {
  if (!Empty()) {
    data_[--size_] = '\0';
  }
}

void String::Resize(size_t new_size) {
  Reserve(new_size);
  if (size_ > new_size) {
    memset(data_ + new_size, '\0', size_ - new_size);
  }
  size_ = new_size;
}

void String::Resize(size_t new_size, char character) {
  Reserve(new_size);
  if (size_ > new_size) {
    memset(data_ + new_size, '\0', size_ - new_size);
  } else {
    memset(data_ + size_, character, new_size - size_);
  }
  size_ = new_size;
}

void String::Reserve(size_t new_cap) {
  if (new_cap > capacity_ - 1) {
    data_ = (char*)realloc(data_, new_cap + 1);
    memset(data_ + capacity_, '\0', new_cap - capacity_ + 1);
    capacity_ = new_cap + 1;
  }
}

void String::ShrinkToFit() {
  data_ = (char*)realloc(data_, size_ + 1);
  capacity_ = size_ + 1;
}

void String::Swap(String& other) {
  char* other_data = other.data_;
  size_t other_size = other.size_;
  size_t other_capacity = other.capacity_;
  other.data_ = data_;
  other.size_ = size_;
  other.capacity_ = capacity_;
  data_ = other_data;
  size_ = other_size;
  capacity_ = other_capacity;
}

char String::operator[](size_t index) const {
  if (index > size_) {
    index = size_;
  }
  return data_[index];
}

char& String::operator[](size_t index) { return data_[index]; }

const char& String::Front() const { return data_[0]; }

char& String::Front() { return data_[0]; }

const char& String::Back() const { return data_[size_ - 1]; }

char& String::Back() { return data_[size_ - 1]; }

bool String::Empty() const { return (size_ == 0); }

size_t String::Size() const { return size_; }

size_t String::Capacity() const { return capacity_ - 1; }

const char* String::Data() const { return data_; }

String& String::operator+=(const String& other) {
  size_t size = other.Size();
  for (size_t i = 0; i < size; i++) {
    PushBack(other[i]);
  }
  return *this;
}

String& String::operator*=(int n) {
  size_t size = size_;
  if (n == 0) {
    Clear();
  } else {
    while (--n != 0) {
      for (size_t i = 0; i < size; i++) {
        PushBack(data_[i]);
      }
    }
  }
  return *this;
}

String operator+(const String& first, const String& second) {
  String res(first);
  res += second;
  return res;
}

String operator*(const String& str, int n) {
  String res(str);
  res *= n;
  return res;
}

std::vector<String> String::Split(const String& delim) const {
  std::vector<String> strings;
  String str;
  for (size_t i = 0; i <= size_; i++) {
    bool split = true;
    if (i + delim.Size() - 1 < size_) {
      for (size_t j = 0; j < delim.Size(); j++) {
        if (delim[j] != data_[i + j]) {
          split = false;
        }
      }
    } else {
      split = false;
    }
    if (split) {
      strings.push_back(str);
      str.Clear();
      i += delim.Size() - 1;
    } else if (i != size_) {
      str.PushBack(data_[i]);
    } else {
      strings.push_back(str);
    }
  }
  return strings;
}

String String::Join(const std::vector<String>& strings) const {
  String res;
  if (!strings.empty()) {
    res += strings[0];
  }
  for (size_t i = 1; i < strings.size(); i++) {
    res += *this + strings[i];
  }
  return res;
}

std::ostream& operator<<(std::ostream& out, const String& str) {
  for (int i = 0; i < str.Size(); i++) {
    out << str[i];
  }
  return out;
}

std::istream& operator>>(std::istream& in, String& str) {
  char input;
  while (in.get(input) && input != '\n') {
    str.PushBack(input);
  }
  return in;
}

bool operator<(const String& first, const String& second) {
  return strcmp(first.Data(), second.Data()) < 0;
}

bool operator>(const String& first, const String& second) {
  return strcmp(first.Data(), second.Data()) > 0;
}

bool operator<=(const String& first, const String& second) {
  return strcmp(first.Data(), second.Data()) <= 0;
}

bool operator>=(const String& first, const String& second) {
  return strcmp(first.Data(), second.Data()) >= 0;
}

bool operator==(const String& first, const String& second) {
  return strcmp(first.Data(), second.Data()) == 0;
}

bool operator!=(const String& first, const String& second) {
  return strcmp(first.Data(), second.Data()) != 0;
}
