#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class obiekt {

public:
	float szerokosc_obiekt;
	float wysokosc_obiekt;
	int rozdzielczosc_x;
	int rozdzielczosc_y;
	//int pozycja_x, pozycja_y;
	Texture tekstura;
	Vector2f wielkosc;
	Vector2f pozycja;

	~obiekt() {
		cout << "dekonstruktor obiekt ";
	};
};

class obiekt_neutralny : obiekt {
private:
	RectangleShape ksztalt;

public:
	obiekt_neutralny(float szerokosc_obiekt, float wysokosc_obiekt, int rozdzielczosc_x, int rozdzielczosc_y) {

		this->szerokosc_obiekt = szerokosc_obiekt;
		this->wysokosc_obiekt = wysokosc_obiekt;
		this->rozdzielczosc_x = rozdzielczosc_x;
		this->rozdzielczosc_y = rozdzielczosc_y;

		wielkosc.x = szerokosc_obiekt;
		wielkosc.y = wysokosc_obiekt;

		ksztalt.setPosition(pozycja);
		ksztalt.setSize(wielkosc);
		ksztalt.setFillColor(Color::White);

	}

	void ustaw_pozycje(int x, int y) {
		pozycja.x = x;
		pozycja.y = y;
		ksztalt.setPosition(pozycja);
	}

	RectangleShape wypisz() {
		return ksztalt;
	}

	~obiekt_neutralny() {
		cout << "dekonstruktor obiekt naturalny ";
	}
};

class pilka : public obiekt {

private:
	CircleShape ksztalt;
	float predkosc_x;
	float predkosc_y;
	//float wspolczynnik_predkosc;?


public:
	Vector2f predkosc{ predkosc_x , predkosc_y };

	pilka(float szerokosc_obiekt, float wysokosc_obiekt, int rozdzielczosc_x, int rozdzielczosc_y, int Rakieta_x, int Rakieta_y) {
		this->szerokosc_obiekt = szerokosc_obiekt;
		this->wysokosc_obiekt = wysokosc_obiekt;
		this->rozdzielczosc_x = rozdzielczosc_x;
		this->rozdzielczosc_y = rozdzielczosc_y;

		wielkosc.x = szerokosc_obiekt;
		wielkosc.y = szerokosc_obiekt;
		ksztalt.setRadius(wielkosc.x / 2);
		ksztalt.setFillColor(Color(0, 216, 255));
		//	pozycja.x = rozdzielczosc_x / 2;
			//pozycja.y = rozdzielczosc_y / 2;
		pozycja.x = Rakieta_x;
		pozycja.y = Rakieta_y;
		ksztalt.setPosition(pozycja);
		predkosc.x = 0;
		predkosc.y = 0;
	}

	void ruch() {
		if (ksztalt.getPosition().x >= rozdzielczosc_x - 2 * szerokosc_obiekt || ksztalt.getPosition().x <= szerokosc_obiekt)
			predkosc.x = predkosc.x * (-1);

		if (ksztalt.getPosition().y <= wysokosc_obiekt * 2 + 5)
			predkosc.y = predkosc.y * (-1);

		pozycja.x += predkosc.x;
		pozycja.y += predkosc.y;
		ksztalt.setPosition(pozycja);
	}

	void ruch_rakietka(int Rakieta_x, int Rakieta_y) {
		predkosc.x = 0;
		predkosc.y = 0;
		pozycja.x = Rakieta_x;
		pozycja.y = Rakieta_y;
		ksztalt.setPosition(pozycja);
	}

	float kolizja_lewo() {
		return pozycja.x;
	}

	float kolizja_prawo() {
		return pozycja.x + wielkosc.x;
	}

	float kolizja_gora() {
		return pozycja.y;
	}

	float kolizja_dol() {
		return pozycja.y + wielkosc.y;
	}

	float srodek_dol() {
		return pozycja.x + wielkosc.x / 2;
	}

