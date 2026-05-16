#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <array>

class Car {
private:
    std::string model;
    std::array<double, 3> fuel;
    int maxSpeed;
    int power;

public:
    Car() : model(""), fuel{0.0, 0.0, 0.0}, maxSpeed(0), power(0) {}

    Car(const std::string& m, double fuelHighway, double fuelCity, double fuelMixed,
        int speed, int p)
            : model(m), fuel{fuelHighway, fuelCity, fuelMixed}, maxSpeed(speed), power(p) {}

    Car(const Car&) = default;
    Car& operator=(const Car&) = default;

    Car(Car&&) = default;
    Car& operator=(Car&&) = default;

    ~Car() = default;

    const std::string& getModel() const { return model; }

    friend std::ostream& operator<<(std::ostream& os, const Car& car) {
        os << "Модель: " << car.model
           << ", расход (трасса/город/смешанный): " << car.fuel[0] << "/" << car.fuel[1] << "/" << car.fuel[2]
           << " л/100км, макс. скорость: " << car.maxSpeed << " км/ч, мощность: " << car.power << " л.с.";
        return os;
    }
};

int main() {
    std::vector<Car> cars;
    std::ifstream inFile("input.txt");
    if (!inFile.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл input.txt" << std::endl;
        return 1;
    }

    std::string model;
    double fuelHighway, fuelCity, fuelMixed;
    int speed, power;
    while (inFile >> model >> fuelHighway >> fuelCity >> fuelMixed >> speed >> power) {
        cars.emplace_back(model, fuelHighway, fuelCity, fuelMixed, speed, power);
    }
    inFile.close();

    if (cars.empty()) {
        std::cerr << "Файл пуст или содержит некорректные данные" << std::endl;
        return 1;
    }

    std::vector<Car> carsCopy;
    carsCopy.resize(cars.size());
    std::copy(cars.begin(), cars.end(), carsCopy.begin());

    std::sort(cars.begin(), cars.end(),
              [](const Car& a, const Car& b) { return a.getModel() < b.getModel(); });

    std::ofstream outFile("output.txt");
    if (!outFile.is_open()) {
        std::cerr << "Ошибка: не удалось создать файл output.txt" << std::endl;
        return 1;
    }

    outFile << "=== Исходный контейнер (до сортировки) ===" << std::endl;
    for (const auto& car : carsCopy) {
        outFile << car << std::endl;
    }

    outFile << "\n=== Контейнер после сортировки по названию модели ===" << std::endl;
    for (const auto& car : cars) {
        outFile << car << std::endl;
    }

    outFile << "\n=== Контейнер, скопированный из исходного (std::copy) ===" << std::endl;
    for (const auto& car : carsCopy) {
        outFile << car << std::endl;
    }

    outFile.close();
    std::cout << "Результаты записаны в файл output.txt" << std::endl;
    return 0;
}
