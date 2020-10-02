

#include <stdio.h>

#include <memory>

enum class Colors { GREEN = 1, YELLOW = 2, RED = 3 };

class State {
 private:
  Colors color_;

 public:
  std::shared_ptr<int> i;
  // int * i;
  // std::string i;

  State() { color_ = Colors::GREEN; }

  Colors getColor() const { return color_; }
};

class Base {
  State s_;

 public:
  virtual State* getState() { return &s_; }

  //virtual const State* getState() const { return &s_; }
};

class Derived : public Base {
 public:
  Derived() : Base() {}
};

class BreakingStuff {
 public:
  void write(const Derived& d) {
    State* s = ((Base)d).getState();
    // const State * s = d.getState();
    auto color = (int)s->getColor();
    printf("%i", color);
  }
};

int main() {
  Derived d;
  BreakingStuff b;
  b.write(d);
}