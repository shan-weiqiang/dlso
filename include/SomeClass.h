#include <string>
class SomeClass {
public:
  SomeClass(const std::string &value);
  SomeClass();
  std::string get_name() const;
  int get_age() const;

private:
  std::string name_;
  int age;
};