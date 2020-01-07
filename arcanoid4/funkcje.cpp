#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "obiekty_gry.h"
#include "gracz.h"
#include "funkcje.h"
#include "tryby_gry.h"
#include "menu_glowne.h"
#include <cstdio>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;
using namespace sf;

void zeruj_bonus(rakietka &Rakieta, pilka &Pilka, float &szer_obiekt, bool &czy_kolizja_blok) {
	Rakieta.zmiana_predkosc(7.5);
	Rakieta.wielkosc.x = szer_obiekt * 4;
	Rakieta.zmiana_wielkosci();
	Pilka.zmiana_kolor_normal();
	czy_kolizja_blok = true;

}

void brak_kolizji_blok(blok &Blok, pilka &Pilka, int &pkt, int &ilosc_blokow) {

	if (Pilka.predkosc.x < 0) {
		if (Blok.kolizja_prawo() > Pilka.kolizja_lewo() && Pilka.kolizja_lewo() > Blok.kolizja_prawo() - 10) {
			if (Blok.kolizja_gora() <= Pilka.kolizja_dol() && Blok.kolizja_dol() >= Pilka.kolizja_gora()) {
				Blok.kolizja_pilka_pomarancz();

				pkt += 10;

			}
		}
	}
	else if (Pilka.predkosc.x > 0) {
		//kolizja z lewej strony
		if (Blok.kolizja_lewo() < Pilka.kolizja_prawo() && Pilka.kolizja_prawo() < Blok.kolizja_lewo() + 10) {
			if (Blok.kolizja_gora() <= Pilka.kolizja_dol() && Blok.kolizja_dol() >= Pilka.kolizja_gora()) {
				Blok.kolizja_pilka_pomarancz();

				pkt += 10;

			}
		}
	}

	if (Pilka.predkosc.y > 0) {
		//kolizja z góry
		if (Blok.kolizja_gora() < Pilka.kolizja_dol() && Pilka.kolizja_dol() < Blok.kolizja_gora() + 10) {
			if (Blok.kolizja_lewo() <= Pilka.kolizja_prawo() && Blok.kolizja_prawo() >= Pilka.kolizja_lewo()) {
				Blok.kolizja_pilka_pomarancz();

				pkt += 10;

			}
		}
	}
	else {
		//kolizja z do³u
		if (Blok.kolizja_dol() > Pilka.kolizja_gora() && Pilka.kolizja_gora() > Blok.kolizja_dol() - 10) {
			if (Blok.kolizja_lewo() <= Pilka.kolizja_prawo() && Blok.kolizja_prawo() >= Pilka.kolizja_lewo()) {
				Blok.kolizja_pilka_pomarancz();

				pkt += 10;

			}
		}
	}

//	if (Blok.zycie == 0) {
//		ilosc_blokow -= 1;
//		cout << ilosc_blokow << " ";
//	}
}

void kolizja_blok(blok &Blok, pilka &Pilka, int &pkt, int &ilosc_blokow) {

	// kolizja z prawej strony
	if (Pilka.predkosc.x < 0) {
		if (Blok.kolizja_prawo() > Pilka.kolizja_lewo() && Pilka.kolizja_lewo() > Blok.kolizja_prawo() - 10) {
			if (Blok.kolizja_gora() <= Pilka.kolizja_dol() && Blok.kolizja_dol() >= Pilka.kolizja_gora()) {

			

				Blok.czy_wyswietla();

				Pilka.predkosc.x *= -1;

				Pilka.ruch();
				//cout << "prawo";
				pkt += 10;

			}
		}
	}
	else if (Pilka.predkosc.x > 0) {
		//kolizja z lewej strony
		if (Blok.kolizja_lewo() < Pilka.kolizja_prawo() && Pilka.kolizja_prawo() < Blok.kolizja_lewo() + 10) {
			if (Blok.kolizja_gora() <= Pilka.kolizja_dol() && Blok.kolizja_dol() >= Pilka.kolizja_gora()) {

				Blok.czy_wyswietla();

				Pilka.predkosc.x *= -1;

				Pilka.ruch();
				//cout << "lewo";
				pkt += 10;

			}
		}
	}

	if (Pilka.predkosc.y > 0) {
		//kolizja z góry
		if (Blok.kolizja_gora() < Pilka.kolizja_dol() && Pilka.kolizja_dol() < Blok.kolizja_gora() + 10) {
			if (Blok.kolizja_lewo() <= Pilka.kolizja_prawo() && Blok.kolizja_prawo() >= Pilka.kolizja_lewo()) {

				Blok.czy_wyswietla();

				Pilka.predkosc.y *= -1;

				Pilka.ruch();
				pkt += 10;

			}
		}
	}
	else {
		//kolizja z do³u
		if (Blok.kolizja_dol() > Pilka.kolizja_gora() && Pilka.kolizja_gora() > Blok.kolizja_dol() - 10) {
			if (Blok.kolizja_lewo() <= Pilka.kolizja_prawo() && Blok.kolizja_prawo() >= Pilka.kolizja_lewo()) {

				Blok.czy_wyswietla();

				Pilka.predkosc.y *= -1;

				Pilka.ruch();
				pkt += 10;

			}
		}
	}

//	if (Blok.zycie == 0) {
//		ilosc_blokow -= 1;
//		cout << ilosc_blokow << " ";
//	}
	
}

