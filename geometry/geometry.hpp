#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace Geometry {

  class Vector;

  class IShape;

  class Point;

  class Segment;

  class Ray;

  class Line;

  class Circle;

  class Polygon;

  template <typename T>
  int Sign(T x) {
    return (x == 0 ? 0 : x / std::abs(x));
  }

  int Sign(double x) {
    double eps = 1e-6;
    if (x < -eps) {
      return -1;
    }
    if (x > eps) {
      return 1;
    }
    return 0;
  }

  class Vector {
   public:
    Vector() { x = y = 0; }

    Vector(int x, int y) : x(x), y(y) {}

    Vector& operator=(const Vector& other) = default;

    ~Vector() = default;

    Vector& operator+=(const Vector& other) {
      x += other.x;
      y += other.y;
      return *this;
    }

    Vector& operator-=(const Vector& other) {
      x -= other.x;
      y -= other.y;
      return *this;
    }

    Vector& operator*=(const int kValue) {
      x *= kValue;
      y *= kValue;
      return *this;
    }

    Vector operator-() const { return {-x, -y}; }

    int x;
    int y;
  };

/////////////////////////Vector/////////////////////////
  long long operator*(const Vector& l, const Vector& r) {
    return l.x * r.x + l.y * r.y;
  }

  Vector operator*(const Vector& l, int value) {
    return {l.x * value, l.y * value};
  }

  Vector operator*(int value, const Vector& l) {
    return {l.x * value, l.y * value};
  }

  long long operator^(const Vector& l, const Vector& r) {
    return l.x * r.y - l.y * r.x;
  }

  Vector operator+(const Vector& l, const Vector& r) {
    Vector res(l.x + r.x, l.y + r.y);
    return res;
  }

  Vector operator-(const Vector& l, const Vector& r) {
    Vector res(l.x - r.x, l.y - r.y);
    return res;
  }

  bool operator==(const Vector& l, const Vector& r) {
    return l.x == r.x && l.y == r.y;
  }

  std::ostream& operator<<(std::ostream& out, const Vector& str) {
    out << "Vector(" << str.x << ", " << str.y << ")";
    return out;
  }

  class IShape {
   public:
    virtual ~IShape() = default;

    virtual IShape& Move(const Vector&) = 0;

    virtual bool ContainsPoint(const Point&) const = 0;

    virtual bool CrossesSegment(const Segment&) const = 0;

    virtual IShape* Clone() const = 0;

    virtual std::string ToString() const = 0;
  };

  class Point : public IShape {
   public:
    Point() = default;

    Point(int x, int y);

    Point& operator=(const Point& other) = default;

    IShape& Move(const Vector& vector) override;

    bool ContainsPoint(const Point& in_point) const override;

    std::string ToString() const override;

    bool CrossesSegment(const Segment& seg) const override;

    IShape* Clone() const override;

    Vector coordinate;
  };

  class Segment : public IShape {
   public:
    Segment() = default;

    Segment(const Point& l, const Point& r);

    Segment& operator=(const Segment& other) = default;

    IShape& Move(const Vector& vector) override;

    bool ContainsPoint(const Point& point) const override;

    bool ContainsPoint(double x, double y) const;

    bool CrossesSegment(const Segment& seg) const override;

    std::string ToString() const override;

    IShape* Clone() const override;

    Point GetL() const;

    Point GetR() const;

   private:
    Point l_;
    Point r_;
  };

  class Line : public IShape {
   public:
    Line() = default;

    Line(const Point& l, const Point& r);

    Line& operator=(const Line& other) = default;

    IShape& Move(const Vector& vector) override;

    bool ContainsPoint(const Point& point) const override;

    bool CrossesSegment(const Segment& seg) const override;

    std::string ToString() const override;

    IShape* Clone() const override;

   private:
    Point l_;
    Point r_;
    int a_ = 0;
    int b_ = 0;
    int c_ = 0;
  };

  class Ray : public IShape {
   public:
    Ray() = default;

    Ray(const Point& point, const Point& point1);

    Ray& operator=(const Ray& other) = default;

    IShape& Move(const Vector& vector) override;

    bool ContainsPoint(const Point& point) const override;

    bool CrossesSegment(const Segment& seg) const override;

    std::string ToString() const override;

    IShape* Clone() const override;

   private:
    Point point_;
    Vector vector_;
  };

  class Polygon : public IShape {
   public:
    Polygon() = default;

    explicit Polygon(std::vector<Point> points);

    Polygon& operator=(const Polygon& other) = default;

    IShape& Move(const Vector& vector) override;

    bool ContainsPoint(const Point& point) const override;

    bool CrossesSegment(const Segment& seg) const override;

    std::string ToString() const override;

    IShape* Clone() const override;

   private:
    std::vector<Point> points_;
  };

  class Circle : public IShape {
   public:
    Circle() = default;

    Circle(const Point& center, int radius);

    Circle& operator=(const Circle& other) = default;

    IShape& Move(const Vector& vector) override;

    bool ContainsPoint(const Point& point) const override;

    bool CrossesSegment(const Segment& seg) const override;

    std::string ToString() const override;

    IShape* Clone() const override;

   private:
    Point center_;
    int radius_ = 0;
  };