	void zmiana_kolor_przenikanie() {
		ksztalt.setFillColor(Color(255,191,0));
	}

	void zmiana_kolor_normal() {
		ksztalt.setFillColor(Color(0, 216, 255));
	}

	CircleShape wypisz() {
		return ksztalt;
	}

	~pilka() {
		cout << "dekonstruktor pilka";
	};
};

class rakietka : public obiekt {

private:
	float prendkosc_rakietki;
	RectangleShape ksztalt;

public:
	float czesc_rakietki;

	rakietka(float szerokosc_obiekt, float wysokosc_obiekt, int rozdzielczosc_x, int rozdzielczosc_y) {

		this->szerokosc_obiekt = szerokosc_obiekt;
		this->wysokosc_obiekt = wysokosc_obiekt;
		this->rozdzielczosc_x = rozdzielczosc_x;
		this->rozdzielczosc_y = rozdzielczosc_y;

		if (tekstura.loadFromFile("./grafika/rakietka_4.png")) {
			cout << "Tekstura rakietka OK";
		}
		else {
			cout << "Tekstura rakietka ERROR";
		}
		prendkosc_rakietki = 7.5f;

		wielkosc.x = szerokosc_obiekt * 4;
		wielkosc.y = wysokosc_obiekt / 1.5;

		pozycja.x = rozdzielczosc_x / 2 - (szerokosc_obiekt * 2);
		pozycja.y = rozdzielczosc_y - wysokosc_obiekt * 2;

		ksztalt.setTexture(&tekstura);
		ksztalt.setSize(wielkosc);
		ksztalt.setPosition(pozycja);

		czesc_rakietki = wielkosc.x / 7;
	}

	void ruch_lewo() {
		if (Keyboard::isKeyPressed(Keyboard::Key::Left) && pozycja.x > szerokosc_obiekt) {
			pozycja.x -= prendkosc_rakietki;
			ksztalt.setPosition(pozycja);
		}

	}

	void ruch_prawo() {
		if (Keyboard::isKeyPressed(Keyboard::Key::Right) && pozycja.x < szerokosc_obiekt * 50 - wielkosc.x - szerokosc_obiekt) {
			pozycja.x += prendkosc_rakietki;
			ksztalt.setPosition(pozycja);
		}

	}

	void zmiana_predkosc(int ile) {
		prendkosc_rakietki = ile;

	}

	void zmiana_wielkosci() {
		ksztalt.setSize(wielkosc);
		czesc_rakietki = wielkosc.x / 7;
		//ksztalt.setTexture(&tekstura);
	}

	float kolizja_lewo() {
		return pozycja.x;
	}

	float kolizja_prawo() {
		return pozycja.x + wielkosc.x;
	}

	float kolizja_gora() {
		return pozycja.y;
	}

	float kolizja_dol() {
		return pozycja.y + wielkosc.y;
	}


	RectangleShape wypisz() {
		return ksztalt;
	}

	~rakietka() {
		cout << "dekonstruktor rakietka ";
	}
};

class blok : public obiekt {

public:
	bool blok_czy_bonus;
	int zycie;
	int punkty;


	blok() {

	};