void kolizja_rakietka(rakietka &Rakietka, pilka &Pilka) {

	
	// kolizja z prawej strony
	if (Pilka.predkosc.x < 0) {
		if (Rakietka.kolizja_prawo() > Pilka.kolizja_lewo() && Pilka.kolizja_lewo() > Rakietka.kolizja_prawo() - 10) {
			if (Rakietka.kolizja_gora() <= Pilka.kolizja_dol() && Rakietka.kolizja_dol() >= Pilka.kolizja_gora()) {


				//Pilka.predkosc.x *= -1;
				Pilka.predkosc.y = -1.5;
				Pilka.predkosc.x = 3.9685;

				Pilka.ruch();
				//cout << "prawo";

			}
		}
	}
	else if (Pilka.predkosc.x > 0) {
		//kolizja z lewej strony
		if (Rakietka.kolizja_lewo() < Pilka.kolizja_prawo() && Pilka.kolizja_prawo() < Rakietka.kolizja_lewo() + 10) {
			if (Rakietka.kolizja_gora() <= Pilka.kolizja_dol() && Rakietka.kolizja_dol() >= Pilka.kolizja_gora()) {


				//Pilka.predkosc.x *= -1;
				Pilka.predkosc.y = -1.5;
				Pilka.predkosc.x = -3.9685;

				Pilka.ruch();
				//cout << "lewo";

			}
		}
	}
	

	
	if (Pilka.predkosc.y > 0) {
		//kolizja z góry
		if (Rakietka.kolizja_gora() < Pilka.kolizja_dol() && Pilka.kolizja_dol() < Rakietka.kolizja_gora() + 10) {
			if (Rakietka.kolizja_lewo() <= Pilka.kolizja_prawo() && Rakietka.kolizja_prawo() >= Pilka.kolizja_lewo()) {


				//Pilka.predkosc.y *= -1;

				if (Pilka.kolizja_prawo() > Rakietka.pozycja.x && Pilka.srodek_dol() < Rakietka.pozycja.x + Rakietka.czesc_rakietki) {
					Pilka.predkosc.y = -1.5;
					Pilka.predkosc.x = -3.9685;
				}
				else if (Pilka.srodek_dol() > Rakietka.pozycja.x + Rakietka.czesc_rakietki && Pilka.srodek_dol() < Rakietka.pozycja.x + Rakietka.czesc_rakietki * 2) {
					Pilka.predkosc.y = -3;
					Pilka.predkosc.x = -3;
				}
				else if (Pilka.srodek_dol() > Rakietka.pozycja.x + Rakietka.czesc_rakietki * 2 && Pilka.srodek_dol() < Rakietka.pozycja.x + Rakietka.czesc_rakietki * 3) {
					Pilka.predkosc.y = -3.9685;
					Pilka.predkosc.x = -1.5;
				}


				else if (Pilka.srodek_dol() > Rakietka.pozycja.x + Rakietka.czesc_rakietki * 3 && Pilka.srodek_dol() < Rakietka.pozycja.x + Rakietka.czesc_rakietki * 4) {
					Pilka.predkosc.y = -4.2426;
					Pilka.predkosc.x = 0;
				}


				else if (Pilka.srodek_dol() > Rakietka.pozycja.x + Rakietka.czesc_rakietki * 4 && Pilka.srodek_dol() < Rakietka.pozycja.x + Rakietka.czesc_rakietki * 5) {
					Pilka.predkosc.y = -3.9685;
					Pilka.predkosc.x = 1.5;
				}
				else if (Pilka.srodek_dol() > Rakietka.pozycja.x + Rakietka.czesc_rakietki * 5 && Pilka.srodek_dol() < Rakietka.pozycja.x + Rakietka.czesc_rakietki * 6) {
					Pilka.predkosc.y = -3;
					Pilka.predkosc.x = 3;
				}
				else if (Pilka.srodek_dol() > Rakietka.pozycja.x + Rakietka.czesc_rakietki * 6 && Pilka.kolizja_lewo() < Rakietka.pozycja.x + Rakietka.czesc_rakietki * 7) {
					Pilka.predkosc.y = -1.5;
					Pilka.predkosc.x = 3.9685;
				}

				Pilka.ruch();

			}
		}
	}
	else {
		//kolizja z do³u
		if (Rakietka.kolizja_dol() > Pilka.kolizja_gora() && Pilka.kolizja_gora() > Rakietka.kolizja_dol() - 10) {
			if (Rakietka.kolizja_lewo() <= Pilka.kolizja_prawo() && Rakietka.kolizja_prawo() >= Pilka.kolizja_lewo()) {


				Pilka.predkosc.y *= -1;



				Pilka.ruch();

			}
		}
	}

	/*
	if (Pilka.kolizja_dol() > Rakietka.kolizja_gora() && Pilka.kolizja_dol() < Rakietka.kolizja_dol() && Pilka.kolizja_prawo() > Rakietka.kolizja_lewo() && Pilka.kolizja_lewo() < Rakietka.kolizja_prawo()) {

		if (Pilka.kolizja_prawo() > Rakietka.pozycja.x && Pilka.srodek_dol() < Rakietka.pozycja.x + Rakietka.czesc_rakietki) {
			Pilka.predkosc.y = -1.5;
			Pilka.predkosc.x = -3.9685;
		}
		else if (Pilka.srodek_dol() > Rakietka.pozycja.x + Rakietka.czesc_rakietki && Pilka.srodek_dol() < Rakietka.pozycja.x + Rakietka.czesc_rakietki * 2) {
			Pilka.predkosc.y = -3;
			Pilka.predkosc.x = -3;
		}
		else if (Pilka.srodek_dol() > Rakietka.pozycja.x + Rakietka.czesc_rakietki * 2 && Pilka.srodek_dol() < Rakietka.pozycja.x + Rakietka.czesc_rakietki * 3) {
			Pilka.predkosc.y = -3.9685;
			Pilka.predkosc.x = -1.5;
		}


		else if (Pilka.srodek_dol() > Rakietka.pozycja.x + Rakietka.czesc_rakietki * 3 && Pilka.srodek_dol() < Rakietka.pozycja.x + Rakietka.czesc_rakietki * 4) {
			Pilka.predkosc.y = -4.2426;
			Pilka.predkosc.x = 0;
		}


		else if (Pilka.srodek_dol() > Rakietka.pozycja.x + Rakietka.czesc_rakietki * 4 && Pilka.srodek_dol() < Rakietka.pozycja.x + Rakietka.czesc_rakietki * 5) {
			Pilka.predkosc.y = -3.9685;
			Pilka.predkosc.x = 1.5;
		}
		else if (Pilka.srodek_dol() > Rakietka.pozycja.x + Rakietka.czesc_rakietki * 5 && Pilka.srodek_dol() < Rakietka.pozycja.x + Rakietka.czesc_rakietki * 6) {
			Pilka.predkosc.y = -3;
			Pilka.predkosc.x = 3;
		}
		else if (Pilka.srodek_dol() > Rakietka.pozycja.x + Rakietka.czesc_rakietki * 6 && Pilka.kolizja_lewo() < Rakietka.pozycja.x + Rakietka.czesc_rakietki * 7) {
			Pilka.predkosc.y = -1.5;
			Pilka.predkosc.x = 3.9685;
		}
		Pilka.ruch();
	}
	*/

}

