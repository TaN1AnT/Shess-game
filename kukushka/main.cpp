#include <iostream>
#include "windows.h"
#include <ctime>

using namespace std;

class Date {
private:
    int day;
    int month;
    int year;
public:
    Date() {
        time_t seconds = time(0);
        tm* date = localtime(&seconds);
        day = date->tm_mday;
        month = date->tm_mon + 1;
        year = date->tm_year + 1900;
    }
    Date(int _day, int _month, int _year) {
        day = _day;
        month = _month;
        year = _year;
    }
    Date(const Date& old_date) {
        day = old_date.day;
        month = old_date.month;
        year = old_date.year;
    }
    ~Date() {}
    int getDay() {
        return day;
    }
    int getMonth() {
        return month;
    }
    int getYear() {
        return year;
    }
    void printDate() {
        if (this->day < 10)
            cout << "0";
        cout << this->day << ".";
        if (this->month < 10)
            cout << "0";
        cout << this->month << ".";
        if (this->year % 100 < 10)
            cout << "0";
        cout << this->year % 100 << endl;
    }

    Date& setDay(int new_day) {
        day = new_day;
        return *this;
    }
    Date& setMonth(int new_month) {
        month = new_month;
        return *this;
    }
    Date& setYear(int new_year) {
        year = new_year;
        return *this;
    }
};

enum class Placement {
    CAGE,
    AVIARY,
    AQUARIUM,
    TERRARIUM
};


// Animal
class Animal {
private:
    char* kind;
    char* name;
    char* country;
    Date date_birth;

public:
    Animal() {
        try {
            kind = new char[9];
        }
        catch (bad_alloc) {
            abort();
        }
        memcpy(kind, "Невідомо", sizeof(char) * 9);
        try {
            name = new char[9];
        }
        catch (bad_alloc) {
            abort();
        }
        memcpy(name, "Невідомо", sizeof(char) * 9);
        try {
            country = new char[9];
        }
        catch (bad_alloc) {
            abort();
        }
        memcpy(country, "Невідомо", sizeof(char) * 9);
        date_birth = Date();
    }

    Animal(const char* _kind, const char* _name, const char* _country, Date _date_birth) {
        try {
            kind = new char[strlen(_kind) + 1];
        }
        catch (bad_alloc) {
            abort();
        }
        memcpy(kind, _kind, sizeof(char) * (strlen(_kind) + 1));

        try {
            name = new char[strlen(_name) + 1];
        }
        catch (bad_alloc) {
            abort();
        }
        memcpy(name, _name, sizeof(char) * (strlen(_name) + 1));

        try {
            country = new char[strlen(_country) + 1];
        }
        catch (bad_alloc) {
            abort();
        }
        memcpy(country, _country, sizeof(char) * (strlen(_country) + 1));
        date_birth = _date_birth;
    }
    Animal(const Animal& old_animal) {
        try {
            kind = new char[strlen(old_animal.kind) + 1];
        }
        catch (bad_alloc) {
            abort();
        }
        memcpy(kind, old_animal.kind, sizeof(char) * (strlen(old_animal.kind) + 1));
        try {
            name = new char[strlen(old_animal.name) + 1];
        }
        catch (bad_alloc) {
            abort();
        }
        memcpy(name, old_animal.name, sizeof(char) * (strlen(old_animal.name) + 1));
        try {
            country = new char[strlen(old_animal.country) + 1];
        }
        catch (bad_alloc) {
            abort();
        }
        memcpy(country, old_animal.country, sizeof(char) * (strlen(old_animal.country) + 1));
        date_birth = old_animal.date_birth;
    }
    ~Animal() {}
    char* getKind() {
        return kind;
    }
    char* getName() {
        return name;
    }
    char* getCountry() {
        return country;
    }
    Date getDate() {
        return date_birth;
    }
    void print() {
        cout << "Вид тварини : " << kind << endl
            << "Страна походження: " << country << endl
            << "Кличка тварини: " << name << endl
            << "Дата народження: "; date_birth.printDate();
    }

