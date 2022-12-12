#include <string>
#include <iostream>
#include<fstream>
#include<cstring>
#include<stdio.h>


using namespace std;

#pragma warning(disable : 4996)

//prima clasa 
class Persoana {
	char* nume = nullptr;
	int* chirie_lunara = nullptr;
	int numar_luni;

	const int id;
public:
	//metoda virtuala persoana
	virtual void persoana() {
		cout << "sunt o persoana";
	}
	static int nr_persoane;
	//constructor fara parametrii
	Persoana() :id(-1)
	{
		this->nume = new char[strlen("Daniel") + 1];
		strcpy(this->nume, "Daniel");
		this->chirie_lunara = nullptr;
		this->numar_luni = 0;
		this->nr_persoane++;
	}
	//constructor cu parametrii
	Persoana(const char* nume, int* chirie_lunara, int numar_luni, int id) :id(id)
	{
		if (nume != nullptr)
		{
			this->nume = new char[strlen(nume) + 1];
			strcpy(this->nume, nume);
		}
		this->numar_luni = numar_luni;
		if (this->numar_luni > 0) {
			this->chirie_lunara = new int[numar_luni];
			for (int i = 0; i < this->numar_luni; i++) {
				this->chirie_lunara[i] = chirie_lunara[i];
			}
		}
		else chirie_lunara = nullptr;
		this->nr_persoane++;
	}
	//constructor de copiere
	Persoana(const Persoana& copie) :id(copie.id + 1) {
		if (copie.nume != nullptr) {
			this->nume = new char[strlen(copie.nume) + 1];
			strcpy(this->nume, copie.nume);
		}
		this->numar_luni = copie.numar_luni;
		if (copie.numar_luni != 0) {
			this->chirie_lunara = new int[copie.numar_luni];
			for (int i = 0; i < copie.numar_luni; i++)
				this->chirie_lunara[i] = copie.chirie_lunara[i];
			this->nr_persoane = copie.nr_persoane;
		}
	}
	//destructor
	~Persoana() {
		if (nume != nullptr) {
			delete[] nume;
		}
		if (chirie_lunara != nullptr) {
			delete[] chirie_lunara;
		}
		this->nr_persoane--;
	}
	friend ostream& operator<<(ostream& out, Persoana persoana);
	friend istream& operator>>(istream& in, Persoana& persoana);
	//supraincarcarea operatorului = 
	Persoana& operator=(const Persoana& persoana)
	{
		if (this->nume != nullptr) {
			delete[] this->nume;
		}
		if (persoana.nume != nullptr) {
			this->nume = new char[strlen(persoana.nume) + 1];
			strcpy(this->nume, persoana.nume);
		}
		else this->nume = nullptr;
		this->numar_luni = persoana.numar_luni;
		if (chirie_lunara != 0) {
			delete[] this->chirie_lunara;
		}
		if (persoana.chirie_lunara != 0) {
			this->chirie_lunara = new int[persoana.numar_luni];
			for (int i = 0; i < persoana.numar_luni; i++) {
				this->chirie_lunara[i] = persoana.chirie_lunara[i];
			}
		}

		return *this;
	}
	// operatorul de indexare
	char operator[](int index)
	{
		if (index >= 0 && index < strlen(this->nume)) {
			return this->nume[index];
		}
		else {
			cout << endl
				<< "Index out of range" << endl;
			return '-';
		}
	}
	// operatorul +
	int operator+(int numar_luni)
	{
		return this->numar_luni + numar_luni;
	}
	//operatorul ++
	Persoana& operator+=(int luni_aditionale)
	{
		this->numar_luni += luni_aditionale;
		return *this;
	}

	// preincrementare
	Persoana& operator++()
	{
		this->numar_luni += 2;
		return *this;
	}

	// postincrementare
	Persoana operator++(int)
	{
		Persoana copie = *this;
		this->numar_luni += 2;
		return copie;
	}
	//operatorul cast 
	operator double()
	{
		return this->numar_luni;
	}
	// operatorul !
	bool operator!() {
		if (this->nume != nullptr) {
			return true;
		}
		else {
			return false;
		}
	}
	//operatorul < 
	bool operator<(Persoana p)
	{
		if (this->numar_luni < p.numar_luni)
			return true;
		else return false;
	}
	//operatorul =
	bool operator==(Persoana& persoana)
	{
		if (this->nume == persoana.nume)
			return 1;
		else return 0;
	}
	//getter+setter nume
	char* get_nume() {
		return this->nume;
	}
	void setNume(const char* NumeNou) {
		this->nume = new char[strlen(NumeNou) + 1];
		strcpy(this->nume, NumeNou);
	}
	//getter+setter numar luni
	int getnumar_luni() {
		return this->numar_luni;
	}
	void setNumar_Luni(int numar_luniNou) {
		this->numar_luni = numar_luniNou;
	}
	friend ifstream& operator>>(ifstream& in, Persoana& persoana);
	friend ofstream& operator<<(ofstream& out, Persoana persoana);
};
//citire din fisier text
ifstream& operator>>(ifstream& in, Persoana& persoana)
{
	char buffer[50];
	in >> ws;
	in.getline(buffer, 50);
	strcpy(persoana.nume, buffer);
	in >> persoana.numar_luni;
	if (persoana.chirie_lunara != nullptr) {
		delete[]persoana.chirie_lunara;
	}
	persoana.chirie_lunara = new int[persoana.numar_luni];
	for (int i = 0; i < persoana.numar_luni; i++)
		in >> persoana.chirie_lunara[i];
	return in;
}
//afisare intr-un fisier binar
ofstream& operator<<(ofstream& out, Persoana persoana)
{
	out << endl
		<< "Nume   ";
	if (persoana.nume != nullptr) {
		out << persoana.nume;
	}
	else {
		out << "-";
	}
	out << " id persoana    " << persoana.id;
	out << "  numar luni   " << persoana.numar_luni;
	out << "   chiria lunara:   ";
	if (persoana.chirie_lunara != nullptr)
	{
		for (int i = 0; i < persoana.numar_luni; i++)
			out << "  " << persoana.chirie_lunara[i];
	}
	return out;
}
//supraincarcare operator <<
ostream& operator<<(ostream& out, Persoana persoana)
{
	out << endl
		<< "Nume   ";
	if (persoana.nume != nullptr) {
		out << persoana.nume;
	}
	else {
		out << "-";
	}
	out << " id persoana    " << persoana.id;
	out << "  numar luni   " << persoana.numar_luni;
	out << "   chiria lunara:   ";
	if (persoana.chirie_lunara != nullptr)
	{
		for (int i = 0; i < persoana.numar_luni; i++)
			out << "  " << persoana.chirie_lunara[i];
	}

	return out;
}
//supraincarcare operator >>
istream& operator>>(istream& in, Persoana& persoana)
{
	cout << endl;
	cout << "nume persoana= ";
	char buffer[1000];
	in.ignore(numeric_limits<streamsize>::max(), '\n');
	in.getline(buffer, 1000);
	if (persoana.nume != nullptr)
	{
		delete[]persoana.nume;
	}
	persoana.nume = new char[strlen(buffer) + 1];
	strcpy(persoana.nume, buffer);
	cout << " numar luni ";
	in >> persoana.numar_luni;
	if (persoana.chirie_lunara != nullptr) {
		delete[]persoana.chirie_lunara;
	}
	persoana.chirie_lunara = new int[persoana.numar_luni];
	for (int i = 0; i < persoana.numar_luni; i++)
		in >> persoana.chirie_lunara[i];
	return in;
}