bool kolizja_bonus_rakietka(bonus &blok_bonus, rakietka &Rakietka) {

	if (blok_bonus.pozycja.y + blok_bonus.wielkosc.y >= Rakietka.pozycja.y && blok_bonus.pozycja.y <= Rakietka.pozycja.y + Rakietka.wielkosc.y) {

		if (blok_bonus.kolizja_lewo() <= Rakietka.kolizja_prawo() && blok_bonus.kolizja_prawo() >= Rakietka.kolizja_lewo()) {

			return true;
		}
	}

	return false;
}

void ramka_stworz(float szerokosc_obiekt, float wysokosc_obiekt, int rozdzielczosc_x, int rozdzielczosc_y, vector<vector<obiekt_neutralny>> &ramka) {

	vector<obiekt_neutralny> ramka_pomoc;

	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 50; j++) {
			obiekt_neutralny obj(szerokosc_obiekt, wysokosc_obiekt, rozdzielczosc_x, rozdzielczosc_y);
			obj.ustaw_pozycje(szerokosc_obiekt * j, wysokosc_obiekt * i);
			ramka_pomoc.push_back(obj);
		}
		ramka.push_back(ramka_pomoc);
		ramka_pomoc.clear();

	}




}

void pasek_zycia_aktualizacja(pasek_zycia &pasek_gracz, pilka &Pilka, int &rozdzielczosc_y, bool &rozpoczecie_gry) {

	if (Pilka.pozycja.y > rozdzielczosc_y) {
		rozpoczecie_gry = false;
		pasek_gracz.zycie_zmiejsz();
		pasek_gracz.zmiana_rozmiar();
		Pilka.predkosc.x = 0;
		Pilka.predkosc.y = 0;
		
		
	}
}

