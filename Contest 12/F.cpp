#include <complex.h>

#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <queue>
#include <valarray>
#include <vector>

using Complex = std::complex<long double>;

void PrepareIO() {
  std::ios::sync_with_stdio(false);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

void FFT(std::vector<Complex>& polynom,
         std::pair<long long, long long> start_finish, long long count,
         Complex omega) {
  if (count == 1) {
    return;
  }
  long long centre = (start_finish.first + start_finish.second) / 2;
  FFT(polynom, {start_finish.first, centre}, count / 2, omega * omega);
  FFT(polynom, {centre + 1, start_finish.second}, count / 2, omega * omega);
  Complex omega_degree = {1, 0};
  for (long long i = start_finish.first; i <= centre; ++i) {
    Complex first = polynom[i] + polynom[count / 2 + i] * omega_degree;
    Complex second = polynom[i] - polynom[count / 2 + i] * omega_degree;
    polynom[i] = first;
    polynom[i + count / 2] = second;
    omega_degree *= omega;
  }
}

size_t Rev(size_t number, size_t size) {
  size_t rev = 0;
  for (size_t i = 0; i < size; ++i) {
    if ((number & (1LL << i)) != 0) {
      rev |= (1LL << (size - 1 - i));
    }
  }
  return rev;
}

void FillPoly(std::vector<long double>& polynom1,
              std::vector<long double>& polynom2, std::vector<Complex>& poly1,
              std::vector<Complex>& poly2, long long count2) {
  for (long long i = 0; i < (1LL << count2); ++i) {
    if (Rev(i, count2) >= polynom1.size()) {
      poly1.push_back(0);
    } else {
      poly1.push_back({polynom1[Rev(i, count2)], 0});
    }
    if (Rev(i, count2) >= polynom2.size()) {
      poly2.push_back(0);
    } else {
      poly2.push_back({polynom2[Rev(i, count2)], 0});
    }
  }
}

void FindComposition(std::vector<long double>& polynom1,
                     std::vector<long double>& polynom2,
                     std::vector<long long>& composition) {
  long long count = 1;
  long long count2 = 0;
  while (count < static_cast<long long>(composition.size())) {
    count *= 2;
    count2 += 1;
  }
  Complex omega(cos(2 * M_PI / count), sin(2 * M_PI / count));
  
  std::vector<Complex> poly1;
  std::vector<Complex> poly2;
  FillPoly(polynom1, polynom2, poly1, poly2, count2);
  
  FFT(poly1, {0, count - 1}, count, omega);
  FFT(poly2, {0, count - 1}, count, omega);
  std::vector<Complex> poly;
  for (long long i = 0; i < count; ++i) {
    poly.push_back(poly1[Rev(i, count2)] * poly2[Rev(i, count2)]);
  }
  FFT(poly, {0, count - 1}, count,
      {cos(2 * M_PI / count), -sin(2 * M_PI / count)});
  for (size_t i = 0; i < composition.size(); ++i) {
    composition[i] = std::round(poly[i].real() / count);
  }
}

int main() {
  PrepareIO();
  long long count1;
  std::cin >> count1;
  std::vector<long double> polynom1(count1 + 1);
  for (long long i = count1; i >= 0; --i) {
    std::cin >> polynom1[i];
  }
  long long count2;
  std::cin >> count2;
  std::vector<long double> polynom2(count2 + 1);
  for (long long i = count2; i >= 0; --i) {
    std::cin >> polynom2[i];
  }
  std::vector<long long> composition(count1 + count2 + 1);
  FindComposition(polynom1, polynom2, composition);
  std::cout << composition.size() - 1 << " ";
  for (long long i = count1 + count2; i >= 0; --i) {
    std::cout << composition[i] << " ";
  }
}