    Animal& setName(const char* new_name) {
        delete[] name;
        try {
            name = new char[strlen(new_name) + 1];
        }
        catch (bad_alloc) {
            abort();
        }
        memcpy(name, new_name, sizeof(char) * (strlen(new_name) + 1));
        return *this;
    }
    Animal& setCountry(const char* new_country) {
        delete[] country;
        try {
            country = new char[strlen(new_country) + 1];
        }
        catch (bad_alloc) {
            abort();
        }
        memcpy(country, new_country, sizeof(char) * (strlen(new_country) + 1));
        return *this;
    }
    Animal& setKind(const char* new_kind) {
        delete[] kind;
        try {
            kind = new char[strlen(new_kind) + 1];
        }
        catch (bad_alloc) {
            abort();
        }
        memcpy(kind, new_kind, sizeof(char) * (strlen(new_kind) + 1));
        return *this;
    }
    Animal& setDate(Date new_date_birth) {
        date_birth = new_date_birth;
        return *this;
    }


};


class Unit {
private:
    Animal animal;
    /*Placement placement;*/
    Date date;
    int price;


public:
    Unit() {

        animal = Animal();
        date = Date();
        price = 0;
    }
    Unit(Animal _animal, /*Placement _placement,*/ Date _date, int _price) {

        animal = _animal;
        date = _date;
        price = _price;

    }
    Unit(const Unit& old_unit) {

        animal = old_unit.animal;
        date = old_unit.date;
        price = old_unit.price;

    }
    ~Unit() {}

    Animal getAnimal() {
        return animal;
    }
    Date getDate() {
        return date;
    }
    int getPrice() {
        return price;
    }

    void print() {
        cout << "Дата прийняття: ";
        date.printDate();
        animal.print();
        cout << "Вартість утримання: " << price << " грн";
    }


    /*Place& setPlacement(Placement new_placement) {
        placement = new_form_of_conducting;
        return *this;
    }*/
    Unit& setAnimal(Animal new_animal) {
        animal = new_animal;
        return *this;
    }
    Unit& setDate(Date new_date) {
        date = new_date;
        return *this;
    }
    Unit& setPrice(int new_price) {
        price = new_price;
        return *this;
    }
};

class Place {
private:
    Unit* arr_ptr;
    Placement placement;
    int number;
    int square;
    int price_cleaning;
    int len;

public:
    Place() {
        placement = Placement::CAGE;
        arr_ptr = nullptr;
        number = 0;
        square = 0;
        price_cleaning = 0;
        len = 0;

    }
    Place(Unit* _arr_ptr, Placement _placement, int _number, int _square, int _price_cleaning, int _len) {
        placement = _placement;
        arr_ptr = _arr_ptr;
        number = _number;
        square = _square;
        price_cleaning = _price_cleaning;
        len = _len;


    }
    /*Tour(Unit* _arr_ptr, int _len) {

        arr_ptr = _arr_ptr;
        len = _len;


    }*/

    Place(const Place& old_Place) {
        placement = old_Place.placement;
        arr_ptr = old_Place.arr_ptr;
        number = old_Place.number;
        square = old_Place.square;
        price_cleaning = old_Place.price_cleaning;
        len = old_Place.len;


    }
    ~Place() {}

    Placement getPlacement() {
        return placement;
    }
    Unit* getArrPtr() {
        return arr_ptr;
    }
    int getNumber() {
        return number;
    }
    int getSquare() {
        return square;
    }
    int getPrice_Cleaning() {
        return price_cleaning;
    }
    int getLen() {
        return len;
    }

    Place& setPlacement(Placement new_placement) {
        placement = new_placement;
        return *this;
    }
    Place& setArrPtr(Unit* new_arr_ptr) {
        arr_ptr = new_arr_ptr;
        return *this;
    }
    Place& setLen(int new_len) {
        len = new_len;
        return *this;
    }
    Place& setNumber(int new_number) {
        number = new_number;
        return *this;
    }
    Place& setSquare(int new_square) {
        square = new_square;
        return *this;
    }
    Place& setPrice_Cleaning(int new_price_cleaning) {
        price_cleaning = new_price_cleaning;
        return *this;
    }