class Cheltuiala {
	int suma_platita_lunara[20];
	char* bancnota = nullptr;
	int nr_luni_cheltuieli;
public:
	//metoda virtuala cheltuiala
	virtual void cheltuiala() {
		cout << "Eu platesc o anumita suma de bani pentru o cheltuiala";
	}
	Cheltuiala()
	{
		this->bancnota = new char[strlen("euro") + 1];
		strcpy(this->bancnota, "euro");
		for (int i = 0; i < this->nr_luni_cheltuieli; i++)
		{
			this->suma_platita_lunara[i] = suma_platita_lunara[i];
		}
		this->nr_luni_cheltuieli = 0;
	}
	Cheltuiala(const char* bancnota, int suma_platita_lunara[20], int nr_luni_cheltuieli)
	{
		if (bancnota != nullptr)
		{
			this->bancnota = new char[strlen(bancnota) + 1];
			strcpy(this->bancnota, bancnota);
		}
		this->nr_luni_cheltuieli = nr_luni_cheltuieli;
		if (this->nr_luni_cheltuieli > 0) {
			for (int i = 0; i < this->nr_luni_cheltuieli; i++) {
				this->suma_platita_lunara[i] = suma_platita_lunara[i];
			}
		}
	}
	Cheltuiala(const Cheltuiala& copie) {
		if (copie.bancnota != nullptr) {
			this->bancnota = new char[strlen(copie.bancnota) + 1];
			strcpy(this->bancnota, copie.bancnota);
		}
		this->nr_luni_cheltuieli = copie.nr_luni_cheltuieli;
		if (copie.nr_luni_cheltuieli != 0) {

			for (int i = 0; i < copie.nr_luni_cheltuieli; i++)
				this->suma_platita_lunara[i] = copie.suma_platita_lunara[i];
		}
	}
	~Cheltuiala() {
		if (bancnota != nullptr) {
			delete[] bancnota;
		}
	}
	friend ostream& operator<<(ostream& out, Cheltuiala cheltuieli);
	friend istream& operator>>(istream& in, Cheltuiala& cheltuieli);
	friend ofstream& operator<<(ofstream& out, Cheltuiala cheltuiala);
	friend ifstream& operator>>(ifstream& in, Cheltuiala& cheltuiala);
	Cheltuiala& operator=(const Cheltuiala& cheltuieli)
	{
		if (this->bancnota != nullptr) {
			delete[] this->bancnota;
		}
		if (cheltuieli.bancnota != nullptr) {
			this->bancnota = new char[strlen(cheltuieli.bancnota) + 1];
			strcpy(this->bancnota, cheltuieli.bancnota);
		}
		else this->bancnota = nullptr;
		this->nr_luni_cheltuieli = cheltuieli.nr_luni_cheltuieli;
		for (int i = 0; i < cheltuieli.nr_luni_cheltuieli; i++) {
			this->suma_platita_lunara[i] = cheltuieli.suma_platita_lunara[i];
		}

		return *this;
	}
	char operator[](int index)
	{
		if (index >= 0 && index < strlen(this->bancnota)) {
			return this->bancnota[index];
		}
		else {
			cout << endl
				<< "Index out of range" << endl;
			return '-';
		}
	}
	double operator+(int nr_luni_cheltuieli)
	{
		return this->nr_luni_cheltuieli + nr_luni_cheltuieli;
	}

	Cheltuiala& operator+=(int nr_luni_aditionale)
	{
		this->nr_luni_cheltuieli += nr_luni_aditionale;
		return *this;
	}

	// preincrementare
	Cheltuiala& operator++()
	{
		this->nr_luni_cheltuieli += 2;
		return *this;
	}

	// postincrementare
	Cheltuiala operator++(int)
	{
		Cheltuiala copie = *this;
		this->nr_luni_cheltuieli += 2;
		return copie;
	}
	operator int()
	{
		return this->nr_luni_cheltuieli;
	}
	// operatorul !
	bool operator!() {
		if (this->bancnota != nullptr) {
			return true;
		}
		else {
			return false;
		}
	}
	//operatorul < 
	bool operator<(Cheltuiala c)
	{
		if (this->nr_luni_cheltuieli < c.nr_luni_cheltuieli)
			return true;
		else return false;
	}
	//operatorul =
	bool operator==(Cheltuiala& cheltuiala)
	{
		if (this->bancnota == cheltuiala.bancnota)
			return 1;
		else return 0;
	}
	char* get_bancnota() {
		return this->bancnota;
	}
	void setBancnota(const char* BancnotaNoua) {
		this->bancnota = new char[strlen(BancnotaNoua) + 1];
		strcpy(this->bancnota, BancnotaNoua);
	}
	int getnr_luni_cheltuieli() {
		return this->nr_luni_cheltuieli;
	}
	void setNumar_Luni(int numar_luniNou) {
		this->nr_luni_cheltuieli = numar_luniNou;
	}
};