////////////////////////////////////Point///////////////////////////////////////
  Point::Point(int x, int y) : coordinate(x, y) {}

  IShape& Point::Move(const Vector& vector) {
    coordinate.x += vector.x;
    coordinate.y += vector.y;
    return *this;
  }

  bool Point::ContainsPoint(const Point& in_point) const {
    return coordinate == in_point.coordinate;
  }

  std::string Point::ToString() const {
    std::string output;
    output = "Point(" + std::to_string(coordinate.x) + ", " +
             std::to_string(coordinate.y) + ")";
    return output;
  }

  bool Point::CrossesSegment(const Segment& seg) const {
    return seg.ContainsPoint(*this);
  }

  IShape* Point::Clone() const {
    auto* clone = new Point(this->coordinate.x, this->coordinate.y);
    return clone;
  }

  Vector operator-(const Point& l, const Point& r) {
    Vector vector = l.coordinate - r.coordinate;
    return vector;
  }

///////////////////////////////////Segment//////////////////////////////////////
  Segment::Segment(const Point& l, const Point& r) : l_(l), r_(r) {}

  IShape& Segment::Move(const Vector& vector) {
    l_.Move(vector);
    r_.Move(vector);
    return *this;
  }

  bool Segment::ContainsPoint(const Point& point) const {
    return Sign((l_ - point) ^ (point - r_)) == 0 &&
           std::min(l_.coordinate.x, r_.coordinate.x) <= point.coordinate.x &&
           std::max(l_.coordinate.x, r_.coordinate.x) >= point.coordinate.x &&
           std::min(l_.coordinate.y, r_.coordinate.y) <= point.coordinate.y &&
           std::max(l_.coordinate.y, r_.coordinate.y) >= point.coordinate.y;
  }

  bool Segment::ContainsPoint(double x, double y) const {
    double eps = 1e-6;
    return (Sign((l_.coordinate.x - x) * (y - r_.coordinate.y) -
                 (l_.coordinate.y - y) * (x - r_.coordinate.x)) == 0) &&
           std::min(l_.coordinate.x, r_.coordinate.x) - x < eps &&
           std::max(l_.coordinate.x, r_.coordinate.x) - x > -eps &&
           std::min(l_.coordinate.y, r_.coordinate.y) - y < eps &&
           std::max(l_.coordinate.y, r_.coordinate.y) - y > -eps;
  }

  bool Segment::CrossesSegment(const Segment& seg) const {
    return seg.ContainsPoint(l_) || seg.ContainsPoint(r_) ||
           ContainsPoint(seg.l_) || ContainsPoint(seg.r_) ||
           (Sign(((l_ - r_) ^ (l_ - seg.r_)) * ((l_ - r_) ^ (l_ - seg.l_))) ==
            -1 &&
            Sign(((seg.l_ - seg.r_) ^ (seg.l_ - r_)) *
                 ((seg.l_ - seg.r_) ^ (seg.l_ - l_))) == -1);
  }

  std::string Segment::ToString() const {
    std::string output;
    output = "Segment(" + l_.ToString() + ", " + r_.ToString() + ")";
    return output;
  }

  IShape* Segment::Clone() const {
    auto* clone = new Segment(l_, r_);
    return clone;
  }

  Point Segment::GetL() const { return l_; }

  Point Segment::GetR() const { return r_; }

