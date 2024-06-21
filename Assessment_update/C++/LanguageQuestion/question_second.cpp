#include <iostream>  
#include <cmath>
  
class Shape {  
public:  
    virtual double calculateArea() const = 0;
};  
  
class Circle : public Shape {  
private:  
    double radius;  
  
public:  
    Circle(double r) : radius(r) {}  
  
    double calculateArea() const override {  
        return M_PI * radius * radius;
    }  
};  
  
class Rectangle : public Shape {  
private:  
    double width;  
    double height;  
  
public:  
    Rectangle(double w, double h) : width(w), height(h) {}  
   
    double calculateArea() const override {  
        return width * height;  
    }  
};  
  
int main() {  
    Circle circle(5.0);  
    std::cout << "Circle area: " << circle.calculateArea() << std::endl;  
  
    Rectangle rectangle(4.0, 6.0);  
    std::cout << "Rectangle area: " << rectangle.calculateArea() << std::endl;  
  
    return 0;  
}