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
using namespace std;
using namespace sf;

void gra_tryb_gracz1(int &rozdzielczosc_x, int  &rozdzielczosc_y, RenderWindow &okno_aplikacja, float &szer_obiekt, float &wys_obiekt, Event &zdarzenie, int &wybor, string &nazwa_gracza, int &poziom, int &pkt) {
	

	szer_obiekt = float(rozdzielczosc_x / 50.0);
	wys_obiekt = float(rozdzielczosc_y / 30.0);

	pasek_zycia pasek_gracz(szer_obiekt, wys_obiekt, rozdzielczosc_x, rozdzielczosc_y, 3);
	pasek_gracz.ustawienie_tekstury();
	rakietka Rakieta(szer_obiekt, wys_obiekt, rozdzielczosc_x, rozdzielczosc_y);
	pilka Pilka(wys_obiekt, szer_obiekt, rozdzielczosc_x, rozdzielczosc_y, (Rakieta.pozycja.x + Rakieta.wielkosc.x / 2) - szer_obiekt / 2, Rakieta.pozycja.y - wys_obiekt);
	vector_blok bloki(szer_obiekt, wys_obiekt, rozdzielczosc_x, rozdzielczosc_y, 100, 100, poziom);
	vector<vector<obiekt_neutralny>> ramka;
	string pkt_pomoc;
	int x = 5, y = 10;
	//int pkt = 0;
	int ilosc_blokow = 70;
	czcionka punkty_wyraz("Punkty", szer_obiekt, wys_obiekt, rozdzielczosc_x, rozdzielczosc_y, 0);
	czcionka punkty_liczba("0", szer_obiekt, wys_obiekt, rozdzielczosc_x, rozdzielczosc_y, 120);
	czcionka poziom_gry_wyswietlacz(to_string(poziom), szer_obiekt, wys_obiekt, rozdzielczosc_x, rozdzielczosc_y, szer_obiekt * 25 - 29);
	

	vector<bonus> vector_bonus;
	bool czy_zebrano_bonus;
	bool czy_kolizja_blok = true;
	bool rozpoczecie_gry = false;
	bool palza = false;

	ramka_stworz(szer_obiekt, wys_obiekt, rozdzielczosc_x, rozdzielczosc_y, ramka);

	

	while (true) {

		okno_aplikacja.pollEvent(zdarzenie);

		if (zdarzenie.type == Event::KeyPressed && zdarzenie.key.code == Keyboard::Escape && palza == false) {
			palza = true;
		}
		else if (zdarzenie.type == Event::KeyPressed && zdarzenie.key.code == Keyboard::Escape && palza == true) {
			palza = false;
		}

		if (palza == true) {
			okno_aplikacja.clear(Color::Black);
			okno_aplikacja.display();
			gra_pauza(okno_aplikacja, zdarzenie, rozdzielczosc_x, rozdzielczosc_y, wybor);
			if (wybor == 0) {
				return;
			}
			else {
				palza = false;
			}
		}
		else if (pasek_gracz.zmiana_rozmiar() == 0) {

			okno_aplikacja.clear(Color::Green);
			
			wybor = koniec_gry_porazka(okno_aplikacja, zdarzenie, rozdzielczosc_x, rozdzielczosc_y, pkt, poziom, nazwa_gracza);
			pkt = 0;
			return;

			okno_aplikacja.display();
		}
		else {


			okno_aplikacja.clear(Color::Black);

			

			if (zdarzenie.type == Event::Closed) {
				okno_aplikacja.close();
				break;
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::Space) && rozpoczecie_gry == false) {
				rozpoczecie_gry = true;
				Pilka.predkosc.x = 3;
				Pilka.predkosc.y = -3;
			}

			// rysowanie blokow
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 7; j++) {
					
					if (bloki.wypisz_b(i, j).zycie > 0) {
						if (czy_kolizja_blok == true) {
							kolizja_blok(bloki.wypisz_b(i, j), Pilka, pkt, ilosc_blokow);
						}
						else {
							brak_kolizji_blok(bloki.wypisz_b(i, j), Pilka, pkt, ilosc_blokow);
						}

						

						okno_aplikacja.draw(bloki.wypisz_b(i, j).wypisz());

						if (bloki.wypisz_b(i, j).zycie == 0 && bloki.wypisz_b(i, j).blok_czy_bonus == true) {
							bonus bonus_blok(szer_obiekt, wys_obiekt, rozdzielczosc_x, rozdzielczosc_y);
							bonus_blok.generuj_bonus(poziom);
							bonus_blok.pozycja_ustaw(bloki.wypisz_b(i, j).pozycja);
							vector_bonus.push_back(bonus_blok);

						}



					}

					/*					
					else if (bloki.wypisz_b(i, j).zycie == 0) {
						ilosc_blokow += 1;
						bloki.wypisz_b(i, j).zycie = -1;
						cout << ilosc_blokow << " ";
					}*/
					
					

				}
			}

			//zliczanie bloków
			ilosc_blokow = 0;
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 7; j++) {
					
					ilosc_blokow = bloki.wypisz_b(i, j).ilosc_blok_zmiana(ilosc_blokow);
					//cout << "ILOSC" << ilosc_blokow << " ";
				}
			}
			cout << ilosc_blokow << " ";

			//wywolanie konca gry - nastepny poziom 70
			if (ilosc_blokow == 8) {
				cout << "brawo koniec";
				nastepny_poziom(okno_aplikacja, zdarzenie, rozdzielczosc_x, rozdzielczosc_y, pkt, poziom, nazwa_gracza, wybor);
				cout << poziom << " wybor:" << wybor << endl;
				return;
				//poziom++;
			}


			//kolizja pilki z rakietka
			kolizja_rakietka(Rakieta, Pilka);


			//rysowanie bonusa
			for (int i = 0; i < vector_bonus.size(); i++) {
				vector_bonus[i].ruch_bonus();
				okno_aplikacja.draw(vector_bonus[i].wypisz());

				czy_zebrano_bonus = kolizja_bonus_rakietka(vector_bonus[i], Rakieta);

				if (czy_zebrano_bonus == true) {

					zeruj_bonus(Rakieta, Pilka, szer_obiekt, czy_kolizja_blok);

					switch (vector_bonus[i].wypisz_id_bonus()) {
					case 1:
						Rakieta.zmiana_predkosc(15);
						break;
					case 2:
						pkt += 50;
						pkt_pomoc = to_string(pkt);
						punkty_liczba.Tresc_zmiana(pkt_pomoc);
						break;
					case 3:
						//pasek_gracz.zycie_zwieksz();
						czy_kolizja_blok = false;
						Pilka.zmiana_kolor_przenikanie();
						//pasek_gracz.zmiana_rozmiar();
						break;
					case 4:
						Rakieta.wielkosc.x = szer_obiekt * 6;
						Rakieta.zmiana_wielkosci();
						break;

					case 11:
						Rakieta.zmiana_predkosc(4.5);
						break;
					case 12:
						pkt -= 50;
						pkt_pomoc = to_string(pkt);
						punkty_liczba.Tresc_zmiana(pkt_pomoc);
						break;
					case 13:
						pasek_zycia_aktualizacja(pasek_gracz, Pilka, rozdzielczosc_y, rozpoczecie_gry);
						break;
					case 14:
						Rakieta.wielkosc.x = szer_obiekt * 2;
						Rakieta.zmiana_wielkosci();
						break;
					default:
						break;
					}

					vector_bonus[i].~bonus();

				}
			}


			//Ruch rakietki
			Rakieta.ruch_lewo();
			Rakieta.ruch_prawo();
			okno_aplikacja.draw(Rakieta.wypisz());


			//rysowanie obramowania plnaszy
			for (int i = 0; i < 30; i++) {
				for (int j = 0; j < 50; j++) {
					if (i == 0 || i == 1) {
						okno_aplikacja.draw(ramka[i][j].wypisz());
					}
					else {
						if (j == 0 || j == 49) {
							okno_aplikacja.draw(ramka[i][j].wypisz());
						}
					}

				}
			}



			//ruch u rysowanie pilki
			if (rozpoczecie_gry == true) {
				Pilka.ruch();
			}
			else {
				zeruj_bonus(Rakieta, Pilka, szer_obiekt, czy_kolizja_blok);
				Pilka.ruch_rakietka((Rakieta.pozycja.x + Rakieta.wielkosc.x / 2) - szer_obiekt / 2, Rakieta.pozycja.y - wys_obiekt);
			}

			okno_aplikacja.draw(Pilka.wypisz());
			//cout << Pilka.pozycja.x;


			// zmiana licznika punktow
			pkt_pomoc = to_string(pkt);
			punkty_liczba.Tresc_zmiana(pkt_pomoc);



			for (int i = 0; i < pasek_gracz.zwroc_rozmiar(); i++) {
				okno_aplikacja.draw(pasek_gracz.wypisz(i));
			}
			//zmiana statusy paska zycia
			pasek_zycia_aktualizacja(pasek_gracz, Pilka, rozdzielczosc_y, rozpoczecie_gry);



			//cout << rozpoczecie_gry << " ";
			okno_aplikacja.draw(punkty_wyraz.wypisz());
			okno_aplikacja.draw(punkty_liczba.wypisz());
			okno_aplikacja.draw(poziom_gry_wyswietlacz.wypisz());
			okno_aplikacja.display();
			//cout << "ilosc_blokow: " << ilosc_blokow << ": " << endl;
			if (ilosc_blokow == 70) {
				wybor = 0;
			}

			if (ilosc_blokow == 70) {
				cout << "koniec";
				
				//system("pause");
			}
		}
	}
}

