// В задаче необходимо вычислить среднее геометрическое на отрезке по нескольким
// запросам

#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

int main() {
  const int kPrecision = 10;
  size_t count_mandrake;
  std::cin >> count_mandrake;

  std::vector<double> volume(count_mandrake);
  for (size_t mandrake_i = 0; mandrake_i < count_mandrake; ++mandrake_i) {
    std::cin >> volume[mandrake_i];
  }
  std::vector<double> prefix_sum_logs(count_mandrake + 1);
  double prefix_sum_logs_i = 0;
  prefix_sum_logs[0] = 0;
  for (size_t mandrake_i = 1; mandrake_i < count_mandrake + 1; ++mandrake_i) {
    prefix_sum_logs_i += log(volume[mandrake_i - 1]);
    prefix_sum_logs[mandrake_i] = prefix_sum_logs_i;
  }
  size_t count_request;
  std::cin >> count_request;
  for (size_t request_i = 0; request_i < count_request; ++request_i) {
    size_t left;
    size_t right;
    double geometric_mean;
    std::cin >> left >> right;
    geometric_mean =
        std::exp((prefix_sum_logs[right + 1] - prefix_sum_logs[left]) *
                 (1. / (static_cast<double>(right - left) + 1)));
    std::cout << std::setprecision(kPrecision) << geometric_mean << "\n";
  }
  return 0;
}