	blok(float szerokosc_obiekt, float wysokosc_obiekt, int rozdzielczosc_x, int rozdzielczosc_y, int pozycja_x, int pozycja_y, int poziom) {
		this->szerokosc_obiekt = szerokosc_obiekt;
		this->wysokosc_obiekt = wysokosc_obiekt;
		this->rozdzielczosc_x = rozdzielczosc_x;
		this->rozdzielczosc_y = rozdzielczosc_y;
		this->pozycja.x = pozycja_x;
		this->pozycja.y = pozycja_y;
		
		
		int los_blok_zycie = rand() % 100;
		int proporcja_losowania = 100 - 5 * poziom;
		cout << los_blok_zycie << " :";

		if (los_blok_zycie <= proporcja_losowania) {
			cout << "blok_1" << " ";
			zycie = 1;
			ksztalt.setFillColor(Color::Yellow);
		}
		else {
			int pozostale_punkty = 100 - proporcja_losowania;
			
			if (los_blok_zycie <= (65 * pozostale_punkty / 100) + proporcja_losowania) {
				cout << "blok_2" << " ";
				zycie = 2;
				ksztalt.setFillColor(Color::Blue);
			}
			else {
				cout << "blok_3" << " ";
				zycie = 3;
				ksztalt.setFillColor(Color::Red);
			}

		}

		//czy_bonus
		int los_czy_bonus = rand() % 100;

		if (los_czy_bonus <= 20) {
			blok_czy_bonus = true;
		}
		else {
			blok_czy_bonus = false;
		}

		punkty = 10;
		wielkosc.x = 3 * szerokosc_obiekt;
		wielkosc.y = wysokosc_obiekt;
		ksztalt.setSize(wielkosc);
		//ksztalt.setFillColor(Color::Yellow);
		//pozycja.x = pozycja_x;
		//pozycja.y = pozycja_y;
		ksztalt.setPosition(pozycja);
	}

	int czy_wyswietla() {
		//cout << zycie;
		zycie = zycie - 1;

		if (zycie == 2) {
			ksztalt.setFillColor(Color::Blue);
		}
		else if (zycie == 1) {
			ksztalt.setFillColor(Color::Yellow);
		}

		return zycie;
	}

	void kolizja_pilka_pomarancz() {
		zycie = 0;
	}

	float kolizja_lewo() {
		return pozycja.x;
	}

	float kolizja_prawo() {
		return pozycja.x + wielkosc.x;
	}

	float kolizja_gora() {
		return pozycja.y;
	}

	float kolizja_dol() {
		return pozycja.y + wielkosc.y;
	}

	int ilosc_blok_zmiana(int ilosc_blok) {
		if (zycie <= 0) {
			
			ilosc_blok = ilosc_blok + 1;
			//cout << ilosc_blok << " ";
		}

		return ilosc_blok;
	}

	RectangleShape wypisz() {
		return ksztalt;
	}

	Vector2f wypisz_pozycja() {
		return pozycja;
	}

	~blok() {
		cout << "dekonstruktor blok";
	}
private:
	RectangleShape ksztalt;
};

class vector_blok : public blok {
private:
	vector<blok> wiersz_blok;
	vector<vector<blok>> tablica_blok;
public:

	vector_blok(float szerokosc_obiekt, float wysokosc_obiekt, int rozdzielczosc_x, int rozdzielczosc_y, int pozycja_x, int pozycja_y, int poziom) : blok() {
		this->szerokosc_obiekt = szerokosc_obiekt;
		this->wysokosc_obiekt = wysokosc_obiekt;
		this->rozdzielczosc_x = rozdzielczosc_x;
		this->rozdzielczosc_y = rozdzielczosc_y;
		float przerwa_x = 0, przerwa_y = 0;
		przerwa_x = (szerokosc_obiekt * 10) / 9;
		przerwa_y = (wysokosc_obiekt * 0.7);


		cout << "blok" << szerokosc_obiekt << endl;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 7; j++) {
				pozycja_x;
				if (i == 0) {

					if (j == 0) {
						blok bloczek(szerokosc_obiekt, wysokosc_obiekt, rozdzielczosc_x, rozdzielczosc_y, 5 * szerokosc_obiekt, 4 * wysokosc_obiekt, poziom);
						wiersz_blok.push_back(bloczek);
					}
					else {
						blok bloczek(szerokosc_obiekt, wysokosc_obiekt, rozdzielczosc_x, rozdzielczosc_y, 5 * szerokosc_obiekt, (4 * wysokosc_obiekt) + j * (wysokosc_obiekt + przerwa_y), poziom);
						wiersz_blok.push_back(bloczek);
					}

				}
				else {
					przerwa_x = (szerokosc_obiekt * 10) / 9;

					if (j == 0) {
						blok bloczek(szerokosc_obiekt, wysokosc_obiekt, rozdzielczosc_x, rozdzielczosc_y, i * (przerwa_x + szerokosc_obiekt * 3) + (5 * szerokosc_obiekt), 4 * wysokosc_obiekt, poziom);
						wiersz_blok.push_back(bloczek);
					}
					else {
						blok bloczek(szerokosc_obiekt, wysokosc_obiekt, rozdzielczosc_x, rozdzielczosc_y, i * (przerwa_x + szerokosc_obiekt * 3) + (5 * szerokosc_obiekt), (4 * wysokosc_obiekt) + j * (wysokosc_obiekt + przerwa_y), poziom);
						wiersz_blok.push_back(bloczek);
					}

				}

				//blok bloczek(szerokosc_obiekt, wysokosc_obiekt, rozdzielczosc_x, rozdzielczosc_y, i * przerwa , j * 40);



			}
			tablica_blok.push_back(wiersz_blok);
			wiersz_blok.clear();
		}
	}

	blok& wypisz_b(int i, int j) {
		return tablica_blok[i][j];
	}

	~vector_blok() {
		cout << "dekonstruktor vector blok";
	}
};

