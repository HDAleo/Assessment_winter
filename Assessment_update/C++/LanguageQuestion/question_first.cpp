#include <iostream>  
#include <string>  
  
class Person {  
private:  
    std::string name;
    int age;
  
public:  
    Person(const std::string& personName, int personAge) : name(personName), age(personAge) {  
    }  
  
    void display() const {  
        std::cout << "Name: " << name << ", Age: " << age << std::endl;  
    }  
};  
  
int main() {  
    Person person1("Alice", 30);  
    Person person2("Bob", 25);  
  
    person1.display();  
    person2.display();  
  
    return 0;  
}