string podaj_nazwe_gracza(RenderWindow &okno_aplikacja, Event &zdarzenie, int rozdzielczosc_x, int rozdzielczosc_y) {
	

	RectangleShape wpisz;
	Text nazwa_gracz;
	Text info, info2;
	Font styl;
	string string_gracz;
	
	wpisz.setFillColor(Color::White);
	wpisz.setSize({ 600,60 });

	Vector2f pozycja_pole(rozdzielczosc_x / 2 - 300, 280);
	wpisz.setPosition(pozycja_pole);

	if (styl.loadFromFile("grafika/czcionka_1/Raleway-LightItalic.ttf")) {
		cout << "Czcionka poprawnie zaladowana";
	}
	else {
		cout << "Cznionka nie zaladowana";
	}

	nazwa_gracz.setFont(styl);
	nazwa_gracz.setFillColor(Color::Red);
	nazwa_gracz.setPosition({200,200 });
	//tekst.setScale({ 100,100 });
	info.setFont(styl);
	info.setFillColor(Color::Red);
	info.setString("Nacisnij ENTER aby rozpoczac gre");
	FloatRect wysrotkowanie_tekstu_info = info.getLocalBounds();
	info.setOrigin(wysrotkowanie_tekstu_info.width / 2, wysrotkowanie_tekstu_info.height / 2);
	Vector2f pozycja_info(rozdzielczosc_x / 2, rozdzielczosc_y - 100);
	info.setPosition(pozycja_info);

	info2.setFont(styl);
	info2.setFillColor(Color::Red);
	info2.setString("Wpisz nazwe gracza");
	FloatRect wysrotkowanie_tekstu_info2 = info2.getLocalBounds();
	info2.setOrigin(wysrotkowanie_tekstu_info2.width / 2, wysrotkowanie_tekstu_info2.height / 2);
	Vector2f pozycja_info2(rozdzielczosc_x / 2, 200);
	info2.setPosition(pozycja_info2);
	

	FloatRect wysrotkowanie_tekstu_nazwa;
	Vector2f pozycja_nazwa(rozdzielczosc_x / 2, 300);

	while (true) {
		okno_aplikacja.pollEvent(zdarzenie);
		okno_aplikacja.clear(Color::Black);
		okno_aplikacja.draw(wpisz);

		if (zdarzenie.type == Event::KeyPressed) {
			cout << zdarzenie.key.code<<" ";
			//cout << static_cast <char>(zdarzenie.key.code);

			
			switch (zdarzenie.key.code) {

			case 0:
				string_gracz += 'A';
				break;
			case 1:
				string_gracz += 'B';
				break;
			case 2:
				string_gracz += 'C';
				break;
			case 3:
				string_gracz += 'D';
				break;
			case 4:
				string_gracz += 'E';
				break;
			case 5:
				string_gracz += 'F';
				break;
			case 6:
				string_gracz += 'G';
				break;
			case 7:
				string_gracz += 'H';
				break;
			case 8:
				string_gracz += 'I';
				break;
			case 9:
				string_gracz += 'J';
				break;
			case 10:
				string_gracz += 'K';
				break;
			case 11:
				string_gracz += 'L';
				break;
			case 12:
				string_gracz += 'M';
				break;
			case 13:
				string_gracz += 'N';
				break;
			case 14:
				string_gracz += 'O';
				break;
			case 15:
				string_gracz += 'P';
				break;
			case 16:
				string_gracz += 'Q';
				break;
			case 17:
				string_gracz += 'R';
				break;
			case 18:
				string_gracz += 'S';
				break;
			case 19:
				string_gracz += 'T';
				break;
			case 20:
				string_gracz += 'U';
				break;
			case 21:
				string_gracz += 'V';
				break;
			case 22:
				string_gracz += 'W';
				break;
			case 23:
				string_gracz += 'X';
				break;
			case 24:
				string_gracz += 'Y';
				break;
			case 25:
				string_gracz += 'Z';
				break;
			case 59:
				if (string_gracz.size() > 0) {
					string_gracz.erase(string_gracz.size() - 1, 1);
				}
				
				break;
			case 58:
				if (string_gracz.size() > 0) {
					//wybor = 1;
					return string_gracz;
				}
			}
			nazwa_gracz.setString(string_gracz);
			wysrotkowanie_tekstu_nazwa = nazwa_gracz.getLocalBounds();
			nazwa_gracz.setOrigin(wysrotkowanie_tekstu_nazwa.width / 2, wysrotkowanie_tekstu_nazwa.height / 2);
			nazwa_gracz.setPosition(pozycja_nazwa);
			
			
		}

		okno_aplikacja.draw(nazwa_gracz);
		okno_aplikacja.draw(info);
		okno_aplikacja.draw(info2);
		okno_aplikacja.display();
		//cout << string_gracz;

		//return 0;
	}
	//return string_gracz;

}