ostream& operator<<(ostream& out, Cheltuiala cheltuieli)
{
	out << endl
		<< "bancnota   ";
	if (cheltuieli.bancnota != nullptr) {
		out << cheltuieli.bancnota;
	}
	else {
		out << "-";
	}

	out << "  numar luni   " << cheltuieli.nr_luni_cheltuieli;
	out << "   plata lunara:   ";
	for (int i = 0; i < cheltuieli.nr_luni_cheltuieli; i++)
		out << "  " << cheltuieli.suma_platita_lunara[i];


	return out;
}
istream& operator>>(istream& in, Cheltuiala& cheltuieli)
{
	cout << endl;
	cout << "nume bancnota= ";
	char buffer[1000];
	in.ignore(numeric_limits<streamsize>::max(), '\n');
	in.getline(buffer, 1000);
	if (cheltuieli.bancnota != nullptr)
	{
		delete[]cheltuieli.bancnota;
	}
	cheltuieli.bancnota = new char[strlen(buffer) + 1];
	strcpy(cheltuieli.bancnota, buffer);
	cout << " numar luni ";
	in >> cheltuieli.nr_luni_cheltuieli;

	for (int i = 0; i < cheltuieli.nr_luni_cheltuieli; i++)
		in >> cheltuieli.suma_platita_lunara[i];
	return in;
}
//citire din fisier text
ifstream& operator>>(ifstream& in, Cheltuiala& cheltuiala)
{
	char buffer[50];
	in >> ws;
	in.getline(buffer, 50);
	strcpy(cheltuiala.bancnota, buffer);
	in >> cheltuiala.nr_luni_cheltuieli;
	for (int i = 0; i < cheltuiala.nr_luni_cheltuieli; i++)
		in >> cheltuiala.suma_platita_lunara[i];
	return in;
	
}
//afisare intr-un fisier binar
ofstream& operator<<(ofstream& out, Cheltuiala cheltuiala)
{
	out << endl
		<< "bancnota   ";
	if (cheltuiala.bancnota != nullptr) {
		out << cheltuiala.bancnota;
	}
	else {
		out << "-";
	}

	out << "  numar luni   " << cheltuiala.nr_luni_cheltuieli;
	out << "   plata lunara:   ";
	for (int i = 0; i < cheltuiala.nr_luni_cheltuieli; i++)
		out << "  " << cheltuiala.suma_platita_lunara[i];

	return out;
}

class CheltuialaUtilitati :public Cheltuiala {
private:
	char* nume_utilitate = nullptr;
	int cantitate_consumata;
public:
	void cheltuiala() {
		cout << "Eu platesc o suma de bani pentru cheltuieli utilitati care sunt tot o cheltuiala";
	}
	CheltuialaUtilitati() :Cheltuiala()
	{
		this->nume_utilitate = new char[strlen("apa") + 1];
		strcpy(this->nume_utilitate, "apa");
		this->cantitate_consumata = 200;
	}
	CheltuialaUtilitati(const char* bancnota, int suma_platita_lunara[50], int nr_luni_cheltuieli, const char* nume_utilitate, int cantitate_consumata)
		:Cheltuiala(bancnota, suma_platita_lunara, nr_luni_cheltuieli)
	{
		this->nume_utilitate = new char[strlen(nume_utilitate) + 1];
		strcpy(this->nume_utilitate, nume_utilitate);
		this->cantitate_consumata = cantitate_consumata;
	}
	CheltuialaUtilitati(const CheltuialaUtilitati& copie)
		: Cheltuiala(copie)
	{
		cout << endl;
		this->nume_utilitate = new char[strlen(copie.nume_utilitate) + 1];
		strcpy(this->nume_utilitate, copie.nume_utilitate);
		this->cantitate_consumata = copie.cantitate_consumata;

	}
	~CheltuialaUtilitati()
	{
		if (this->nume_utilitate != nullptr) {
			delete[]nume_utilitate;
		}
	}
	CheltuialaUtilitati& operator=(const CheltuialaUtilitati& cheltuiala)
	{
		cout << endl;
		Cheltuiala::operator=(cheltuiala);
		this->nume_utilitate = new char[strlen(cheltuiala.nume_utilitate) + 1];
		strcpy(this->nume_utilitate, cheltuiala.nume_utilitate);
		this->cantitate_consumata = cheltuiala.cantitate_consumata;
		return *this;
	}
	char* getNumeUtilitate()
	{
		return this->nume_utilitate;
	}
	int getCantitateConsumata() {
		return this->cantitate_consumata;
	}
	void setNumeUtilitate(const char* NumeNou) {
		this->nume_utilitate = new char[strlen(NumeNou) + 1];
		strcpy(this->nume_utilitate, NumeNou);
	}
	void setCantitateConsumata(int cantitateNoua) {
		this->cantitate_consumata = cantitateNoua;
	}
	friend ostream& operator<<(ostream&, CheltuialaUtilitati);
	friend istream& operator>>(istream&, CheltuialaUtilitati&);
	friend ofstream& operator<<(ofstream&, CheltuialaUtilitati);
	friend ifstream& operator>>(ifstream&, CheltuialaUtilitati&);
	char operator[](int index)
	{
		if (index >= 0 && index < strlen(this->nume_utilitate)) {
			return this->nume_utilitate[index];
		}
		else {
			cout << endl
				<< "Index out of range" << endl;
			return '-';
		}
	}
	int operator+(int cantitate_consumata)
	{
		return this->cantitate_consumata + cantitate_consumata;
	}
	CheltuialaUtilitati& operator+=(int cantitate_aditionala)
	{
		this->cantitate_consumata += cantitate_aditionala;
		return *this;
	}

