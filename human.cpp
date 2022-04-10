#include <iostream>
#include <string.h>
#include <locale.h>
#include <cstdlib>
#include <math.h>

using namespace std;

#define PI 3.14159265                                  

class Coord {
private:

	double longtitude; 
	double latitude;	
	double newLongtitude; 
	double newLatitude; 

	long double allDist; 
	long double Dist; 
	long double d; //angular distance in a iteration

public:
	Coord(double longtitude, double latitude)
	{
		allDist = 0;
		Dist = 0;
		d = 0;

		if (longtitude >= 0 && longtitude <= 180)
		{
			this->longtitude = longtitude;
		}
		else 
		{
			cout << "Error, it's uncorrect longtitude value" << endl;
			this->longtitude = -1;
		}

		if (latitude >= 0 && latitude <= 90)
		{
			this->latitude = latitude;
			
		}
		else 
		{
			cout << "Error, it's uncorrect latitude value" << endl;
			this->latitude = -1;
		}
		newLatitude = this->latitude;
		newLongtitude = this->longtitude;
	}

	void move()
	{
		longtitude = newLongtitude;
		latitude = newLatitude;
		newLatitude += 0 + rand() % 15 - 5;
		newLongtitude += 0 + rand() % 15 - 5;
	}

	void setCoordinates(double longtitude, double latitude) {
		this->longtitude = longtitude;
		this->latitude = latitude;
	}

	double getLongtitude() {
		return longtitude;
	}

	double getLatitude() {
		return latitude;
	}

	double getDist() {
		long double Latitud = latitude * PI / 180;
		long double newLatitud = newLatitude * PI / 180;
		long double newLongtitud = newLongtitude * PI / 180;
		long double longtitud = longtitude * PI / 180;

		d = 2 * abs(asin(sqrt(pow(sin((newLatitud - Latitud) / 2), 2) + (cos(Latitud) * cos(newLatitud) * pow(sin(abs(newLongtitud - longtitud) / 2), 2)))));
		Dist = d * 6372.795;
		allDist += Dist;
		return Dist>0.1?Dist:0;
	}

	double getAllDist() {
		return allDist;

	}

	double getNewLongtitude()
	{
		return newLongtitude;
	}

	double getNewLatitude()
	{
		return newLatitude;
	}

	void showStartCoordinates() {
		cout << "\nStart longtitude: " << getLongtitude() << endl;
		cout << "Start latitude: " << getLatitude() << endl;
	}

	void showNewCoordinates()
	{
		cout << "\nCurrent longtitude: " << getNewLongtitude() << endl;
		cout << "Start latitude: " << getNewLatitude() << endl;
	}
};

class Human : public Coord {
private:
	string Name;
	string Surname;
	string Patronymi;
	double Weight;
	double Height;
	int Age;

public:
	Human(string surname, string name, string patronymi, int age, double weight, double height, double longt, double latit) : Coord(longt, latit) 
	{
		setParameters(name, surname, patronymi, age, weight, height);
	}

	void setParameters(string Name, string Surname, string Patronymi, int Age, double Weight, double Height) {
	    this->Name = Name;
		this->Surname = Surname;
		this->Patronymi = Patronymi;
		this->Age = Age;
		this->Weight = Weight;
		this->Height = Height;
	}
};

int main() {

	int lifeTime;
	cout << "Enter a program life time: " << endl;
	cin >> lifeTime;
	

	Human* human = new Human("Bolotov", "Egor", "Denisovich", 20, 60, 178, 30, 76);
	human->showStartCoordinates();

	for (int i = 0; i < lifeTime; i++)
	{
		human->move();
		human->showNewCoordinates();
		cout << "The distance walked in an iteration: " << human->getDist() << " kh" << endl;
	}

	cout << "\nThe distance walked in the life time " << human->getAllDist() << " kh" << endl;
}