//////////////////////////////////////Line//////////////////////////////////////
  Line::Line(const Point& l, const Point& r) : l_(l), r_(r) {
    a_ = r.coordinate.y - l.coordinate.y;
    b_ = l.coordinate.x - r.coordinate.x;
    c_ = l.coordinate.y * (r.coordinate.x - l.coordinate.x) -
         l.coordinate.x * (r.coordinate.y - l.coordinate.y);
  }

  IShape& Line::Move(const Vector& vector) {
    l_.Move(vector);
    r_.Move(vector);
    c_ += -a_ * vector.x - b_ * vector.y;
    return *this;
  }

  bool Line::ContainsPoint(const Point& point) const {
    return a_ * point.coordinate.x + b_ * point.coordinate.y + c_ == 0;
  }

  bool Line::CrossesSegment(const Segment& seg) const {
    return ContainsPoint(seg.GetL()) || ContainsPoint(seg.GetR()) ||
           (Sign((l_ - r_) ^ (l_ - seg.GetL())) *
            ((l_ - r_) ^ (l_ - seg.GetR()))) == -1;
  }

  std::string Line::ToString() const {
    std::string output;
    output = "Line(" + std::to_string(a_) + ", " + std::to_string(b_) + ", " +
             std::to_string(c_) + ")";
    return output;
  }

  IShape* Line::Clone() const {
    auto* clone = new Line(l_, r_);
    return clone;
  }

////////////////////////////////////Ray/////////////////////////////////////////
  Ray::Ray(const Point& point, const Point& point1) : point_(point) {
    vector_ = point1 - point;
  }

  IShape& Ray::Move(const Vector& vector) {
    point_.Move(vector);
    return *this;
  }

  bool Ray::ContainsPoint(const Point& point) const {
    return vector_.x * (point.coordinate.y - point_.coordinate.y) ==
           vector_.y * (point.coordinate.x - point_.coordinate.x) &&
           Sign(vector_.x) * Sign(point.coordinate.x - point_.coordinate.x) >=
           0 &&
           Sign(vector_.y) * Sign(point.coordinate.y - point_.coordinate.y) >= 0;
  }

  bool Ray::CrossesSegment(const Segment& seg) const {
    return ContainsPoint(seg.GetL()) || ContainsPoint(seg.GetR()) ||
           (Sign((vector_ ^ (seg.GetL() - point_)) *
                 (vector_ ^ (seg.GetR() - point_))) == -1 &&
            vector_ * (seg.GetL() - point_) >= 0 &&
            vector_ * (seg.GetR() - point_) >= 0);
  }

  std::string Ray::ToString() const {
    std::string output;
    output = "Ray(" + point_.ToString() + ", Vector(" +
             std::to_string(vector_.x) + ", " + std::to_string(vector_.y) + "))";
    return output;
  }

  IShape* Ray::Clone() const {
    Point point1(point_);
    point1.Move(vector_);
    auto* clone = new Ray(point_, point1);
    return clone;
  }