	// preincrementare
	CheltuialaUtilitati& operator++()
	{
		this->cantitate_consumata += 200;
		return *this;
	}

	// postincrementare
	CheltuialaUtilitati operator++(int)
	{
		CheltuialaUtilitati copie = *this;
		this->cantitate_consumata += 200;
		return copie;
	}
	operator double()
	{
		return this->cantitate_consumata;
	}
	// operatorul !
	bool operator!() {
		if (this->nume_utilitate != nullptr) {
			return true;
		}
		else {
			return false;
		}
	}
	//operatorul < 
	bool operator<(CheltuialaUtilitati cu)
	{
		if (this->cantitate_consumata < cu.cantitate_consumata)
			return true;
		else return false;
	}
	//operatorul =
	bool operator==(CheltuialaUtilitati& cheltuiala)
	{
		if (this->nume_utilitate == cheltuiala.nume_utilitate)
			return 1;
		else return 0;
	}
};
//citire din fisier text
ifstream& operator>>(ifstream& in, CheltuialaUtilitati& cheltuiala)
{
	in >> (Cheltuiala&)cheltuiala;
	cout << endl;
	char buffer[1000];
	in >> ws;
	in.ignore(numeric_limits<streamsize>::max(), '\n');
	in.getline(buffer, 1000);
	if (cheltuiala.nume_utilitate != nullptr)
	{
		delete[]cheltuiala.nume_utilitate;
	}
	cheltuiala.nume_utilitate = new char[strlen(buffer) + 1];
	strcpy(cheltuiala.nume_utilitate, buffer);
	in >> cheltuiala.cantitate_consumata;
	return in;
}
//afisare intr-un fisier binar
ofstream& operator<<(ofstream& out, CheltuialaUtilitati cheltuiala)
{
	out << (Cheltuiala)cheltuiala;
	out << ", nume utilitate: " << cheltuiala.nume_utilitate;
	out << " cantitatea consumata  " << cheltuiala.cantitate_consumata;
	return out;
}
ostream& operator<<(ostream& out, CheltuialaUtilitati cheltuiala)
{
	out << (Cheltuiala)cheltuiala;
	out << ", nume utilitate: " << cheltuiala.nume_utilitate;
	out << " cantitatea consumata  " << cheltuiala.cantitate_consumata;
	return out;
}
istream& operator>>(istream& in, CheltuialaUtilitati& cheltuiala)
{
	in >> (Cheltuiala&)cheltuiala;
	cout << endl;
	cout << "nume bancnota= ";
	char buffer[1000];
	in.ignore(numeric_limits<streamsize>::max(), '\n');
	in.getline(buffer, 1000);
	if (cheltuiala.nume_utilitate != nullptr)
	{
		delete[]cheltuiala.nume_utilitate;
	}
	cheltuiala.nume_utilitate = new char[strlen(buffer) + 1];
	strcpy(cheltuiala.nume_utilitate, buffer);
	cout << "cititi cantitatea consumata";
	in >> cheltuiala.cantitate_consumata;
	return in;
}
class CheltuialaAnimale :public Cheltuiala {
private:
	char* nume_animal = nullptr;
	int nr_pungi_mancare;
public:
	void cheltuiala() {
		cout << "Eu platesc o suma de bani pentru cheltuielile cu animalele care sunt tot o cheltuiala";
	}
	CheltuialaAnimale() :Cheltuiala()
	{
		this->nume_animal = new char[strlen("pisica") + 1];
		strcpy(this->nume_animal, "pisica");
		this->nr_pungi_mancare = 5;
	}
	CheltuialaAnimale(const char* bancnota, int suma_platita_lunara[50], int nr_luni_cheltuieli, const char* nume_animal, int nr_pungi_mancare)
		:Cheltuiala(bancnota, suma_platita_lunara, nr_luni_cheltuieli)
	{
		this->nume_animal = new char[strlen(nume_animal) + 1];
		strcpy(this->nume_animal, nume_animal);
		this->nr_pungi_mancare = nr_pungi_mancare;
	}
	CheltuialaAnimale(const CheltuialaAnimale& copie)
		: Cheltuiala(copie)
	{
		cout << endl;
		this->nume_animal = new char[strlen(copie.nume_animal) + 1];
		strcpy(this->nume_animal, copie.nume_animal);
		this->nr_pungi_mancare = copie.nr_pungi_mancare;

	}
	~CheltuialaAnimale()
	{
		if (this->nume_animal != nullptr) {
			delete[]nume_animal;
		}
	}
	CheltuialaAnimale& operator=(const CheltuialaAnimale& animale)
	{
		cout << endl;
		Cheltuiala::operator=(animale);
		this->nume_animal = new char[strlen(animale.nume_animal) + 1];
		strcpy(this->nume_animal, animale.nume_animal);
		this->nr_pungi_mancare = animale.nr_pungi_mancare;
		return *this;
	}
	char* getNumeAnimal()
	{
		return this->nume_animal;
	}
	int getNrPungiMancare() {
		return this->nr_pungi_mancare;
	}
	void setNumeAnimal(const char* NumeNou) {
		this->nume_animal = new char[strlen(NumeNou) + 1];
		strcpy(this->nume_animal, NumeNou);
	}
	void setNrPungiMancare(int nrpungiNoua) {
		this->nr_pungi_mancare = nrpungiNoua;
	}
	friend ostream& operator<<(ostream&, CheltuialaAnimale);
	friend istream& operator>>(istream&, CheltuialaAnimale&);
	friend ofstream& operator<<(ofstream&, CheltuialaAnimale);
	friend ifstream& operator>>(ifstream&, CheltuialaAnimale&);
	char operator[](int index)
	{
		if (index >= 0 && index < strlen(this->nume_animal)) {
			return this->nume_animal[index];
		}
		else {
			cout << endl
				<< "Index out of range" << endl;
			return '-';
		}
	}
	int operator+(int nr_pungi_consumate)
	{
		return this->nr_pungi_mancare + nr_pungi_consumate;
	}
	CheltuialaAnimale& operator+=(int pungi_aditionale)
	{
		this->nr_pungi_mancare += pungi_aditionale;
		return *this;
	}

