#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Объявление метода (с использованием делегата) 
// для обработки события
delegate void MethodContainer(int count);
delegate void newVehicle(string su);
delegate void deleteVehicle(string su);
delegate void editedVehicle(string su);

ref class Writer
{
public:
    // Объявляем события
    event MethodContainer^ onCount; // объявление события onCount c типом делегата MethodContainer
    event newVehicle^ nVehicle; // объявление события nVehicle(новое трансп. ср-во в некотором гараже) c типом делегата newVehicle
    
    event deleteVehicle^ delVehicle;
    event editedVehicle^ edVehicle;

    // Вызываем события
    void newVehicle(string su)
    {
        nVehicle(su);
    }

    void deleteVehicle(string su)
    {
        delVehicle(su);
    }

    void editedVehicle(string su)
    {
        edVehicle(su);
    }
};

// классы ClassEvent реагируeт на событие класса Writer записью строки в консоль.
ref class ClassEvent
{
public:
    void Message(string su)
    {
        cout << "New vehicle is added " << su << endl;
    }
};

class Vehicle // Создаём класс транспортного средства
{  
private:
    string type, name, color; // Вид транспорта, название, цвет;
    int garage;  // Гараж, в который поместить транспорт

public:
    Vehicle(string sType, string sName, string sColor, int iGarage)
    {
        type = sType;
        name = sName;
        color = sColor;
        garage = iGarage;
    }

    // Вывод информации об объекте транспорта
    void showVehicle()
    {
        cout << "Type: " << type << endl;
        cout << "Name: " << name << endl;
        cout << "Color: " << color << endl;
        cout << "Location: Garage " << garage << endl;
    }

    // сеттеры и геттеры для взаимодействия с приватными полями класса
    void setName(string sName) { name = sName; }
    void setColor(string sColor) { color = sColor; }
    void setGarage(int iGarage) { garage = iGarage; }
    string getType() { return type; }
    string getName() { return name; }
    string getColor() { return color; }
    int getGarage() { return garage; }
};


// Класс гараж для хранения экземляров класса транспорт
class Garage
{
private:
    int number;
    vector <Vehicle> garage;

public:
    // При создании присваиваем гаражу номер
    Garage(int iNumber) { number = iNumber; }

    // Геттер для получения номера гаража
    int getNumber() { return number; }

    // Добавление транспорта в гараж
    void addVehicle(Vehicle newVehicle) { garage.push_back(newVehicle); }

    // Удаление транспорта по названию и цвету
    void deleteVehicle(string sName, string sColor)
    {
        vector<Vehicle> nGarage;
        for (auto &v : garage)
        {
            if (v.getName() != sName || v.getColor() != sColor)
                nGarage.push_back(v);
        }
        garage = nGarage;
    }

    // Редактирование информации о выбранном по названию и цвету транспорте
    // Возвращает отредактированный объект - это нужно для записи в логи в процессе работы с классом
    Vehicle editVehicle(string sName, string sColor)
    {
        vector<Vehicle> nGarage;
        for (auto &v : garage)
        {
            if (v.getName() == sName && v.getColor() == sColor)
            {
                Vehicle nVehicle(v.getType(), sName, sColor, v.getGarage());
                cout << "What information do you want to edit?\n1 - name\n2 - color\n3 - garage" << endl;
                int ans; cin >> ans;
                if (ans == 1)
                {
                    cout << "Enter new vehicle's name: " << endl;
                    string newName; cin >> newName;
                    nVehicle.setName(newName);
                }
                else if (ans == 2)
                {
                    cout << "Enter new vehicle's color: " << endl;
                    string newColor; cin >> newColor;
                    nVehicle.setColor(newColor);
                }
                else if (ans == 3)
                {
                    cout << "Enter new garage's number to replace trasfer the vehicle:" << endl;
                    int newGarage; cin >> newGarage;
                    nVehicle.setGarage(newGarage);
                }
                nGarage.push_back(nVehicle);
                return nVehicle;
            }
            else { nGarage.push_back(v); }
        }
        garage = nGarage;
    }

    // Вывод информации о транспортных средствах в гараже
    void showGarage()
    {
        cout << "Garage number " << number << endl;
        for (auto v : garage) {v.showVehicle();}
    }
};

void event(string str)
{
    Writer^ writer = gcnew Writer();
    ClassEvent^ Event = gcnew ClassEvent();
    writer->newVehicle(str);
    writer->deleteVehicle(str);
    writer->editedVehicle(str);
}

int main()
{
    vector<Garage> garages; // Контейнер для хранения гаражений
    ofstream file("logs.txt");
    // Цикл работает до тех пор, пока пользователь не выйдет из программы (пока ans != 5)
    while (true)
    {
        cout << "\nChoose option:" << endl;
        cout << "1) Add vehicle" << endl;
        cout << "2) Edit vehicle" << endl;
        cout << "3) Delete Vehicle" << endl;
        cout << "4) Show garages list" << endl;
        cout << "5) Exit program\n" << endl;
        int ans; cin >> ans;

        if (ans == 1) // Добавление транспорта
        {
            cout << "Enter new vehicle's type, name, color and number of garage for it:" << endl;
            string sType, sName, sColor; int iGarage;
            cin >> sType >> sName >> sColor >> iGarage;
            Vehicle vehicle(sType, sName, sColor, iGarage);

            bool found = false;
            for (auto &v : garages)
            {
                if (v.getNumber() == iGarage)
                {
                    found = true;
                    v.addVehicle(vehicle);
                }
            }
            if (!found)
            {
                Garage garage(iGarage);
                garage.addVehicle(vehicle);
                garages.push_back(garage);
            }

            // Передаём название транспорта с помощью сеттера
            event(vehicle.getName());
            // Запись в файл
            file << vehicle.getName() << " was added into garage " << vehicle.getGarage() << "\n";
        }
        else if (ans == 2)
        {
            cout << "Enter vehicle's garage, name and color to edit:" << endl;
            int iGarage; cin >> iGarage;
            string sName, sColor; cin >> sName >> sColor;
            for (auto g : garages)
            {
                if (g.getNumber() == iGarage)
                {
                    Vehicle newV = g.editVehicle(sName, sColor);

                    event(newV.getName());
                    file << sName << sColor << " in garage " << iGarage << " was edited and became ";
                    file << newV.getName() << " " << newV.getColor() << " in garage " << newV.getGarage() << endl;
                    break;
                }
                else { cout << "The vehicle is not found!" << endl; }
            }

        }
        else if (ans == 3) // Удаление транспорта
        {
            cout << "Enter vehicle's garage, name and color to delete:" << endl;
            int iGarage; cin >> iGarage;
            string sName, sColor; cin >> sName >> sColor;
            for (auto g : garages)
            {
                if (g.getNumber() == iGarage) { g.deleteVehicle(sName, sColor); }
            }

            event(sName);
            file << sName << " in garage " << iGarage << " was deleted" << endl;
        }
        else if (ans == 4) // Вывод транспортных средств
        {
            for (auto g : garages)
            {
                g.showGarage();
            }
        }
        else if (ans == 5) { break; }
        else { cout << "Unknown input!" << endl; }
    }
    file.close();
    return 0;
}