void gra_pauza(RenderWindow &okno_aplikacja, Event &zdarzenie, int rozdzielczosc_x, int rozdzielczosc_y, int &wybor) {
	Font styl;
	Text info, info2, info3;

	if (styl.loadFromFile("grafika/czcionka_1/Raleway-LightItalic.ttf")) {
		cout << "Czcionka poprawnie zaladowana";
	}
	else {
		cout << "Cznionka nie zaladowana";
	}

	info.setFont(styl);
	info.setFillColor(Color::Red);
	info.setString("PAUZA");
	info.setScale({ 3,3 });
	FloatRect wysrotkowanie_tekstu_info = info.getLocalBounds();
	info.setOrigin(wysrotkowanie_tekstu_info.width / 2, wysrotkowanie_tekstu_info.height / 2);
	Vector2f pozycja_info(rozdzielczosc_x / 2, 100);
	info.setPosition(pozycja_info);

	info2.setFont(styl);
	info2.setFillColor(Color::Red);
	info2.setString("Nacisnij ESC aby wrocic do gry");
	FloatRect wysrotkowanie_tekstu_info2 = info2.getLocalBounds();
	info2.setOrigin(wysrotkowanie_tekstu_info2.width / 2, wysrotkowanie_tekstu_info2.height / 2);
	Vector2f pozycja_info2(rozdzielczosc_x / 2, rozdzielczosc_y / 2 + 200);
	info2.setPosition(pozycja_info2);

	info3.setFont(styl);
	info3.setFillColor(Color::Red);
	
	info3.setString("Nacisnij ENTER aby wyjsc do MENU");
	FloatRect wysrotkowanie_tekstu_info3 = info3.getLocalBounds();
	info3.setOrigin(wysrotkowanie_tekstu_info3.width / 2, wysrotkowanie_tekstu_info3.height / 2);
	Vector2f pozycja_info3(rozdzielczosc_x / 2, rozdzielczosc_y - 100);
	info3.setPosition(pozycja_info3);

	while (true) {
		okno_aplikacja.clear();
		okno_aplikacja.pollEvent(zdarzenie);

		if (zdarzenie.type == Event::KeyPressed && zdarzenie.key.code == Keyboard::Escape) {
			return;
		}
		else if (zdarzenie.type == Event::KeyPressed && zdarzenie.key.code == Keyboard::Enter) {
			wybor = 0;
			return;
		}



		okno_aplikacja.draw(info);
		okno_aplikacja.draw(info2);
		okno_aplikacja.draw(info3);
		okno_aplikacja.display();
	}
}

