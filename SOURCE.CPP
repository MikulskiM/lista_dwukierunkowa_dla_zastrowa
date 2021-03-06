﻿#include <string>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>

using namespace std;

struct rekord               //tworzenie rekordu
{

	string key;
	rekord* next;
	rekord* prev;

	rekord();
};

rekord::rekord()
{
	next = 0;
	prev = 0;
}

struct list
{
	rekord* head;
	rekord* tail;

	list();
	void display();
	void displayBack();
	void list_insert_front();
	void list_insert_back();
	void list_insert_in();
	void list_insert(string data);
	void list_delete_last();			// usuwanie ostatniego rekordu
	void list_delete_first();			// usuwanie pierwszego rekordu
	void list_delete_in();		// usuwanie wskazanego rekordu
	void load();				// wczytanie listy z pliku .txt
	void save();
	int ile();

};

list::list()
{

	head = 0;
	tail = 0;
}

void list::list_insert_front()
{

	rekord* nowy = new rekord;

	cout << "Prosze wpisac dane: ";
	cin >> nowy->key;

	if (head == 0)
	{
		//string input;
		//getline(cin, input, '|');
		head = nowy;                                                                    // = wkazuje a nie STAJE SIE
		tail = nowy;
	}
	else
	{
		head->next = nowy;                                                              //head jest wskaznikiem listy na element
		nowy->prev = head;
		nowy->next = 0;
		head = nowy;
	}
}
void list::list_insert_back()
{
	rekord* nowy = new rekord;

	cout << "Prosze wpisac dane: ";
	cin >> nowy->key;

	if (head == 0)
	{
		//string input;
		//getline(cin, input, '|');
		head = nowy;                                                                    // = wkazuje a nie STAJE SIE
		tail = nowy;
	}
	else

	{
		tail->prev = nowy;                                                              //head jest wskaznikiem listy na element
		nowy->next = tail;
		nowy->prev = 0;
		tail = nowy;
	}
}

void list::list_insert_in()
{

	if (head == 0)
	{
		rekord* nowy = new rekord;

		cout << "Prosze wpisac dane: ";
		cin >> nowy->key;																				//string input;
																						//getline(cin, input, '|');
		head = nowy;                                                                    // = wkazuje a nie STAJE SIE
		tail = nowy;
	}
	else
	{
		int wybor;
		cout << "Na ktorej pozycji chcesz wstawic element? ";
		cin >> wybor;
		if (wybor == 0)
		{
			list_insert_back();
		}
		else if (wybor > 0)
		{
			if (wybor >= ile()) {
				list_insert_front();
			}
			else {
				rekord* nowy = new rekord;

				cout << "Prosze wpisac dane: ";
				cin >> nowy->key;

				nowy->next = tail;

				for (int i = 0; i < ile(); i++)
				{
					nowy->next = nowy->next->next;

				}

				nowy->prev = nowy->next->prev;
				nowy->prev->next = nowy;
				nowy->next->prev = nowy->prev;
			}
		}
		else
		{
			cout << "Musisz wybrać miejsce na liscie (0 - " << ile() << ")";
		}

	}
}

void list::list_insert(string data)
{                                                      //tworzenie nowego elementu listy dla konkretnego podanego wczesniej keya

	rekord* nowy = new rekord;

	nowy->key = data;

	if (head == 0)
	{
		head = nowy;
		tail = nowy;
	}
	else
	{
		head->next = nowy;
		nowy->prev = head;
		nowy->next = 0;
		head = nowy;
	}
}

void list::display()
{
	if (head == 0)
		cout << "\nERROR: Lista jest pusta. \nNie mam nic do wyswietlwnia\n";
	else
	{
		rekord* temp = tail;
		while (temp)
		{
			cout << temp->key << endl;

			temp = temp->next;
		}
	}
}

void list::displayBack()
{
	if (head == 0)
		cout << "\nERROR: Lista jest pusta. \nNie ma nic do wyswietlenia?\n";
	else
	{
		rekord* temp = head;
		while (temp)
		{
			cout << temp->key << endl;

			temp = temp->prev;
		}
	}
}

void list::load()
{
	tail = 0;
	head = 0;

	fstream plik;							// tworzymy obiekt do operowania na plikach

	plik.open("dane_listy.txt", ios::in);                       // plik sam siê tworzy przy zapisie, tylko do odczytu dla progemu
	if (plik.good() == true)
	{
		cout << "\n\n loaded saved list :) \n\n";
		string line;

		while (getline(plik, line)) {
			list_insert(line);
		}

	}
	else {
		cout << "\nFailed to open dane_listy.txt file \n";               //wyœwietli sie kiedy plik tekstowy nie istnieje
	}

	plik.close();

}

void list::save() {												       	// ZAPIS

	fstream plik;

	plik.open("dane_listy.txt", ios::out);

	if (head == 0)
		cout << "\n Lista jest pusta. \n";
	else {
		rekord* temp = tail;
		while (temp)
		{
			plik << temp->key << endl;

			temp = temp->next;
		}
	}
	plik.close();

}