/////////////////////////////////////Polygon////////////////////////////////////
  Polygon::Polygon(std::vector<Point> points) : points_(std::move(points)) {}

  IShape& Polygon::Move(const Vector& vector) {
    for (auto& point : points_) {
      point.Move(vector);
    }
    return *this;
  }

  bool Polygon::ContainsPoint(const Point& point) const {
    for (size_t i = 1; i < points_.size(); i++) {
      Segment seg_i(points_[i - 1], points_[i]);
      if (seg_i.ContainsPoint(point)) {
        return true;
      }
    }
    Segment seg_0(points_[points_.size() - 1], points_[0]);
    if (seg_0.ContainsPoint(point)) {
      return true;
    }
    while (true) {
      Point point1(point);
      point1.Move({rand() % 100 + 1, rand() % 100 + 1});
      Ray ray(point, point1);
      bool cnt = false;
      bool ok = true;
      for (const auto& point_i : points_) {
        ok &= 1 - static_cast<int>(ray.ContainsPoint(point_i));
      }
      if (ok) {
        for (size_t i = 1; i < points_.size(); i++) {
          cnt ^=
                  static_cast<int>(ray.CrossesSegment({points_[i - 1], points_[i]}));
        }
        cnt ^=
                static_cast<int>(ray.CrossesSegment({*points_.rbegin(), points_[0]}));
        return cnt;
      }
    }
  }

  bool Polygon::CrossesSegment(const Segment& seg) const {
    for (size_t i = 1; i < points_.size(); i++) {
      Segment seg_i(points_[i - 1], points_[i]);
      if (seg.CrossesSegment(seg_i)) {
        return true;
      }
    }
    Segment seg_0(*points_.rbegin(), points_[0]);
    return seg.CrossesSegment(seg_0);
  }

  std::string Polygon::ToString() const {
    std::string output = "Polygon(";
    for (size_t i = 0; i < points_.size(); i++) {
      output += points_[i].ToString();
      if (i != points_.size() - 1) {
        output += ", ";
      }
    }
    output += ")";
    return output;
  }

  IShape* Polygon::Clone() const {
    auto* clone = new Polygon(points_);
    return clone;
  }

/////////////////////////////////////Circle/////////////////////////////////////
  Circle::Circle(const Point& center, int radius)
          : center_(center), radius_(radius) {}

  IShape& Circle::Move(const Vector& vector) {
    center_.Move(vector);
    return *this;
  }

  bool Circle::ContainsPoint(const Point& point) const {
    return (long long)(center_.coordinate.x - point.coordinate.x) *
           (center_.coordinate.x - point.coordinate.x) +
           (center_.coordinate.y - point.coordinate.y) *
           (center_.coordinate.y - point.coordinate.y) <=
           (long long)radius_ * radius_;
  }

  bool Circle::CrossesSegment(const Segment& seg) const {
    Point l = seg.GetL();
    Point r = seg.GetR();
    l.Move(center_.coordinate * -1);
    r.Move(center_.coordinate * -1);
    long long a = r.coordinate.y - l.coordinate.y;
    long long b = l.coordinate.x - r.coordinate.x;
    long long c = l.coordinate.y * (r.coordinate.x - l.coordinate.x) -
                  l.coordinate.x * (r.coordinate.y - l.coordinate.y);
    if (c * c - (long long)radius_ * radius_ * (a * a + b * b) > 0) {
      return false;
    }
    double x0 = (double)-a * c / (a * a + b * b) + center_.coordinate.x;
    double y0 = (double)-b * c / (a * a + b * b) + center_.coordinate.y;
    if (c * c - (long long)radius_ * radius_ * (a * a + b * b) == 0) {
      return seg.ContainsPoint(x0, y0);
    }
    double mul =
            sqrt(((double)radius_ * radius_ - (double)c * c / (a * a + b * b)) /
                 (double)(a * a + b * b));
    return seg.ContainsPoint(x0 + mul * b, y0 - mul * a) ||
           seg.ContainsPoint(x0 - mul * b, y0 + mul * a);
  }

  std::string Circle::ToString() const {
    std::string output = "Circle(";
    output += center_.ToString() + ", " + std::to_string(radius_) + ")";
    return output;
  }

  IShape* Circle::Clone() const {
    auto* clone = new Circle(center_, radius_);
    return clone;
  }
}  // namespace Geometry
