// В задаче необходимо вычислить среднее геометрическое на отрезке по нескольким запросам

#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>


int main() {
  const int kPrecision = 10;
  size_t cnt_mandrake;
  std::cin >> cnt_mandrake;

  std::vector<double> volume(cnt_mandrake);
  for (size_t mandrake_i = 0; mandrake_i < cnt_mandrake; ++mandrake_i) {
    std::cin >> volume[mandrake_i];
  }
  std::vector<double> pref_sum_logs(cnt_mandrake + 1);
  double pref_sum_logs_i = 0;
  pref_sum_logs[0] = 0;
  for (size_t mandrake_i = 1; mandrake_i < cnt_mandrake + 1; ++mandrake_i) {
    pref_sum_logs_i += log(volume[mandrake_i - 1]);
    pref_sum_logs[mandrake_i] = pref_sum_logs_i;
  }
  size_t cnt_request;
  std::cin >> cnt_request;
  int left_i;
  int right_i;
  double ans_i;
  for (size_t request_i = 0; request_i < cnt_request; ++request_i) {
    std::cin >> left_i >> right_i;
    ans_i = std::exp((pref_sum_logs[right_i + 1] - pref_sum_logs[left_i]) *
                     (1. / (static_cast<double>(right_i - left_i) + 1)));
    std::cout << std::setprecision(kPrecision) << ans_i << "\n";
  }
  return 0;
}