	// preincrementare
	CheltuialaAnimale& operator++()
	{
		this->nr_pungi_mancare += 2;
		return *this;
	}

	// postincrementare
	CheltuialaAnimale operator++(int)
	{
		CheltuialaAnimale copie = *this;
		this->nr_pungi_mancare += 2;
		return copie;
	}
	operator double()
	{
		return this->nr_pungi_mancare;
	}
	bool operator!() {
		if (this->nume_animal != nullptr) {
			return true;
		}
		else {
			return false;
		}
	}
	//operatorul < 
	bool operator<(CheltuialaAnimale ca)
	{
		if (this->nr_pungi_mancare < ca.nr_pungi_mancare)
			return true;
		else return false;
	}
	//operatorul =
	bool operator==(CheltuialaAnimale& cheltuiala)
	{
		if (this->nume_animal == cheltuiala.nume_animal)
			return 1;
		else return 0;
	}
};
ifstream& operator>>(ifstream& in, CheltuialaAnimale& animal)
{
	in >> (Cheltuiala&)animal;
	cout << endl;
	char buffer[1000];
	in >> ws;
	in.ignore(numeric_limits<streamsize>::max(), '\n');
	in.getline(buffer, 1000);
	if (animal.nume_animal != nullptr)
	{
		delete[]animal.nume_animal;
	}
    animal.nume_animal = new char[strlen(buffer) + 1];
	strcpy(animal.nume_animal, buffer);
	in >> animal.nr_pungi_mancare;
	return in;
}
//afisare intr-un fisier binar
ofstream& operator<<(ofstream& out, CheltuialaAnimale animal)
{
	out << (Cheltuiala)animal;
	out << ", nume utilitate: " << animal.nume_animal;
	out << " cantitatea consumata  " << animal.nr_pungi_mancare;
	return out;
}
ostream& operator<<(ostream& out, CheltuialaAnimale cheltuiala)
{
	out << (Cheltuiala)cheltuiala;
	out << ", nume animal: " << cheltuiala.nume_animal;
	out << " nr_pungi_consumate  " << cheltuiala.nr_pungi_mancare;
	return out;
}
istream& operator>>(istream& in, CheltuialaAnimale& cheltuiala)
{
	in >> (Cheltuiala&)cheltuiala;
	cout << endl;
	cout << "animal=  ";
	char buffer[1000];
	in.ignore(numeric_limits<streamsize>::max(), '\n');
	in.getline(buffer, 1000);
	if (cheltuiala.nume_animal != nullptr)
	{
		delete[]cheltuiala.nume_animal;
	}
	cheltuiala.nume_animal = new char[strlen(buffer) + 1];
	strcpy(cheltuiala.nume_animal, buffer);
	cout << "cititi nr de pungi consumate";
	in >> cheltuiala.nr_pungi_mancare;
	return in;
}
class CheltuialaProduse :public Cheltuiala {
private:
	char* nume_produs = nullptr;
	int numar_produse;
public:
	void cheltuiala() {
		cout << "Eu platesc o suma de bani pentru cheltuielile cu produsele care sunt tot o cheltuiala";
	}
	CheltuialaProduse() :Cheltuiala()
	{
		this->nume_produs = new char[strlen("lapte") + 1];
		strcpy(this->nume_produs, "lapte");
		this->numar_produse = 5;
	}
	CheltuialaProduse(const char* bancnota, int suma_platita_lunara[50], int nr_luni_cheltuieli, const char* nume_produs, int numar_produse)
		:Cheltuiala(bancnota, suma_platita_lunara, nr_luni_cheltuieli)
	{
		this->nume_produs = new char[strlen(nume_produs) + 1];
		strcpy(this->nume_produs, nume_produs);
		this->numar_produse = numar_produse;
	}
	CheltuialaProduse(const CheltuialaProduse& copie)
		: Cheltuiala(copie)
	{
		cout << endl;
		this->nume_produs = new char[strlen(copie.nume_produs) + 1];
		strcpy(this->nume_produs, copie.nume_produs);
		this->numar_produse = copie.numar_produse;

	}
	~CheltuialaProduse()
	{
		if (this->nume_produs != nullptr) {
			delete[]nume_produs;
		}
	}
	CheltuialaProduse& operator=(const CheltuialaProduse& produs)
	{
		cout << endl;
		Cheltuiala::operator=(produs);
		this->nume_produs = new char[strlen(produs.nume_produs) + 1];
		strcpy(this->nume_produs, produs.nume_produs);
		this->numar_produse = produs.numar_produse;
		return *this;
	}
	char* getNumeProdus()
	{
		return this->nume_produs;
	}
	int getNrProduse() {
		return this->numar_produse;
	}
	void setNumeProdus(const char* NumeNou) {
		this->nume_produs = new char[strlen(NumeNou) + 1];
		strcpy(this->nume_produs, NumeNou);
	}
	void setNrProduse(int nrproduseNoua) {
		this->numar_produse = nrproduseNoua;
	}
	friend ostream& operator<<(ostream&, CheltuialaProduse);
	friend istream& operator>>(istream&, CheltuialaProduse&);
	friend ofstream& operator<<(ofstream&, CheltuialaProduse);
	friend ifstream& operator>>(ifstream&, CheltuialaProduse&);
	char operator[](int index)
	{
		if (index >= 0 && index < strlen(this->nume_produs)) {
			return this->nume_produs[index];
		}
		else {
			cout << endl
				<< "Index out of range" << endl;
			return '-';
		}
	}
	int operator+(int numar_produse)
	{
		return this->numar_produse + numar_produse;
	}
	CheltuialaProduse& operator+=(int nr_produse_aditionale)
	{
		this->numar_produse += numar_produse;
		return *this;
	}

