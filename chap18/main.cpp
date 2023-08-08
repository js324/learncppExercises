#include <iostream>
#include <vector>
class Shape {
public:
    virtual std::ostream& print(std::ostream& out) = 0;
    friend std::ostream& operator<<(std::ostream& out, Shape& shape) {
        return shape.print(out);
    }
       
    virtual ~Shape() = default;
};
class Point{
private:
    int m_x;
    int m_y;
public:
    Point() = default;
    Point(int x, int y) : m_x{ x }, m_y{ y } {

    }
    
};
class Circle : public Shape {
private:
    Point m_center{};
    int m_radius{};
public:
    Circle(const Point& center, int radius) : m_radius{ radius }, m_center{ center } {}
    std::ostream& print(std::ostream& out) {
        out << "Circle";
        return out;
    }
    int getRadius() {
        return m_radius;
    }
};
class Triangle : public Shape {
private:
    Point m_p1{};
    Point m_p2{};
    Point m_p3{};
public:
    Triangle(const Point& p1, const Point& p2, const Point& p3): m_p1{p1}, m_p2{p2}, m_p3{p3} {}
    std::ostream& print(std::ostream& out) {
        out << "Triangle";
        return out;
    }
};
int getLargestRadius(std::vector<Shape*> v) {
    int max = -1;
    for (auto* element : v) {
        auto* ptr = dynamic_cast<Circle*>(element);
        if (ptr) {
            max = ptr->getRadius() > max ? ptr->getRadius() : max;
        }
    }
    return max;
}
int main()
{
    std::vector<Shape*> v{
        new Circle{ Point{ 1, 2 }, 7 },
            new Triangle{ Point{ 1, 2 }, Point{ 3, 4 }, Point{ 5, 6 } },
            new Circle{ Point{ 7, 8 }, 3 }
    };

    for (auto element : v) {
        std::cout << *element << '\n';
    }
    std::cout << "The largest radius is: " << getLargestRadius(v) << '\n'; // write this function

    // delete each element in the vector here

    return 0;
}