int koniec_gry_porazka(RenderWindow &okno_aplikacja, Event &zdarzenie, int rozdzielczosc_x, int rozdzielczosc_y, int &punkty, int &poziom, string &nazwa_gracza) {
	zapis_do_pliku(nazwa_gracza, punkty, poziom);
	
	
	fstream plik_tabela;
	plik_tabela.open("tabela_wyniki.txt", ios::in);
	string nazwa_plik;
	string punkty_plik;
	string poziom_plik;
	int punkty_sort;

	string wszystko;

	Text pozycja;
	Text nr_pozycja;
	Font styl;

	
	Vector2f pozycja_pole(rozdzielczosc_x / 2, 280);
	Vector2f pozycja_pole_nr(200, 280);


	if (styl.loadFromFile("grafika/czcionka_1/Raleway-LightItalic.ttf")) {
		cout << "Czcionka poprawnie zaladowana";
	}
	else {
		cout << "Cznionka nie zaladowana";
	}

	pozycja.setFont(styl);
	pozycja.setFillColor(Color::Red);
	pozycja.setPosition(pozycja_pole);
	//tekst.setScale({ 100,100 });
	
	FloatRect wysrotkowanie_tekstu_info = pozycja.getLocalBounds();
	pozycja.setOrigin(wysrotkowanie_tekstu_info.width / 2, wysrotkowanie_tekstu_info.height / 2);

	nr_pozycja.setFont(styl);
	nr_pozycja.setFillColor(Color::White);
	nr_pozycja.setPosition(pozycja_pole_nr);
	//nr_pozycja.setCharacterSize(24);
	//tekst.setScale({ 100,100 });
	pozycja.setString("test");
	FloatRect wysrotkowanie_tekstu_pozycja_nr = nr_pozycja.getLocalBounds();
	nr_pozycja.setOrigin(wysrotkowanie_tekstu_pozycja_nr.width / 2, wysrotkowanie_tekstu_pozycja_nr.height / 2);



	vector<tabela> tab_wyniki;
	tabela tab_wiersz;
	int pomoc_a = 0;
	if (plik_tabela) {
		while (!plik_tabela.eof()) {
			if (pomoc_a > 0) {
				plik_tabela >> nazwa_plik;
				plik_tabela >> punkty_plik;
				plik_tabela >> poziom_plik;
				punkty_sort = stoi(punkty_plik);

				//wszystko = nazwa_plik + " " + punkty_plik + " " + poziom_plik;
				cout << wszystko << " ";
				tab_wiersz.nazwa = nazwa_plik;
				tab_wiersz.poziom = poziom_plik;
				tab_wiersz.punkty = punkty_plik;
				tab_wiersz.pkt_sort = punkty_sort;

				tab_wyniki.push_back(tab_wiersz);
			}
			else {
				pomoc_a = 1;
			}
			
		}
		
	}
	else {
		cout << "Blad_pliku - zapis";
	}

	for (int i = 0; i < tab_wyniki.size(); i++) {
		cout << tab_wyniki[i].nazwa << " " << tab_wyniki[i].poziom << " " << tab_wyniki[i].punkty<<" " <<tab_wyniki[i].pkt_sort<<endl;
	}

	for (int i = 0; i < tab_wyniki.size(); i++)
		for (int j = 1; j < tab_wyniki.size() - i; j++) //pêtla wewnêtrzna
			if (tab_wyniki[j - 1].pkt_sort < tab_wyniki[j].pkt_sort)
				//zamiana miejscami
				swap(tab_wyniki[j - 1], tab_wyniki[j]);
	//tu sortowanie;

	while (true) {
		okno_aplikacja.pollEvent(zdarzenie);
		okno_aplikacja.clear(Color::Black);
		
		pozycja_pole.y = 40;
		pozycja.setString("Wyniki");
		FloatRect wysrotkowanie_tekstu_info = pozycja.getLocalBounds();
		pozycja.setOrigin(wysrotkowanie_tekstu_info.width / 2, wysrotkowanie_tekstu_info.height / 2);
		pozycja.setPosition(pozycja_pole);
		okno_aplikacja.draw(pozycja);


		pozycja_pole.y = 80;
		pozycja_pole_nr.y += 80;

		nr_pozycja.setString("hejj");
		nr_pozycja.setPosition(pozycja_pole_nr);
		okno_aplikacja.draw(nr_pozycja);

		for (int i = 0; i < tab_wyniki.size(); i++) {
			if (i == 10) break;
			//nr_pozycja.setString("hejj");
			wszystko = tab_wyniki[i].nazwa + " poziom " + tab_wyniki[i].poziom + "  wynik: " + tab_wyniki[i].punkty;
			//cout << tab_wyniki[i].nazwa << " " << tab_wyniki[i].poziom << " " << tab_wyniki[i].punkty << " " << tab_wyniki[i].pkt_sort << endl;
			pozycja.setString(wszystko);
			FloatRect wysrotkowanie_tekstu_info = pozycja.getLocalBounds();
			pozycja.setOrigin(wysrotkowanie_tekstu_info.width / 2, wysrotkowanie_tekstu_info.height / 2);
			FloatRect wysrotkowanie_tekstu_pozycja_nr = nr_pozycja.getLocalBounds();
			nr_pozycja.setOrigin(wysrotkowanie_tekstu_pozycja_nr.width / 2, wysrotkowanie_tekstu_pozycja_nr.height / 2);

			pozycja_pole_nr.y += 50;
			pozycja_pole.y += 50;
			pozycja.setPosition(pozycja_pole);
			
			okno_aplikacja.draw(pozycja);
			
		}
		

		pozycja_pole.y = rozdzielczosc_y - 100;
		pozycja.setString("Nacisnij ENTER aby wrocic do MENU");
		wysrotkowanie_tekstu_info = pozycja.getLocalBounds();
		pozycja.setOrigin(wysrotkowanie_tekstu_info.width / 2, wysrotkowanie_tekstu_info.height / 2);
		pozycja.setPosition(pozycja_pole);
		okno_aplikacja.draw(pozycja);

		okno_aplikacja.display();

		if (zdarzenie.type == Event::KeyPressed && zdarzenie.key.code == Keyboard::Enter) {
			poziom = 0;
			return 0;
		}
	}

	
}
	