class bonus : public obiekt{
private:
	RectangleShape ksztalt;
	Vector2f predkosc;
	int id_bonus;
public:

	bonus(float szerokosc_obiekt, float wysokosc_obiekt, int rozdzielczosc_x, int rozdzielczosc_y) {
		this->szerokosc_obiekt = szerokosc_obiekt;
		this->wysokosc_obiekt = wysokosc_obiekt;
		this->rozdzielczosc_x = rozdzielczosc_x;
		this->rozdzielczosc_y = rozdzielczosc_y;

		wielkosc.x = szerokosc_obiekt;
		wielkosc.y = szerokosc_obiekt;
		ksztalt.setSize(wielkosc);


	}

	void generuj_bonus(int poziom) {
		int los_bonus_rodzaj = rand() % 100;
		int proporcja_losowania = 100 - 5 * poziom;

		if (los_bonus_rodzaj <= proporcja_losowania) {
			//cout << "bonus dobry";
			int los_bonus = rand() % 400;

			if (los_bonus <= 100) id_bonus = 1;
			else if (los_bonus > 100 && los_bonus <= 200) id_bonus = 2;
			else if (los_bonus > 200 && los_bonus <= 300) id_bonus = 3;
			else if (los_bonus > 300 && los_bonus <= 400) id_bonus = 4;

			ksztalt.setFillColor(Color::Green);

		}
		else {
			//cout << "bonus zly";
			int los_bonus = rand() % 400;

			if (los_bonus <= 100) id_bonus = 11;
			else if (los_bonus > 100 && los_bonus <= 200) id_bonus = 12;
			else if (los_bonus > 200 && los_bonus <= 300) id_bonus = 13;
			else if (los_bonus > 300 && los_bonus <= 400) id_bonus = 14;

			ksztalt.setFillColor(Color::White);
		}

	}

	void pozycja_ustaw(Vector2f pozycja_blok) {
		pozycja.x = pozycja_blok.x + szerokosc_obiekt;
		pozycja.y = pozycja_blok.y;
		predkosc.y = 3;
		predkosc.x = 0;
		ksztalt.setPosition(pozycja);

	}

	void ruch_bonus() {
		pozycja.y += predkosc.y;
		ksztalt.setPosition(pozycja);
	}

	int wypisz_id_bonus() {
		return id_bonus;
	}

	RectangleShape wypisz() {
		return ksztalt;
	}

	float kolizja_lewo() {
		return pozycja.x;
	}

	float kolizja_prawo() {
		return pozycja.x + wielkosc.x;
	}

	float kolizja_gora() {
		return pozycja.y;
	}

	float kolizja_dol() {
		return pozycja.y + wielkosc.y;
	}

	~bonus() {
		cout << "wywolano destruktor bonus ";
	};
};
