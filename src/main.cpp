#include <algorithm>
#include <array>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
#include <tuple>
#include <vector>

template <typename InputIt1, typename InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                             InputIt2 last2) {
  for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2) {
    if (*first1 < *first2)
      return true;
    if (*first2 < *first1)
      return false;
  }
  return (first1 == last1) && (first2 != last2);
}

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d) {
  std::vector<std::string> r;

  std::string::size_type start = 0;
  std::string::size_type stop = str.find_first_of(d);
  while (stop != std::string::npos) {
    r.push_back(str.substr(start, stop - start));

    start = stop + 1;
    stop = str.find_first_of(d, start);
  }

  r.push_back(str.substr(start));

  return r;
}

class Address {
  std::array<int, 4> internal;

public:
  Address(const std::string &str) {
    auto parts = split(str, '.');
    std::transform(parts.begin(), parts.end(), internal.begin(),
                   [](const auto &value) { return stoi(value); });
  }

  bool hasByte(int byte) const {
    return std::find(internal.begin(), internal.end(), byte) != internal.end();
  }

  bool hasBytes(const std::vector<int> &bytes) const {
    std::vector<int> cutted(internal.begin(), internal.begin() + bytes.size());
    return cutted == bytes;
  }

  friend std::ostream &operator<<(std::ostream &out, const Address &address) {
    out << address.internal[0] << "." << address.internal[1] << "."
        << address.internal[2] << "." << address.internal[3];
    return out;
  }

  friend bool operator>(const Address &lhs, const Address &rhs) {
    return lexicographical_compare(rhs.internal.begin(), rhs.internal.end(),
                                   lhs.internal.begin(), lhs.internal.end());
  }
};

void filterAny(const std::vector<Address> &input, int byte) {
  for (const auto &address : input)
    if (address.hasByte(byte))
      std::cout << address << std::endl;
}

template <typename... Args>
void filter(const std::vector<Address> &input, Args... args) {
  std::vector<int> bytes = {args...};
  for (const auto &address : input)
    if (address.hasBytes(bytes))
      std::cout << address << std::endl;
}

auto main(int argc, char const *argv[]) -> int {
  try {
    std::vector<Address> ip_pool;

    for (std::string line; std::getline(std::cin, line);) {
      auto v = split(line, '\t');
      ip_pool.push_back(Address(v.at(0)));
    }

    // TODO reverse lexicographically sort
    std::sort(ip_pool.begin(), ip_pool.end(), std::greater<Address>());

    for (const auto &address : ip_pool) {
      std::cout << address << std::endl;
    }

    // 222.173.235.246
    // 222.130.177.64
    // 222.82.198.61
    // ...
    // 1.70.44.170
    // 1.29.168.152
    // 1.1.234.8

    // TODO filter by first byte and output
    // ip = filter(1)
    filter(ip_pool, 1);

    // 1.231.69.33
    // 1.87.203.225
    // 1.70.44.170
    // 1.29.168.152
    // 1.1.234.8

    // TODO filter by first and second bytes and output
    // ip = filter(46, 70)
    filter(ip_pool, 46, 70);

    // 46.70.225.39
    // 46.70.147.26
    // 46.70.113.73
    // 46.70.29.76

    // TODO filter by any byte and output
    // ip = filter_any(46)
    filterAny(ip_pool, 46);

    // 186.204.34.46
    // 186.46.222.194
    // 185.46.87.231
    // 185.46.86.132
    // 185.46.86.131
    // 185.46.86.131
    // 185.46.86.22
    // 185.46.85.204
    // 185.46.85.78
    // 68.46.218.208
    // 46.251.197.23
    // 46.223.254.56
    // 46.223.254.56
    // 46.182.19.219
    // 46.161.63.66
    // 46.161.61.51
    // 46.161.60.92
    // 46.161.60.35
    // 46.161.58.202
    // 46.161.56.241
    // 46.161.56.203
    // 46.161.56.174
    // 46.161.56.106
    // 46.161.56.106
    // 46.101.163.119
    // 46.101.127.145
    // 46.70.225.39
    // 46.70.147.26
    // 46.70.113.73
    // 46.70.29.76
    // 46.55.46.98
    // 46.49.43.85
    // 39.46.86.85
    // 5.189.203.46
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