int nastepny_poziom(RenderWindow &okno_aplikacja, Event &zdarzenie, int rozdzielczosc_x, int rozdzielczosc_y, int &punkty, int &poziom, string &nazwa_gracza, int &wybor) {
	Font styl;
	Text info, info2, info3;

	if (styl.loadFromFile("grafika/czcionka_1/Raleway-LightItalic.ttf")) {
		cout << "Czcionka poprawnie zaladowana";
	}
	else {
		cout << "Cznionka nie zaladowana";
	}

	info.setFont(styl);
	info.setFillColor(Color::Red);
	info.setString("Nacisnij ESC aby zakonczyc gre");
	FloatRect wysrotkowanie_tekstu_info = info.getLocalBounds();
	info.setOrigin(wysrotkowanie_tekstu_info.width / 2, wysrotkowanie_tekstu_info.height / 2);
	Vector2f pozycja_info(rozdzielczosc_x / 2, rozdzielczosc_y - 100);
	info.setPosition(pozycja_info);

	info2.setFont(styl);
	info2.setFillColor(Color::Red);
	info2.setString("Nacisnij Enter aby przejsc do nastepnego poziomu");
	FloatRect wysrotkowanie_tekstu_info2 = info2.getLocalBounds();
	info2.setOrigin(wysrotkowanie_tekstu_info2.width / 2, wysrotkowanie_tekstu_info2.height / 2);
	Vector2f pozycja_info2(rozdzielczosc_x / 2, rozdzielczosc_y / 2 + 200);
	info2.setPosition(pozycja_info2);

	info3.setFont(styl);
	info3.setFillColor(Color::Red);
	info3.setScale({ 2,2 });
	info3.setString("Ukonczyles poziom " + to_string(poziom) + " z wynikiem " + to_string(punkty));
	FloatRect wysrotkowanie_tekstu_info3 = info3.getLocalBounds();
	info3.setOrigin(wysrotkowanie_tekstu_info3.width / 2, wysrotkowanie_tekstu_info3.height / 2);
	Vector2f pozycja_info3(rozdzielczosc_x / 2, 200);
	info3.setPosition(pozycja_info3);

	while (true) {
		okno_aplikacja.clear();
		okno_aplikacja.pollEvent(zdarzenie);

		if (zdarzenie.type == Event::KeyPressed && zdarzenie.key.code == Keyboard::Escape) {
			zapis_do_pliku(nazwa_gracza, punkty, poziom);
			wybor = 0;
			return poziom = 0;
		}
		else if(zdarzenie.type == Event::KeyPressed && zdarzenie.key.code == Keyboard::Enter){
			wybor = 1;
			return poziom++;
		}

		

		okno_aplikacja.draw(info);
		okno_aplikacja.draw(info2);
		okno_aplikacja.draw(info3);
		okno_aplikacja.display();
	}

}

void zapis_do_pliku(string nazwa_gracza, int punkty, int poziom) {
	fstream plik_tabela;
	plik_tabela.open("tabela_wyniki.txt", ios::out | ios::app);

	if (plik_tabela) {
		plik_tabela << endl<< nazwa_gracza << " " << punkty << " " << poziom;
	}
	else {
		cout << "Blad_pliku - zapis";
		system("pause");
	}
	plik_tabela.close();
}

void odczyt_z_pliku( ) {
	fstream plik_tabela;
	plik_tabela.open("tabela_wyniki.txt", ios::in);

	if (plik_tabela) {
		while (!plik_tabela.eof()) {

		}
	}
	else {
		cout << "Blad_pliku - odczyt";
	}

}

