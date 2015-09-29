#include <iostream>

#include "Foo.hpp"

#include <vector>
#include <chrono>
#include <thread>
#include <algorithm>
#include <future>
#include <cstring>
#include <type_traits>

class Buffer
{
public:
  Buffer(size_t len)
    : m_size(len)
  {
    std::cout << "regular ctor" << std::endl;
    m_buffer = new char[m_size];
  }

  Buffer(const Buffer &other)
  {
    m_buffer = new char[other.m_size];
    std::memcpy(m_buffer, other.m_buffer, other.m_size);
    std::cout << "copy ctor" << std::endl;
  }

  Buffer(Buffer &&other)
    : m_size(other.m_size)
    , m_buffer(other.m_buffer)
  {
    std::cout << "move ctor" << std::endl;
    other.m_buffer = nullptr;
    other.m_size = 0;
  }

  ~Buffer()
  {
    std::cout << "destructor called" << std::endl;
    delete[] m_buffer;
  }

private:
  char *m_buffer;
  size_t m_size;
};

template <typename T>
std::vector<T> operator +(const std::vector<T> &rhs, const std::vector<T> &lhs)
{
    std::vector<T> result;
    result.reserve(lhs.size() + rhs.size());
    result.insert(result.end(), lhs.begin(), lhs.end());
    result.insert(result.end(), rhs.begin(), rhs.end());
    return result;
}

std::vector<double> fib(size_t num)
{
  std::vector<double> ret{1.0,1.0};
  for (size_t i(2); i < num; ++i)
  {
    ret.push_back(ret[i-2] + ret[i-1]);
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  }
  return ret;
}


void print_fib(const std::vector<double> &vec)
{
  for (auto i : vec)
    std::cout << i << ' ';
  std::cout << std::endl;
}

void test_threads()
{
  {
    std::cout << "non-async" << std::endl;
    std::vector<double> f1(fib(50));
    std::vector<double> f2(fib(50));
    std::vector<double> f3(fib(50));
    std::vector<double> f4(fib(50));

    std::vector<double> f_sum(f1 + f2 + f3 + f4);
    std::sort(f_sum.begin(), f_sum.end());
    print_fib(f_sum);
  }

  {
    std::cout << "async" << std::endl;
    std::future<std::vector<double> > f1(std::async(std::launch::async, [](){ return fib(50); }));
    std::future<std::vector<double> > f2(std::async(std::launch::async, [](){ return fib(50); }));
    std::future<std::vector<double> > f3(std::async(std::launch::async, [](){ return fib(50); }));
    std::future<std::vector<double> > f4(std::async(std::launch::async, [](){ return fib(50); }));

    std::vector<double> f_sum(f1.get() + f2.get() + f3.get() + f4.get());
    std::sort(f_sum.begin(), f_sum.end());
    print_fib(f_sum);
  }
}

Buffer create_buffer()
{
  Buffer b(100);
  return b;
}

void test_rvalues()
{
  Buffer b1(50);
  Buffer b2(create_buffer());
  Buffer b3(std::move(b1));
}

template<typename T>
T fun_template(const std::vector<T> &foo)
{
  static_assert(std::is_integral<T>() || std::is_floating_point<T>(), "T has to be a numeric type");
  T sum(0);
  for (T i : foo)
    sum += i;
  return sum;
}

int main(int, char**)
{
  //std::shared_ptr<Foo> f_ptr(std::make_shared<Foo>());


  test_rvalues();
  std::vector<float> fs;
  std::vector<int> is;
  fun_template(fs);

  std::cout << "Hello World!" << std::endl;
  return 0;
}