    Place& addPlace(Unit unit) {
        Unit* new_arr_ptr;
        try {
            new_arr_ptr = new Unit[len + 1];
        }
        catch (bad_alloc) {
            abort();
        }
        memcpy(new_arr_ptr, arr_ptr, sizeof(Unit) * len);
        new_arr_ptr[len++] = unit;
        arr_ptr = new_arr_ptr;
        return *this;
    }

    Place& deletePlace(int index) {
        Unit* new_arr_ptr;
        try {
            new_arr_ptr = new Unit[len - 1];
        }
        catch (bad_alloc) {
            abort();
        }
        for (int i = 0; i < index; i++)
            new_arr_ptr[i] = arr_ptr[i];
        for (int i = index + 1; i < len; i++)
            new_arr_ptr[i - 1] = arr_ptr[i];
        len--;
        arr_ptr = new_arr_ptr;
        return *this;
    }

    void print() {
        cout << "Загальна кількість приміщень: " << len << "\n";
        for (int i = 0; i < len; i++) {
            arr_ptr[i].print();
            cout << endl;
        }
    }

    void shortPrint() {
        cout << "------Коротка інформація-----\nПриміщення" << endl
            << "Номер вольеру: " << number << endl
            << "Ціна: " << price_cleaning << endl;



    }

    //void shortPrint(int _price) {
    //    cout << "-----Коротка інформація-----\nЕкскурcія" << endl
    //        << "Ціна: " << _price << " грн" << endl
    //        << "Час: "; date.printDate(); cout << endl;


    //}

};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Place Ex1;
    int placement, number, size, price_cleaning;
    cout << "Тип розміщення:" << endl
        << "0 - Клітка" << endl
        << "1 - Вольер" << endl
        << "2 - Акваріум" << endl
        << "3 - Тераріум" << endl
        << "Вибір: ";
    cin >> placement;
    cout << "Введіть номер клітки" << endl;
    cin >> number;
    cout << "Введіть площу клітки" << endl;
    cin >> size;
    cout << "Введіть ціну прибирання клітки" << endl;
    cin >> price_cleaning;

    Place Ex2(nullptr, Placement(placement), number, size, price_cleaning, 0);

    Place Ex3 = Ex2;

    cout << "__________Перший__________" << endl;
    Ex1.print();
    Ex1.shortPrint();
    cout << "__________Другий__________" << endl;
    Ex2.print();
    Ex2.shortPrint();
    cout << "__________Третій__________" << endl;
    Ex3.print();
    Ex3.shortPrint();



    // animal
    //kind,country,name
    cin.ignore();
    char* kind = new char[255];
    cout << "\n\n***************************\nВид тварини: ";
    cin.getline(kind, 255);

    char* country = new char[255];
    cout << "Країна походження: ";
    cin.getline(country, 255);

    char* name = new char[255];
    cout << "Кличка тварини: ";
    cin.getline(name, 255);
    cin.ignore();

    //Дата народження тварини
    int day1, month1, year1;
    cout << "Дата народження:" << endl;
    cout << "-- День: ";
    cin >> day1;
    cout << "-- Місяць: ";
    cin >> month1;
    cout << "-- Рік: ";
    cin >> year1;
    cout << endl;

    //Дата попадання до зоо
    int day2, month2, year2;
    cout << "Дата потрапляння до Зоопарку:" << endl;
    cout << "-- День: ";
    cin >> day2;
    cout << "-- Місяць: ";
    cin >> month2;
    cout << "-- Рік: ";
    cin >> year2;
    cout << endl;

    //price

    int price_life;
    cout << "Ціна утримання: ";
    cin >> price_life;
    cin.ignore();



    //Unit unit(Organisator(org_name, org_surname), Form_of_conducting(form_of_conducting), Date(day, month, year), location, price);
    Unit unit(Animal(kind, country, name, Date(day1, month1, year1)), Date(day2, month2, year2), price_life);
    Ex2.addPlace(unit);
    cout << "\n***************************" << endl << endl;
    cout << "__________Перший__________" << endl;
    Ex1.print();
    Ex1.shortPrint();
    cout << "__________Другий__________" << endl;
    Ex2.print();
    Ex2.shortPrint();

    cout << "__________Третій__________" << endl;
    Ex3.print();
    Ex3.shortPrint();

    return 0;
}