int list::ile()
{
	rekord* temp = tail;
	int licznik = 0;
	for (temp = tail; temp; temp = temp->next) {
		licznik++;
	}
	/*while (temp)
	{
		temp = tail->next;
		licznik++;
	}*/
	return licznik;
}

void list::list_delete_last() {								// usuwanie ostatniego rekordu
	if (head == 0)
		cout << "\n\n\t\t Lista jest pusta.\n\n";
	else {
		head->prev->next = 0;
		head = head->prev;
	}
}

void list::list_delete_first() {								// usuwanie pierwszego rekordu
	if (tail == 0)
		cout << "\n\n\t\t Lista jest pusta.\n\n";
	else {
		tail->next->prev = 0;
		tail = tail->next;
	}
}

void list::list_delete_in() {							// usuwanie wybranego rekordu
	int numer;
	cout << "\n\n Podaj numer elementu ktory chcesz usunac (liczymy 0, 1, 2...): ";
	cin >> numer;

	if (numer <= 0) {
		cout << "\nnumer<0\n";
		tail = tail->next;
		tail->prev = 0;
	}
	else if (numer > 0 && numer < ile()) {
		cout << "\n numer > 0 && numer < ile()\n";
		rekord* temp = tail;
		int licznik = 0;
		do {
			temp = temp->next;
			licznik++;
		} while (licznik != numer);
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		delete temp;
	}
	else {
		cout << "\npodales numer wiekszy lub rowny \n";
		head = head->prev;
		head->next = 0;
	}

	/*while (numer<=0 || numer>ile())
		{
		cout << "\nChyba czegos nie rozumiesz... Musisz podac liczbe z zakresu 0 - " << ile() << "\t sprobujmy jeszcze raz: ";
		cin >> numer;
		}

	rekord* temp = new rekord;
	temp = tail;

	cout << "\n\nTu bedzie sie dzialo usuwanie, ale jeszcze go nie ma\n\n";
*/
}

int main()
{
	list my_list;

	int wybor;
	do {
		system("cls");
		cout << "   ---------------------------------------------   " << endl;
		cout << "   ----=======>> - Zadanie domowe - <<=======---  " << endl;
		cout << "   ---------------------------------------------   " << endl;
		cout << "   1. Dodaj element na poczatku listy.  " << endl;
		cout << "   2. Dodaj element na koncu listy.  " << endl;
		cout << "   3. Dodaj element w wybranym miejscu listy. " << endl;
		cout << "   4. Usun element z poczatku listy.  " << endl;
		cout << "   5. Usun element z konca listy.  " << endl;
		cout << "   6. Usun element z wybranego miejsca listy. " << endl;
		cout << "   7. Zapisz liste.  " << endl;
		cout << "   8. Wczytaj zapisana liste.  " << endl;
		cout << "   9. Wyswietl liste.  " << endl;
		//cout << "   9. Wyświetl liste od konca.  " << endl;
		cout << "   0. Wyjscie  " << endl;
		cout << "   ---------------------------------------------   " << endl;
		cout << "   ----==== - Made by Agata Buksinska - ====----   " << endl;
		cout << "\n   Wybierz numer polecenia :";

		wybor = _getch();                                                     //jak cin ale bez potwierdzenia,
																			  //cyferki maj¹ odpowiedzni kod z tablicy ASCII

		if (wybor == 49)    //1
		{
			system("cls");
			my_list.list_insert_back();
		}
		else if (wybor == 50)   //2
		{
			system("cls");
			my_list.list_insert_front();
		}
		else if (wybor == 51)    //3
		{
			system("cls");
			my_list.list_insert_in();

		}
		else if (wybor == 52)   //4
		{
			my_list.list_delete_first();
			cout << "\n\n\t\t Usunieto pierwszy element :)\n\n";
			system("pause");
		}
		else if (wybor == 53)   //5
		{
			my_list.list_delete_last();
			cout << "\n\n\t\t Usunieto ostatni element :)\n\n";
			system("pause");
		}
		else if (wybor == 54)   //6
		{
			my_list.list_delete_in();
			cout << "\n\n\t\t Usunieto wybrany element :)\n\n";
			system("pause");
		}
		else if (wybor == 55)   //7
		{
			cout << "\n\n Twoja lista zosta³a zapisana jako dane_listy.txt \n\n";
			my_list.save();
			system("pause");
		}
		else if (wybor == 56)   //8
		{
			cout << "\n\n Twoja lista zostala pomyslnie wczytana z dane_listy.txt \n\n";
			my_list.load();
			system("pause");
		}
		else if (wybor == 57)   //9
		{
			system("cls");
			my_list.display();
			system("pause");

			/*system("cls");
			my_list.displayBack();
			system("pause");*/

		}
		else if (wybor == 105)  //i
		{
			cout << "\n\n Lista ma " << my_list.ile() << " elementow.";
			system("pause");
		}
	} while (wybor != 48); //0

	cout << endl << "Thanks, I hope you enjoyed :)" << endl << endl;

	system("pause");
	return 0;
}