void zasady_gry_funkcja(RenderWindow &okno_aplikacja, Event &zdarzenie, int &wybor, string &nazwa_gracza) {
	int rozdzielczosc_x = okno_aplikacja.getSize().x;	// pobranie rozdzielczoœci ekranu ( horyzontalnie )
	int rozdzielczosc_y = okno_aplikacja.getSize().y;


	while (true) {
		okno_aplikacja.clear(Color::Black);
		Zasady_gry zasady(okno_aplikacja.getSize().x, okno_aplikacja.getSize().y);
		okno_aplikacja.pollEvent(zdarzenie);

		zasady.wypisz(okno_aplikacja);
		//zdarzenie.type == Event::KeyPressed && zdarzenie.key.code == Keyboard::Escape
		//if (Keyboard::isKeyPressed(Keyboard::Key::Right))
		if (zdarzenie.type == Event::KeyPressed && zdarzenie.key.code == Keyboard::Right) return;
			//menu_glowne_funkcja(okno_aplikacja, zdarzenie, wybor, nazwa_gracza);

		okno_aplikacja.display();
	}
	
}

int menu_glowne_funkcja(RenderWindow &okno_aplikacja, Event &zdarzenie, int &wybor, string &nazwa_gracza) {

	int rozdzielczosc_x = okno_aplikacja.getSize().x;	// pobranie rozdzielczoœci ekranu ( horyzontalnie )
	int rozdzielczosc_y = okno_aplikacja.getSize().y;

	Wstep wstep(okno_aplikacja.getSize().x, okno_aplikacja.getSize().y);
	Menu menu(okno_aplikacja.getSize().x, okno_aplikacja.getSize().y);
	Koniec koniec(okno_aplikacja.getSize().x, okno_aplikacja.getSize().y);

	okno_aplikacja.pollEvent(zdarzenie);

	bool wstep_bool = true;
	/*
	while (okno_aplikacja.isOpen()) {
		while (okno_aplikacja.pollEvent(zdarzenie)) {

		}
	}*/



	while (okno_aplikacja.isOpen()) {
		while (okno_aplikacja.pollEvent(zdarzenie)) {
			switch (zdarzenie.type) {
			case Event::KeyPressed:

				switch (zdarzenie.key.code) {
					//case Keyboard::Enter:
							//switch (wstep.wybierz_przycisk()) {
					if (Keyboard::isKeyPressed(Keyboard::Key::Enter)) {
						//okno_aplikacja.clear();
						//menu.wypisz(okno_aplikacja);
				case Keyboard::Up:
					menu.strzalka_w_gore();
					break;
				case Keyboard::Down:
					menu.strzalka_w_dol();
					break;
				case Keyboard::Enter:

					if (wstep_bool == false) {

						switch (menu.wybierz_przycisk()) {
						case 0:
							nazwa_gracza = podaj_nazwe_gracza(okno_aplikacja, zdarzenie, rozdzielczosc_x, rozdzielczosc_y);
							wybor = 1;
							cout <<"wybor: "<< wybor;
							return 0;
							
						case 1:
							//cout << "Option button has been pressed" << endl;
							tabela_rakordow(okno_aplikacja, zdarzenie, rozdzielczosc_x, rozdzielczosc_y, wybor);
							break;
						case 2:
							//cout << "Option button has been pressed" << endl;
							zasady_gry_funkcja(okno_aplikacja, zdarzenie, wybor, nazwa_gracza);
							cout << "zasady gry";
							wybor = 0;
							return 0;
							//cout << "Option button has been pressed" << endl;
							break;
						case 3:
							okno_aplikacja.close();
							wybor = -1;
							break;
						}

					}


					}
				}
				break;
			case Event::Closed:
				okno_aplikacja.close();
				break;
			}
		}

		okno_aplikacja.clear();
		if (wstep_bool == true) {
			wstep.wypisz(okno_aplikacja);

			if (Keyboard::isKeyPressed(Keyboard::Key::Enter)) wstep_bool = false;


		}
		else {
			menu.wypisz(okno_aplikacja);
		}

		okno_aplikacja.display();

	}

}