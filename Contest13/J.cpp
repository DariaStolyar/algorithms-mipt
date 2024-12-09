#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

const long long cThree = 3;

void PrepareIO() {
  std::ios::sync_with_stdio(false);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

struct Vector {
  long long x;
  long long y;

  Vector() : x(0.0), y(0.0){};
  Vector(long long x, long long y) : x(x), y(y){};

  void operator-=(Vector vector) {
    x -= vector.x;
    y -= vector.y;
  }

  Vector operator-(Vector vector) {
    Vector new_vector = *this;
    new_vector -= vector;
    return new_vector;
  }

  void operator+=(Vector vector) {
    x += vector.x;
    y += vector.y;
  }

  Vector operator+(Vector vector) {
    Vector new_vector = *this;
    new_vector += vector;
    return new_vector;
  }

  bool operator==(Vector vector) const {
    return (x == vector.x) and (y == vector.y);
  }

  long long VectorProduct(Vector vector) const {
    return x * vector.y - y * vector.x;
  }
};

size_t FindMinIndex(std::vector<Vector>& vector) {
  size_t index_min = 0;
  for (size_t i = 1; i < vector.size(); ++i) {
    if (vector[i].x < vector[index_min].x or
        (vector[i].x == vector[index_min].x and
         vector[i].y < vector[index_min].y)) {
      index_min = i;
    }
  }
  return index_min;
}

std::vector<Vector> MinkowskiSum(std::vector<Vector>& first,
                                 std::vector<Vector>& second) {
  size_t index_min1 = FindMinIndex(first);
  size_t index_min2 = FindMinIndex(second);
  std::vector<Vector> sum;
  sum.push_back(first[index_min1] + second[index_min2]);
  while (true) {
    Vector first_side =
        first[(index_min1 + 1) % first.size()] - first[index_min1];
    Vector second_side =
        second[(index_min2 + 1) % second.size()] - second[index_min2];
    if (first_side.VectorProduct(second_side) > 0) {
      sum.push_back(sum[sum.size() - 1] + first_side);
      index_min1 = (index_min1 + 1) % first.size();
    } else if (first_side.VectorProduct(second_side) < 0) {
      sum.push_back(sum[sum.size() - 1] + second_side);
      index_min2 = (index_min2 + 1) % second.size();
    } else {
      sum.push_back(sum[sum.size() - 1] + second_side + first_side);
      index_min1 = (index_min1 + 1) % first.size();
      index_min2 = (index_min2 + 1) % second.size();
    }
    if (sum[sum.size() - 1] == sum[0]) {
      sum.pop_back();
      break;
    }
  }
  return sum;
}

std::vector<Vector> SumOfThree(std::vector<Vector>& points1,
                               std::vector<Vector>& points2,
                               std::vector<Vector>& points3) {
  std::vector<Vector> sum = MinkowskiSum(points1, points2);
  return MinkowskiSum(sum, points3);
}

bool IsInAngle(Vector first, Vector second, Vector point) {
  long long angle1 = first.VectorProduct(point);
  long long angle2 = first.VectorProduct(second);
  long long angle3 = point.VectorProduct(second);
  return ((angle1 >= 0 and angle2 >= 0) or (angle1 <= 0 and angle2 <= 0)) and
         ((angle3 >= 0 and angle2 >= 0) or (angle3 <= 0 and angle2 <= 0));
}

bool IsInSum(Vector query, std::vector<Vector>& points, long long index) {
  query.x *= cThree;
  query.y *= cThree;
  if (!IsInAngle(
          points[(index + 1) % points.size()] - points[index],
          points[(index - 1 + points.size()) % points.size()] - points[index],
          query - points[index])) {
    return false;
  }
  size_t right = points.size() - 1;
  size_t left = 1;
  while (left + 1 < right) {
    size_t middle = (right + left) / 2;
    if (!IsInAngle(points[(index + 1) % points.size()] - points[index],
                   points[(middle + index) % points.size()] - points[index],
                   query - points[index])) {
      left = middle;
    } else {
      right = middle;
    }
  }
  return IsInAngle(points[index] - points[(left + index) % points.size()],
                   points[(right + index) % points.size()] -
                       points[(left + index) % points.size()],
                   query - points[(left + index) % points.size()]) and
         IsInAngle(points[index] - points[(right + index) % points.size()],
                   points[(left + index) % points.size()] -
                       points[(right + index) % points.size()],
                   query - points[(right + index) % points.size()]);
}

int main() {
  PrepareIO();
  size_t count_points;
  std::cin >> count_points;
  std::vector<Vector> points1(count_points);
  for (size_t i = 0; i < count_points; ++i) {
    std::cin >> points1[i].x >> points1[i].y;
  }
  std::cin >> count_points;
  std::vector<Vector> points2(count_points);
  for (size_t i = 0; i < count_points; ++i) {
    std::cin >> points2[i].x >> points2[i].y;
  }
  std::cin >> count_points;
  std::vector<Vector> points3(count_points);
  for (size_t i = 0; i < count_points; ++i) {
    std::cin >> points3[i].x >> points3[i].y;
  }
  std::vector<Vector> sum = SumOfThree(points1, points2, points3);
  long long index = FindMinIndex(sum);
  size_t count_queries;
  std::cin >> count_queries;
  for (size_t i = 0; i < count_queries; ++i) {
    Vector query;
    std::cin >> query.x >> query.y;
    bool in_sum = IsInSum(query, sum, index);
    if (in_sum) {
      std::cout << "YES"
                << "\n";
    } else {
      std::cout << "NO"
                << "\n";
    }
  }
}
