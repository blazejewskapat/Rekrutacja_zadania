#include <iostream>
#include <cstdlib>
#include <unistd.h>

using namespace std;

// Klasa bazowa samochodu
class Car {
public:
    string name;
    unsigned short speed;
    float temperature;
    short angle;
    unsigned short turnovers;
    unsigned short max_speed;
    unsigned short turnovers_max;

    // Konstruktor
    Car() {
        speed = 0;
        temperature = 0;
        angle = 0;
        turnovers = 0;
        max_speed = 0;
        turnovers_max = 0;
        cout<<"Kierowca wsiada do auta"<<endl;
    }

    // Destruktor
    ~Car() {
        cout<<"Kierowca wysiada z auta"<<endl;
    }

    // Przygotowanie auta do jazdy - inicjalizacja parametrow
    void prepare_car(string brand_name) {
        name = brand_name;
        temperature = 20.0;
        angle = 0;
        turnovers = 1000;
        cout<<"Auto "<<name<<" gotowe do jazdy"<<endl;
    }

    // Uruchomienie auta - przyjete srednie wartosci 50km/h /2k obrotow
    void run_with_basic(unsigned short val_s, unsigned short val_t) {
        speed = val_s;
        turnovers = val_t;
        cout<<"Uruchomiono auto"<<endl;
    }

    // Zwalnianie predkosci
    void slow_down() {

        decrease_turnovers(); //Spadaja obroty

        if (speed <20) {
            temperature-=0.1; //Gdy niska predkosc moze spasc temp
        }
        else {
            speed -= 5; //Zwalnianie
            if (temperature <20){}
            else temperature -= 0.01; //Gdy niska predkosc moze spasc temp
        }
    }

    // Zwiekszanie predkosci
    void speed_up() {

        increase_turnovers(); //Rosna obroty

        if (speed > max_speed-15){ // Auto osiagnelo predkosc maksymalna
            temperature += 0.05; // Temperatura silnika rosnie
        }
        else {
            speed+=15; //Przyspieszanie
            if (temperature >= 90) {} //Uwaga! Bardzo goracy silnik
            else temperature+=5; // Jak nie goracy to rosnie
        }
    }

    // Wybranie ruchu na podstawie losowanej wartosci
    void move(int state) {
        if (state == 0) slow_down();
        else if (state == 1) speed_up();
        else if (state == 2) move_left();
        else if (state == 3) move_right();
        else {} //No action
    }

    // Ruch kierownica w lewo
    void move_left() {

        slow_down(); //Przed zakretem zwalniamy
        if (angle <= -90) {} //Mozemy osiagnac maksymalny skret kierownicy
        else angle -= 5;
    }

    void move_right() {

        slow_down(); //Przed zakretem zwalniamy
        if (angle >= 90) {} //Mozemy osiagnac maksymalny skret kierownicy
        else angle += 5;
    }

    // Zwiekszanie obrotow silnika
    void increase_turnovers() {
        if (turnovers <= turnovers_max-1500) { //Sprawdzenie czy juz osiagniete maksymalne mozliwe obr
            turnovers+=1500; // Jak nie to zwiekszane
        }
        else {} //No action
    }

    // Zmniejszanie obrotow silnika
    void decrease_turnovers() {
        if (turnovers >= 1500) { // Sprawdzanie czy nie minimum - bo auto stanie
            turnovers -= 500;
        }
        else {} //No action
    }

    // Zatrzymanie auta
    void stop(){
        speed = 0;
        angle = 0;
        turnovers = 0;
        temperature = 0;
        cout<<"Auto zatrzymane"<<endl;
    }

    // Pobranie predkosci
    unsigned short get_speed(){
        return this->speed;
    }

    // Pobranie temperatury
    float get_temperature(){
        return temperature;
    }

    // Pobranie kąta
    short get_angle(){
        return angle;
    }

    // Pobranie obrotow
    unsigned short get_turnovers(){
        return turnovers;
    }
};

// Kaza z marek posiada indywidualna predkosc max i zakres obrotow
// Klasa dziedzicząca po klasie Car, marka auta: Volvo
class Car_volvo:public Car {
public:
    Car_volvo() {
        max_speed = 250;
        turnovers_max = 9000;
    }
};

// Klasa dziedzicząca po klasie Car, marka auta: Toyota
class Car_toyota:public Car {
public:
    Car_toyota() {
        max_speed = 200;
        turnovers_max= 6000;
    }
};

// Klasa dziedzicząca po klasie Car, marka auta: Fiat
class Car_maluch:public Car {
public:
    Car_maluch() {
        max_speed = 100;
        turnovers_max = 5000;
    }
};

// Aktualny status samochodu
void get_actual_data(Car &Auto) {
    cout<<"Predkosc: "<<Auto.get_speed()<<endl;
    printf("Temperatura silnika: %.2f\n",Auto.get_temperature());
    cout<<"Kat kierownicy: "<<Auto.get_angle()<<endl;
    cout<<"Obroty silnika: "<<Auto.get_turnovers()<<endl;
}

int main ()
{
    int fp;
    char sign;
    int state = 1;
    string name;
    Car *Auto;

    cout<<"Modele do wyboru:"<<endl;
    cout<<"a. Volvo"<<endl;
    cout<<"b. Toyota"<<endl;
    cout<<"c. Maluch"<<endl;
    cout<<"Wybierz jakie auto chcesz dzis testowac: "<<endl;
    cin>>sign;

    // Przygotowanie obiektu zgodnie z wybraną marką
    switch(sign){
        case 'a':
            Auto = new Car_volvo();
            name = "Volvo";
            break;
        case 'b':
            Auto = new Car_toyota();
            name = "Toyota";
            break;
        case 'c':
            Auto = new Car_maluch();
            name = "Maluch";
            break;
        default:
            cout<<"To nie jest symulator roweru!"<<endl;
            state = 0;
            break;
    }

    // Jesli wybrano poprawnie - auto rusza
    if (state == 1) {

        Auto->prepare_car(name);
        // Wybranie czestotliwosci probkowania informacji
        // Latwiej przyjac od uzytkownika czas
        cout << "Wybierz czas co jaki chcesz pozyskiwac dane w [s]:" << endl;
        cin >> fp;
        while (fp < 1 || fp > 10) {
            cout << "Wybierz czas pomiedzy 1 a 10 sekund" << endl;
            cin >> fp;
        }

        // Ustawienie wartosci poczatkowych ruchu
        Auto->run_with_basic(50, 2000);

        // Symulacja ruchu auta
        for (int j = 0; j < 10; j++) {
            for (int i = 0; i < 15; i++) {
                int val = rand() % 4;
                Auto->move(val);
            }
            // Podanie aktualnych informacji
            get_actual_data(*Auto);
            sleep(fp); // Oczekiwanie
            cout << endl;
        }
        Auto->stop();
        delete Auto;
    }
    else{
        cout<<"Koniec testow"<<endl;
    }
    return 0;
}