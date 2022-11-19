#include <string>
class SomeClass {
public:
  SomeClass(const std::string &value);
  SomeClass();
  std::string get_name();

private:
  std::string name_;
  int age;
};