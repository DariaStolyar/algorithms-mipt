#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

const long double cHalf = 0.5;

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

  long double Length() const { return std::pow(x * x + y * y, cHalf); }

  void operator-=(Vector vector) {
    x -= vector.x;
    y -= vector.y;
  }

  void operator+=(Vector vector) {
    x += vector.x;
    y += vector.y;
  }

  long long VectorProduct(Vector vector) const {
    return x * vector.y - y * vector.x;
  }
};

bool Cmp(Vector first, Vector second) {
  if (first.VectorProduct(second) > 0) {
    return true;
  }
  return first.VectorProduct(second) == 0 and first.Length() < second.Length();
}

long double FindArea(std::vector<Vector>& convex_hull) {
  long long area = 0;
  for (size_t i = 1; i < convex_hull.size() - 1; ++i) {
    Vector first(convex_hull[i]);
    first -= convex_hull[0];
    Vector second(convex_hull[i + 1]);
    second -= convex_hull[0];
    area += first.VectorProduct(second);
  }
  return cHalf * std::fabs(area);
}

double FindConvexHull(std::vector<Vector>& points, size_t min_point,
                      std::vector<Vector>& convex_hull) {
  std::vector<Vector> sorted_points;
  for (size_t i = 0; i < points.size(); ++i) {
    if (i != min_point) {
      Vector min_to_i(points[i]);
      min_to_i -= points[min_point];
      sorted_points.push_back(min_to_i);
    }
  }
  std::sort(sorted_points.begin(), sorted_points.end(), Cmp);
  convex_hull.push_back({0, 0});
  for (size_t i = 0; i < sorted_points.size(); ++i) {
    while (convex_hull.size() >= 2) {
      if (convex_hull[convex_hull.size() - 1].VectorProduct(sorted_points[i]) ==
          0) {
        convex_hull.pop_back();
        continue;
      }
      Vector last_side = convex_hull[convex_hull.size() - 1];
      last_side -= convex_hull[convex_hull.size() - 2];
      Vector new_side = sorted_points[i];
      new_side -= convex_hull[convex_hull.size() - 1];
      if (last_side.VectorProduct(new_side) <= 0) {
        convex_hull.pop_back();
      } else {
        break;
      }
    }
    convex_hull.push_back(sorted_points[i]);
  }
  return FindArea(convex_hull);
}

int main() {
  PrepareIO();
  size_t count;
  std::cin >> count;
  std::cout.setf(std::ios::fixed);
  std::cout.precision(1);
  std::vector<Vector> points(count);
  size_t min_point = 0;
  for (size_t i = 0; i < count; ++i) {
    long long coord_x;
    long long coord_y;
    std::cin >> coord_x >> coord_y;
    points[i] = {coord_x, coord_y};
    if (coord_x < points[min_point].x or
        (coord_x == points[min_point].x and coord_y < points[min_point].y)) {
      min_point = i;
    }
  }
  std::vector<Vector> convex_hull;
  double area = FindConvexHull(points, min_point, convex_hull);
  std::cout << convex_hull.size() << "\n";
  convex_hull[0] += points[min_point];
  std::cout << convex_hull[0].x << " " << convex_hull[0].y << "\n";
  for (long long i = convex_hull.size() - 1; i > 0; --i) {
    convex_hull[i] += points[min_point];
    std::cout << convex_hull[i].x << " " << convex_hull[i].y << "\n";
  }
  std::cout << area;
}