	// preincrementare
	CheltuialaProduse& operator++()
	{
		this->numar_produse += 2;
		return *this;
	}

	// postincrementare
	CheltuialaProduse operator++(int)
	{
		CheltuialaProduse copie = *this;
		this->numar_produse += 2;
		return copie;
	}
	operator double()
	{
		return this->numar_produse;
	}
	bool operator!() {
		if (this->nume_produs != nullptr) {
			return true;
		}
		else {
			return false;
		}
	}
	//operatorul < 
	bool operator<(CheltuialaProduse cp)
	{
		if (this->numar_produse < cp.numar_produse)
			return true;
		else return false;
	}
	//operatorul =
	bool operator==(CheltuialaProduse& cheltuiala)
	{
		if (this->nume_produs == cheltuiala.nume_produs)
			return 1;
		else return 0;
	}
};
//citire din fisier text
ifstream& operator>>(ifstream& in, CheltuialaProduse& cheltuiala)
{
	in >> (Cheltuiala&)cheltuiala;
	cout << endl;
	char buffer[1000];
	in >> ws;
	in.ignore(numeric_limits<streamsize>::max(), '\n');
	in.getline(buffer, 1000);
	if (cheltuiala.nume_produs != nullptr)
	{
		delete[]cheltuiala.nume_produs;
	}
	cheltuiala.nume_produs = new char[strlen(buffer) + 1];
	strcpy(cheltuiala.nume_produs, buffer);
	in >> cheltuiala.numar_produse;
	return in;
}
//afisare intr-un fisier binar
ofstream& operator<<(ofstream& out, CheltuialaProduse cheltuiala)
{
	out << (Cheltuiala)cheltuiala;
	out << ", nume utilitate: " << cheltuiala.nume_produs;
	out << " cantitatea consumata  " << cheltuiala.numar_produse;
	return out;
}
ostream& operator<<(ostream& out, CheltuialaProduse cheltuiala)
{
	out << (Cheltuiala)cheltuiala;
	out << ", nume produs: " << cheltuiala.nume_produs;
	out << " numar produse " << cheltuiala.numar_produse;
	return out;
}
istream& operator>>(istream& in, CheltuialaProduse& cheltuiala)
{
	in >> (Cheltuiala&)cheltuiala;
	cout << endl;
	cout << "produs =  ";
	char buffer[1000];
	in.ignore(numeric_limits<streamsize>::max(), '\n');
	in.getline(buffer, 1000);
	if (cheltuiala.nume_produs != nullptr)
	{
		delete[]cheltuiala.nume_produs;
	}
	cheltuiala.nume_produs = new char[strlen(buffer) + 1];
	strcpy(cheltuiala.nume_produs, buffer);
	cout << "cititi nr de produse";
	in >> cheltuiala.numar_produse;
	return in;
}
//metode virtuale pure+ clasa abstracta 
//class TVA {
//	virtual float tva() = 0;
//};
//class Impozit {
//public:
//	virtual float Impozitare() = 0;
//};
class CheltuieliTotale/*: public Impozit, public TVA*/
{
	int nr_animale;
	int nr_utilitati;
	int nr_produse;
	CheltuialaAnimale* ca = nullptr;
	CheltuialaUtilitati* cu = nullptr;
	CheltuialaProduse* cp = nullptr;
public:
	CheltuieliTotale()
	{

	}
	CheltuieliTotale(int nr_animale, int nr_utilitati, int nr_produse,CheltuialaAnimale* ca, CheltuialaUtilitati* cu, CheltuialaProduse* cp)
	{
		this->ca = new CheltuialaAnimale[nr_animale];
		for (int i = 0; i < nr_animale; i++)
			this->ca[i] = ca[i];
		this->cu = new CheltuialaUtilitati[nr_utilitati];
		for (int i = 0; i < nr_utilitati; i++)
			this->cu[i] = cu[i];
		this->cp = new CheltuialaProduse[nr_produse];
		for (int i = 0; i < nr_produse; i++)
			this->cp[i] = cp[i];
	}
	friend ostream operator <<(ostream& out , CheltuieliTotale tot);

};
ostream operator <<(ostream& out, CheltuieliTotale tot) {

	out << "numarul de animale " << " " << tot.nr_animale;
	out << "numarul de utilitati" << " " << tot.nr_utilitati;
	out << "  numarul de produse" << " " << tot.nr_produse;
	if (tot.nr_animale > 0) {
		for (int i = 0; i < tot.nr_animale; i++)
			out << tot.ca[i];
	}
	if (tot.nr_utilitati > 0) {
		for (int i = 0; i < tot.nr_utilitati; i++)
			out << tot.cu[i];
	}
	if (tot.nr_produse > 0) {
		for (int i = 0; i < tot.nr_produse; i++)
			out << tot.cp[i];
	}
}
int Persoana::nr_persoane = 0;
int main(int argc, char* argv[])
{
	cout << "constructor fara parametrii   +supraincarcare operator <<   ";
	Persoana p1 = Persoana();
	cout << p1;
	int chirie_lunara[4] = { 900, 901, 903, 905 };
	cout << endl;
	cout << "constructor cu parametrii";
	Persoana p2 = Persoana("Marius", chirie_lunara, 4, 2);
	cout << p2;
	cout << endl;
	Persoana p3;
	cout << "supraincarcare operator =";
	p3 = p2;
	cout << endl;
	cout << "p3: " << p3;
	cout << endl;
	Persoana p4;
	cout << "supraincarcare operator >>";
	cout << endl;
	/*cin >> p4;
	cout << "p4" << p4 << endl;*/
	cout << "getter nr_luni " << p2.getnumar_luni() << endl;
	cout << "getter nume  " << p2.get_nume();
	p2.setNume("Andrei");
	p2.setNumar_Luni(3);
	cout << endl;
	cout << " afisare setter";
	cout << p2;
	cout << endl;
	cout << "operatorul de indexare p4[2]:     " << p4[2] << endl;
	cout << "operatorul +: " << p3 + (int)2 << endl;
	p3 += (int)2;
	p3 += 2;
	cout << "operator ++: " << p3.operator++(1) << endl;
	cout << " operator ! " << p2.operator!() << endl;
	cout << " operator < " << p2.operator<(p3) << endl;
	cout << " operator == ";
	if (p3 == p2)cout << "persoanele sunt egale" << endl;
	else cout << "persoanele nu sunt egale" << endl;
	cout << endl;
	//executare si afisare in consola pentru fisiere text
	ifstream fisierIn;
	fisierIn.open("Persoana.txt", ifstream::in);
	Persoana p5;
	fisierIn >> p5;
	cout << p5;
	fisierIn.close();
	cout << endl;
	//executare,citire din fisier si afisare in cmd pentru fisiere text
	if (argc>1)
	{
		ifstream fisierIn;
		fisierIn.open(argv[1], ifstream::in);
		Persoana p5;
		fisierIn >> p5;
		cout << p5;
		fisierIn.close();
		cout << endl;
	}
	//afisare atribute in fisier binar
	ofstream fisierOut;
	fisierOut.open("Persoana2.bin", ofstream::out, ofstream::binary);
	fisierOut << p3;
	fisierOut.close();

	int cheltuiala_lunara[4] = { 200, 201, 203, 205 };
	cout << "constructor cu parametrii persoana  +supraincarcare operator <<   ";
	Cheltuiala c1 = Cheltuiala();
	cout << c1;
	cout << endl;
	cout << "constructor cu parametrii";
	Cheltuiala c2 = Cheltuiala("euro", cheltuiala_lunara, 4);
	cout << c2 << endl;
	cout << "supraincarcare operator =";
	Cheltuiala c3;
	c3 = c2;
	cout << c3 << endl;
	cout << "supraincarcare operator >>";
	Cheltuiala c4;
	/*cin >> c4;*/
	/*cout << c4;*/
	cout << endl;
	cout << "getter bancnota  " << c2.get_bancnota() << endl;
	cout << "getter numar luni " << c2.getnr_luni_cheltuieli();
	c2.setBancnota("Lei");
	c2.setNumar_Luni(3);
	cout << endl;
	cout << " afisare setter";
	cout << c2;
	cout << endl;
	cout << "operatorul de indexare c2[2]:   " << c2[2] << endl;
	cout << "operatorul +: " << c2 + (int)2 << endl;
	c2 += (int)2;
	c2 += 2;
	cout << "operator ++: " << c2.operator++(1) << endl;
	cout << " operator ! " << c2.operator!() << endl;
	cout << " operator < " << c2.operator<(c3) << endl;
	cout << " operator == ";
	if (c3 == c2)cout << "cheltuielile sunt egale" << endl;
	else cout << "cheltuielile nu sunt egale" << endl;
	cout << endl;
	//executare si afisare in consola pentru fisiere text
	fisierIn.open("cheltuiala.txt", ifstream::in);
	Cheltuiala c5;
	fisierIn >> c5;
	cout << c5;
	fisierIn.close();
	cout << endl;
	//executare,citire din fisier si afisare in cmd pentru fisiere text
	if (argc > 1)
	{
		fisierIn.open(argv[2], ifstream::in);
		Cheltuiala c5;
		fisierIn >> c5;
		cout << c5;
		fisierIn.close();
		cout << endl;
	}
	//afisare atribute in fisier binar
	fisierOut.open("Cheltuiala2.bin", ofstream::out, ofstream::binary);
	fisierOut << c3;
	fisierOut.close();

	cout << "constructor fara parametrii   +supraincarcare operator <<   ";
	CheltuialaUtilitati cu1 = CheltuialaUtilitati();
	cout << cu1;
	cout << endl;
	cout << "constructor cu parametrii";
	CheltuialaUtilitati cu2 = CheltuialaUtilitati("euro", cheltuiala_lunara, 4, "energie", 200);
	cout << cu2 << endl;
	cout << "supraincarcare operator =";
	CheltuialaUtilitati cu3;
	cu3 = cu2;
	cout << cu3 << endl;
	cout << "supraincarcare operator >>";
	CheltuialaUtilitati cu4;
	/*cin >> cu4;*/
	/*cout << cu4;*/
	cout << endl;
	cout << "getter nume utilitate  " << cu2.getNumeUtilitate() << endl;
	cout << "getter numar luni " << cu2.getCantitateConsumata();
	cu2.setNumeUtilitate("Apa");
	cu2.setCantitateConsumata(250);
	cout << endl;
	cout << " afisare setter";
	cout << cu2;
	cout << endl;
	cout << "operatorul de indexare cu2[2]:   " << cu2[2] << endl;
	cout << "operatorul +: " << cu2 + (int)2;
	cu2 += (int)20;
	cu2 += 20;
	cout << "operator ++: " << cu2.operator++(1) << endl;
	cout << endl;
	cout << " operator ! " << cu2.operator!() << endl;
	cout << " operator < " << cu2.operator<(cu3) << endl;
	cout << " operator == ";
	if (cu3 == cu2)cout << "cheltuielile cu utilitatile sunt egale" << endl;
	else cout << "cheltuielile cu utilitatile nu sunt egale" << endl;
	cout << endl;
	//executare si afisare in consola pentru fisiere text
	fisierIn.open("cheltuialaut.txt", ifstream::in);
	CheltuialaUtilitati cu5;
	fisierIn >> cu5;
	cout << cu5;
	fisierIn.close();
	cout << endl;
	//executare,citire din fisier si afisare in cmd pentru fisiere text
	if (argc > 1)
	{
		fisierIn.open(argv[3], ifstream::in);
		CheltuialaUtilitati cu5;
		fisierIn >> cu5;
		cout << cu5;
		fisierIn.close();
		cout << endl;
	}
	//afisare atribute in fisier binar
	fisierOut.open("Cheltuialaut2.bin", ofstream::out, ofstream::binary);
	fisierOut << cu3;
	fisierOut.close();
	cout << "constructor fara parametrii   +supraincarcare operator <<   ";
	CheltuialaAnimale ca1 = CheltuialaAnimale();
	cout << ca1;
	cout << endl;
	cout << "constructor cu parametrii";
	CheltuialaAnimale ca2 = CheltuialaAnimale("euro", cheltuiala_lunara, 4, "caine", 10);
	cout << ca2 << endl;
	cout << "supraincarcare operator =";
	CheltuialaAnimale ca3;
	ca3 = ca2;
	cout << ca3 << endl;
	cout << "supraincarcare operator >>";
	CheltuialaAnimale ca4;
	/*cin >> ca4;*/
	/*cout << ca4;*/
	cout << endl;
	cout << "getter nume animal  " << ca2.getNumeAnimal() << endl;
	cout << "getter numar pungi consumate " << ca2.getNrPungiMancare();
	ca2.setNumeAnimal("Motan");
	ca2.setNrPungiMancare(2);
	cout << endl;
	cout << " afisare setter";
	cout << ca2;
	cout << endl;
	cout << "operatorul de indexare ca2[2]:   " << ca2[2] << endl;
	cout << "operatorul +: " << ca2 + (int)2;
	ca2 += (int)2;
	ca2 += 2;
	cout << "operator ++: " << ca2.operator++(1) << endl;
	cout << endl;
	cout << " operator ! " << ca2.operator!() << endl;
	cout << " operator < " << ca2.operator<(ca3) << endl;
	cout << " operator == ";
	if (ca3 == ca2)cout << "cheltuielile cu animalele sunt egale" << endl;
	else cout << "cheltuielile cu animalele nu sunt egale" << endl;
	cout << endl;
	//executare si afisare in consola pentru fisiere text
	fisierIn.open("cheltuialaan.txt", ifstream::in);
	CheltuialaAnimale ca5;
	fisierIn >> ca5;
	cout << ca5;
	fisierIn.close();
	cout << endl;
	//executare,citire din fisier si afisare in cmd pentru fisiere text
	if (argc > 1)
	{
		fisierIn.open(argv[4], ifstream::in);
		CheltuialaAnimale ca5;
		fisierIn >> ca5;
		cout << ca5;
		fisierIn.close();
		cout << endl;
	}
	//afisare atribute in fisier binar
	fisierOut.open("Cheltuialaan2.bin", ofstream::out,ofstream::binary);
	fisierOut << ca3;
	fisierOut.close();

	cout << "constructor fara parametrii   +supraincarcare operator <<   ";
	CheltuialaProduse cp1 = CheltuialaProduse();
	cout << cp1;
	cout << endl;
	cout << "constructor cu parametrii";
	CheltuialaProduse cp2 = CheltuialaProduse("euro", cheltuiala_lunara, 4, "lapte", 2);
	cout << cp2 << endl;
	cout << "supraincarcare operator =";
	CheltuialaProduse cp3;
	cp3 = cp2;
	cout << cp3 << endl;
	cout << "supraincarcare operator >>";
	CheltuialaProduse cp4;
	/*cin >> cp4;*/
	/*cout << cp4;*/
	cout << endl;
	cout << "getter nume produs  " << cp2.getNumeProdus() << endl;
	cout << "getter numar produse cumparate " << cp2.getNrProduse();
	cp2.setNumeProdus("Cereale");
	cp2.setNrProduse(3);
	cout << endl;
	cout << " afisare setter";
	cout << cp2;
	cout << endl;
	cout << "operatorul de indexare cp2[2]:   " << cp2[2] << endl;
	cout << "operatorul +: " << cp2 + (int)2;
	cp2 += (int)2;
	cp2 += 2;
	cout << "operator ++: " << cp2.operator++(1) << endl;
	cout << endl;
	cout << " operator ! " << cp2.operator!() << endl;
	cout << " operator < " << cp2.operator<(cp3) << endl;
	cout << " operator == ";
	if (cp3 == cp2)cout << "cheltuielile cu produsele sunt egale" << endl;
	else cout << "cheltuielile cu produsele nu sunt egale" << endl;
	cout << endl;
	//executare si afisare in consola pentru fisiere text
	fisierIn.open("cheltuialapr.txt", ifstream::in);
	CheltuialaProduse cp5;
	fisierIn >> cp5;
	cout << cp5;
	fisierIn.close();
	cout << endl;
	//executare,citire din fisier si afisare in cmd pentru fisiere text
	if (argc > 1)
	{
		fisierIn.open(argv[5], ifstream::in);
		CheltuialaAnimale cp5;
		fisierIn >> cp5;
		cout << cp5;
		fisierIn.close();
		cout << endl;
	}
	//afisare atribute in fisier binar
	fisierOut.open("Cheltuialapr2.bin", ofstream::out, ofstream::binary);
	fisierOut << cp3;
	fisierOut.close();
	//metoda virtuala cheltuiala 
	Cheltuiala* cheltuieliCheltuiala[4];
	cheltuieliCheltuiala[0]= new Cheltuiala();
	cheltuieliCheltuiala[1] = new CheltuialaUtilitati();
	cheltuieliCheltuiala[2] = new CheltuialaAnimale();
	cheltuieliCheltuiala[3] = new CheltuialaProduse();
	for (int i = 0; i < 4; i++)
	{
		cheltuieliCheltuiala[i]->cheltuiala();
		cout << endl;
	}
	cout << endl;
	//metoda virtuala persoana
	p4.persoana();

	CheltuialaAnimale ca[] = { ca2,ca1 };
	CheltuialaUtilitati cu[] = { cu2,cu1 };
	CheltuialaProduse cp[] = { cp2,cp1 };
	CheltuieliTotale tot = CheltuieliTotale(1,1,1,ca,cu,cp);
	//tentativa de citit din fisiere csv
	/*fisierIn.open("persoana.csv", ifstream::in);
	Persoana p6;
	fisierIn >> p6;
	cout << p6;
	fisierIn.close();
	cout << endl;*/
}