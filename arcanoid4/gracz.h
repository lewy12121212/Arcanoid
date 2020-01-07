#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;


class pasek_zycia {
private:
	RectangleShape ksztalt;
	Texture tekstura_zycie;
	vector<RectangleShape> pasek;
	Vector2f pozycja;
	int zycie;
	int rozmiar;
	int i;
	float szerokosc_obiekt;
	float wysokosc_obiekt;
	int rozdzielczosc_x;
	int rozdzielczosc_y;
	//float szerokosc_obiekt;
public:

	pasek_zycia(float szerokosc_obiekt, float wysokosc_obiekt, int rozdzielczosc_x, int rozdzielczosc_y, int zycie) {
		this->zycie = zycie;
		//this->szerokosc_obiekt = szerokosc_obiekt;
		this->szerokosc_obiekt = szerokosc_obiekt;
		this->wysokosc_obiekt = wysokosc_obiekt;
		this->rozdzielczosc_x = rozdzielczosc_x;
		this->rozdzielczosc_y = rozdzielczosc_y;

		
		if (tekstura_zycie.loadFromFile("./grafika/serce.png")) {
			cout << "Tekstura rakietka OK";
		}
		else {
			cout << "Tekstura rakietka ERROR";
		}
		ksztalt.setSize({ wysokosc_obiekt, wysokosc_obiekt });
		ksztalt.setTexture(&tekstura_zycie);
		//pozycja.x = rozdzielczosc_x - szerokosc_obiekt * 2;
		pozycja.y = wysokosc_obiekt / 2;

		for (i = 1; i <= zycie; i++) {
			pozycja.x = rozdzielczosc_x - szerokosc_obiekt * 2 * i;
			ksztalt.setPosition(pozycja);
			pasek.push_back(ksztalt);
		}
		i--;
		rozmiar = pasek.size();
		cout << rozmiar;
	}

	vector<RectangleShape> zycie_zmiejsz() {
		pasek.erase(pasek.end() - 1);
		i--;
		return pasek;
		//this->rozmiar = pasek.size();
	}

	vector<RectangleShape> zycie_zwieksz() {
		pozycja.x = rozdzielczosc_x - szerokosc_obiekt * 2 * i;
		ksztalt.setPosition(pozycja);
		pasek.push_back(ksztalt);
		return pasek;
		//this->rozmiar = pasek.size();
	}

	
	void ustawienie_tekstury() {

		if (tekstura_zycie.loadFromFile("./grafika/serce.png")) {
			cout << "Tekstura rakietka OK";
		}
		else {
			cout << "Tekstura rakietka ERROR";
			system("pause");
		}

		for (int j = 0; j < zycie; j++) {
			pasek[j].setTexture(&tekstura_zycie);
		}
		
	}

	int zmiana_rozmiar() {
		return rozmiar = pasek.size();
	}

	int zwroc_rozmiar() {
	//	cout << "rozmiar" << rozmiar;
		return rozmiar;
	}

	RectangleShape wypisz(int i) {
		return pasek[i];
	}

	/*
	~pasek_zycia() {
		cout << "dekonstruktor pasek zycia ";
	}*/
};

class czcionka {
protected:
	Font styl;
	Text tekst;
	string tresc;
	float x;
	float y;

public:

	czcionka(string tresc, float szerokosc_obiekt, float wysokosc_obiekt, int rozdzielczosc_x, int rozdzielczosc_y, float pozycja_x) {
		this->tresc = tresc;
		this->x = x;
		y = wysokosc_obiekt * 0.3;

		//styl.loadFromFile("grafika/czcionka_1/Roboto-Bold.ttf");
		if (styl.loadFromFile("grafika/czcionka_1/Raleway-LightItalic.ttf")) {
			cout << "Czcionka poprawnie zaladowana";
		}
		else {
			cout << "Cznionka nie zaladowana";
		}

		tekst.setFont(styl);
		tekst.setFillColor(Color::Red);
		tekst.setPosition({ szerokosc_obiekt + pozycja_x, y });
		//tekst.setScale({ 100,100 });
		tekst.setString(tresc);

	}

	void Tresc_zmiana(string tresc) {
		tekst.setString(tresc);
	}

	Text wypisz() {
		return tekst;
	}


	~czcionka() {
		cout << "dekostruktor czcionka ";
	}
};

class gracz {
public:
	string imie;
	pasek_zycia pasek;
	czcionka punkty_wyraz;
	czcionka punkty_liczba;
	int punkty;
	int poziom;
};

struct tabela {
	string nazwa;
	string punkty;
	string poziom;
	int pkt_sort;

	~tabela() {
		cout << "dekonstruktor tabela ";
	}
};