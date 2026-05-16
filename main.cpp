#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class Triangle{
private:
    double a, b, c;

public:
    Triangle(double a, double b, double c);
    void print() const;
};

class TriangleError : public invalid_argument{
private:
    double a, b, c;

public:
    TriangleError(const string& msg, double a, double b, double c)
            : invalid_argument(msg), a(a), b(b), c(c) {}

    void print() const
    {
        cout << "Ошибка: " << what() << endl;
        cout << "Стороны: " << a << ", " << b << ", " << c << endl;
    }
};

Triangle::Triangle(double a, double b, double c)
{
    if (a <= 0 || b <= 0 || c <= 0)
        throw TriangleError("Стороны должны быть положительными", a, b, c);
    if (a + b <= c || a + c <= b || b + c <= a)
        throw TriangleError("Неравенство треугольника не выполнено", a, b, c);
    this->a = a;
    this->b = b;
    this->c = c;
}

void Triangle::print() const
{
    cout << "Треугольник со сторонами: " << a << ", " << b << ", " << c << endl;
}

int main()
{
    try {
        Triangle t(3, 4, 5);
        t.print();
    } catch (TriangleError& e) {
        e.print();
    }
    try {
        Triangle t(1, 1, 3);
        t.print();
    } catch (TriangleError& e) {
        e.print();
    }

    return 0;
}
