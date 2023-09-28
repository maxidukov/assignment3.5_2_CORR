#include <iostream>
#include <initializer_list>

class Base {
  int sidenum;
  std::string name;
  double *params;

public:
  Base(std::initializer_list<double> arglist) {
    set_sidenum(arglist.size() / 2);
    int i{};
    params = new double[sidenum * 2];
    for (double const &val : arglist) {
      if (i == sidenum * 2) {
        std::cout << "Even number of arguments needed. Last argument ignored\n";
        break;
      } else {
        params[i++] = val;
      }
    }
    set_name("Фигура");
  }
  Base(){
    set_sidenum(0);
    set_name("Фигура");
    params = nullptr;
  }
  int get_sidenum() { return sidenum; }
  std::string get_name() { return name; }
  void set_sidenum(int sidenum) { this->sidenum = sidenum; }
  void set_name(std::string name) { this->name = name; }
  void print_info() {
    std::cout << name << ": "
              << "\n";
    if (params) {
      char symb = 'a';
      std::cout << "Стороны: ";
      for (int i{}, j{}; i < sidenum * 2; ++i, ++j) {
        if (i == sidenum) {
          symb = 'A';
          std::cout << "\nУглы: ";
          j = 0;
        }
        std::cout << char(symb + j) << "=" << params[i] << " ";
      }
    } else {
      std::cout << "Количество сторон: " << sidenum;
    }
    std::cout << std::endl << std::endl;
  }
  Base(const Base &bs_first)
      : sidenum(bs_first.sidenum),
        name(bs_first.name) { // deep copy constructor
    if (bs_first.params) {
      params = new double[sidenum * 2];
      for (int i = 0; i < sidenum * 2; i++)
        params[i] = bs_first.params[i];
    } else
      params = nullptr; // this is for Base objects with uninitialized params
  }
  Base & operator=(const Base &bs_first) { // deep copy assignment overloading
    // self-assignment is a special case: don't need to do anything
    if (this == &bs_first) {
      return *this;
    } else {
      sidenum = bs_first.sidenum;
      name = bs_first.name;
      if (bs_first.params) { // this is for Base objects with uninitialized params
        params = new double[sidenum * 2];
        for (int i = 0; i < sidenum * 2; ++i) { // copy bs_first's values
          params[i] = bs_first.params[i];       // into this array
        }
      } else
        params = nullptr; // this is for Base objects with uninitialized params
      return *this;
    }
  }
  ~Base(){
      delete [] params;
  }
};

void print_info(Base*);

class Triangle : public Base {
public:
  Triangle(double a, double b, double c, double A, double B, double C)
      : Base({a, b, c, A, B, C}) {
    set_name("Треугольник");
  }
};
class Right_Triangle : public Triangle {
public:
  Right_Triangle(double a, double b, double c, double A, double B)
      : Triangle(a, b, c, A, B, 90) {
    set_name("Прямоугольный треугольник");
  }
};

class Isosceles : public Triangle {
public:
  Isosceles(double a, double b, double A, double B)
      : Triangle(a, b, a, A, B, A) {
    set_name("Равнобедренный треугольник");
  }
};

class Equilateral : public Isosceles {
public:
  Equilateral(double a) : Isosceles(a, a, 60, 60) {
    set_name("Равносторонний треугольник");
  }
};
class Quadrangle : public Base {
public:
  Quadrangle(double a, double b, double c, double d, double A, double B,
             double C, double D)
      : Base({a, b, c, d, A, B, C, D}) {
    set_name("Четырёхугольник");
  }
};
class Parallelogram : public Quadrangle {
public:
  Parallelogram(double a, double b, double A, double B)
      : Quadrangle(a, b, a, b, A, B, A, B) {
    set_name("Параллелограмм");
  }
};
class Rectangle : public Parallelogram {
public:
  Rectangle(double a, double b) : Parallelogram(a, b, 90,90) {
    set_name("Прямоугольник");
  }
};
class Square : public Rectangle {
public:
  Square(double a) : Rectangle(a, a) { set_name("Квадрат"); }
};
class Rhombus : public Parallelogram {
public:
  Rhombus(double a, double A, double B) : Parallelogram(a, a, A, B) {
    set_name("Ромб");
  }
};

int main() {
  // Triangle ABC;
  //Base bs;
  //print_info(&bs);
  Triangle ABC(10, 20, 30, 50, 60, 70);
  //ABC.print_info();
  print_info(&ABC);
  Right_Triangle rABC(10, 20, 30, 50, 60);
  //rABC.print_info();
  print_info(&rABC);
  Isosceles ABA(10, 20, 50, 60);
  //ABA.print_info();
  print_info(&ABA);
  Equilateral AAA(30);
  //AAA.print_info();
  print_info(&AAA);
  Quadrangle ABCD(10, 20, 30, 40, 50, 60, 70, 80);
  //ABCD.print_info();
  print_info(&ABCD);
  Rectangle ABABr(10, 20);
  //ABABr.print_info();
  print_info(&ABABr);
  Square AAAA(20);
  //AAAA.print_info();
  print_info(&AAAA);
  Parallelogram ABAB(20, 30, 30, 40);
  //ABAB.print_info();
  print_info(&ABAB);
  Rhombus rhAAAA(30, 30, 40);
  //rhAAAA.print_info();
  print_info(&rhAAAA);

  // std::streamsize prec = std::cout.precision();
}

void print_info(Base* pbs){
  pbs->print_info();
}