int tabela_rakordow(RenderWindow &okno_aplikacja, Event &zdarzenie, int rozdzielczosc_x, int rozdzielczosc_y, int &wybor) {
	//zapis_do_pliku(nazwa_gracza, punkty, poziom);


	fstream plik_tabela;
	plik_tabela.open("tabela_wyniki.txt", ios::in);
	string nazwa_plik;
	string punkty_plik;
	string poziom_plik;
	int punkty_sort;

	string wszystko;

	Text pozycja;
	Text nr_pozycja;
	Font styl;


	Vector2f pozycja_pole(rozdzielczosc_x / 2, 280);
	Vector2f pozycja_pole_nr(200, 280);


	if (styl.loadFromFile("grafika/czcionka_1/Raleway-LightItalic.ttf")) {
		cout << "Czcionka poprawnie zaladowana";
	}
	else {
		cout << "Cznionka nie zaladowana";
	}

	pozycja.setFont(styl);
	pozycja.setFillColor(Color::Red);
	pozycja.setPosition(pozycja_pole);
	//tekst.setScale({ 100,100 });

	FloatRect wysrotkowanie_tekstu_info = pozycja.getLocalBounds();
	pozycja.setOrigin(wysrotkowanie_tekstu_info.width / 2, wysrotkowanie_tekstu_info.height / 2);

	nr_pozycja.setFont(styl);
	nr_pozycja.setFillColor(Color::White);
	nr_pozycja.setPosition(pozycja_pole_nr);
	//nr_pozycja.setCharacterSize(24);
	//tekst.setScale({ 100,100 });
	pozycja.setString("test");
	FloatRect wysrotkowanie_tekstu_pozycja_nr = nr_pozycja.getLocalBounds();
	nr_pozycja.setOrigin(wysrotkowanie_tekstu_pozycja_nr.width / 2, wysrotkowanie_tekstu_pozycja_nr.height / 2);



	vector<tabela> tab_wyniki;
	tabela tab_wiersz;
	int pomoc_a = 0;
	if (plik_tabela) {
		while (!plik_tabela.eof()) {
			if (pomoc_a > 0) {
				plik_tabela >> nazwa_plik;
				plik_tabela >> punkty_plik;
				plik_tabela >> poziom_plik;
				punkty_sort = stoi(punkty_plik);

				//wszystko = nazwa_plik + " " + punkty_plik + " " + poziom_plik;
				cout << wszystko << " ";
				tab_wiersz.nazwa = nazwa_plik;
				tab_wiersz.poziom = poziom_plik;
				tab_wiersz.punkty = punkty_plik;
				tab_wiersz.pkt_sort = punkty_sort;

				tab_wyniki.push_back(tab_wiersz);
			}
			else {
				pomoc_a = 1;
			}

		}

	}
	else {
		cout << "Blad_pliku - zapis";
	}

	for (int i = 0; i < tab_wyniki.size(); i++) {
		cout << tab_wyniki[i].nazwa << " " << tab_wyniki[i].poziom << " " << tab_wyniki[i].punkty << " " << tab_wyniki[i].pkt_sort << endl;
	}

	for (int i = 0; i < tab_wyniki.size(); i++)
		for (int j = 1; j < tab_wyniki.size() - i; j++) //pêtla wewnêtrzna
			if (tab_wyniki[j - 1].pkt_sort < tab_wyniki[j].pkt_sort)
				//zamiana miejscami
				swap(tab_wyniki[j - 1], tab_wyniki[j]);
	//tu sortowanie;

	while (true) {
		okno_aplikacja.pollEvent(zdarzenie);
		okno_aplikacja.clear(Color::Black);

		pozycja_pole.y = 40;
		pozycja.setString("Wyniki");
		FloatRect wysrotkowanie_tekstu_info = pozycja.getLocalBounds();
		pozycja.setOrigin(wysrotkowanie_tekstu_info.width / 2, wysrotkowanie_tekstu_info.height / 2);
		pozycja.setPosition(pozycja_pole);
		okno_aplikacja.draw(pozycja);


		pozycja_pole.y = 80;
		pozycja_pole_nr.y += 80;

		nr_pozycja.setString("hejj");
		nr_pozycja.setPosition(pozycja_pole_nr);
		okno_aplikacja.draw(nr_pozycja);

		for (int i = 0; i < tab_wyniki.size(); i++) {
			if (i == 10) break;
			//nr_pozycja.setString("hejj");
			wszystko = tab_wyniki[i].nazwa + " poziom " + tab_wyniki[i].poziom + "  wynik: " + tab_wyniki[i].punkty;
			//cout << tab_wyniki[i].nazwa << " " << tab_wyniki[i].poziom << " " << tab_wyniki[i].punkty << " " << tab_wyniki[i].pkt_sort << endl;
			pozycja.setString(wszystko);
			FloatRect wysrotkowanie_tekstu_info = pozycja.getLocalBounds();
			pozycja.setOrigin(wysrotkowanie_tekstu_info.width / 2, wysrotkowanie_tekstu_info.height / 2);
			FloatRect wysrotkowanie_tekstu_pozycja_nr = nr_pozycja.getLocalBounds();
			nr_pozycja.setOrigin(wysrotkowanie_tekstu_pozycja_nr.width / 2, wysrotkowanie_tekstu_pozycja_nr.height / 2);

			pozycja_pole_nr.y += 50;
			pozycja_pole.y += 50;
			pozycja.setPosition(pozycja_pole);

			okno_aplikacja.draw(pozycja);

		}


		pozycja_pole.y = rozdzielczosc_y - 100;
		pozycja.setString("Nacisnij ENTER aby wrocic do MENU");
		wysrotkowanie_tekstu_info = pozycja.getLocalBounds();
		pozycja.setOrigin(wysrotkowanie_tekstu_info.width / 2, wysrotkowanie_tekstu_info.height / 2);
		pozycja.setPosition(pozycja_pole);
		okno_aplikacja.draw(pozycja);

		okno_aplikacja.display();

		if (zdarzenie.type == Event::KeyPressed && zdarzenie.key.code == Keyboard::Enter) {
			wybor = 0;
			return 0;
		}
	}


}