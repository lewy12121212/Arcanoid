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
using namespace std;
using namespace sf;

//int ilosc_blok = 10;

int main()
{
	srand(time(NULL));

	int rozdzielczosc_x = 0, rozdzielczosc_y = 0;
	RenderWindow okno_aplikacja{ VideoMode(1200, 800), "arcanoid"};	// Stworzenie okna gry w trybie Fullscreen  sf::Style::Fullscreen 
	okno_aplikacja.setFramerateLimit(60);			// ustawienie częstotliwości odświerzania na 60 FPS
	Event zdarzenie; // stworzenie zmiennej odpowiadającej za zdarzenia występujące w grze
	rozdzielczosc_x = okno_aplikacja.getSize().x;	// pobranie rozdzielczości ekranu ( horyzontalnie )
	rozdzielczosc_y = okno_aplikacja.getSize().y;	// pobranie rozdzielczości ekranu ( wertykalnie )
	cout << "Rozdzielczosc ekranu: " << rozdzielczosc_x << " x " << rozdzielczosc_y << endl;
	int wybor = 0;	 // zmienna odpowiadająca za wyświetlenie odpowiedniego trybu gry

	float szer_obiekt = 0.0f;
	float wys_obiekt = 0.0f;

	//Koniec k(rozdzielczosc_x, rozdzielczosc_y);

	cout << "szer i wys obj " << szer_obiekt << " x " << wys_obiekt << endl;

	string nazwa_gracza;
	int poziom = 0;
	int punkty_gracz = 0;


	while (true) {

	
		okno_aplikacja.clear(Color::Black);
		okno_aplikacja.pollEvent(zdarzenie);

		if (zdarzenie.type == Event::Closed) {
			okno_aplikacja.close();
			break;
		}

		//gra_tryb_gracz1(rozdzielczosc_x, rozdzielczosc_y, okno_aplikacja, szer_obiekt, wys_obiekt, zdarzenie);
		
		switch (wybor) {

		case -1:
			return 0;
		case 0:
			menu_glowne_funkcja(okno_aplikacja, zdarzenie, wybor, nazwa_gracza);
			break;
		case 1:
			gra_tryb_gracz1(rozdzielczosc_x, rozdzielczosc_y, okno_aplikacja, szer_obiekt, wys_obiekt, zdarzenie, wybor, nazwa_gracza, poziom, punkty_gracz);
			break;

		}
		//gra_tryb_gracz1(rozdzielczosc_x, rozdzielczosc_y, okno_aplikacja, szer_obiekt, wys_obiekt, zdarzenie, wybor);

		cout << wybor << " " << endl;
		okno_aplikacja.display();
	}

	/*
	Texture tekstura_rakietka, tekstura_cegla;

	if (tekstura_rakietka.loadFromFile("./grafika/rakietka_4.png")) {
		cout << "Tekstura rakietka OK";
	}
	else {
		cout << "Tekstura rakietka ERROR";
	}

	if (tekstura_cegla.loadFromFile("./grafika/cegla_2.png")) {
		cout << "Tekstura cegla OK";
	}
	else {
		cout << "Tekstura rakietka ERROR";
	}



	CircleShape pilka;
	pilka.setRadius(15.0f);
	float x_p=100.0f, y_p=100.0f; // polozenie pilki
	Vector2f wektor_ruchu(3.0f, 3.0f); // ruch pilki
	pilka.setPosition(x_p, y_p);
	pilka.setFillColor(Color::Blue);
	Vector2f wielkosc_ob1(szer_obiekt * 4, wys_obiekt / 1.5), wielkosc_cegla(szer_obiekt, wys_obiekt), wielkosc_blok(2* szer_obiekt, wys_obiekt);
	Vector2f polozenie(szer_obiekt*25, wys_obiekt*28.5), polozenie_cegla( 0.0f, 0.0f), polozenie_blok(100,100);
	RectangleShape ob1;
	RectangleShape cegla_sciana, pusty;
	pusty.setSize(wielkosc_cegla);
	cegla_sciana.setSize(wielkosc_cegla);
	cegla_sciana.setTexture(&tekstura_cegla);
	ob1.setSize(wielkosc_ob1);
	ob1.setPosition(polozenie);
	ob1.setTexture(&tekstura_rakietka);
	int i = 0, j = 0;

	float czesc_rakietki = szer_obiekt * 4 / 5;
	cout << "czesc rakietki"<<czesc_rakietki << endl;


	RectangleShape blok;
	blok.setPosition(polozenie_blok);
	blok.setSize(wielkosc_blok);
	blok.setFillColor(Color::Red);
	vector<vector<RectangleShape>> vector_bloki;
	vector<RectangleShape> vector_bloki_wiersz;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 15; j++) {
			vector_bloki_wiersz.push_back(blok);
			polozenie_blok.x += szer_obiekt * 2 + 5;
			blok.setPosition(polozenie_blok);
		}
		vector_bloki.push_back(vector_bloki_wiersz);
		polozenie_blok.y += wys_obiekt + 5;
		polozenie_blok.x = 100;
		blok.setPosition(polozenie_blok);
		vector_bloki_wiersz.clear();
	}


	vector<vector<RectangleShape>> vector_sciana;
	vector<RectangleShape> vector_sciana_wiersz;

	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 50; j++) {

				if (i == 0) {
					vector_sciana_wiersz.push_back(cegla_sciana);
					polozenie_cegla.x += szer_obiekt;
					cegla_sciana.setPosition(polozenie_cegla);
				}
				else {
					if (j == 0 || j == 49) {
						vector_sciana_wiersz.push_back(cegla_sciana);
						polozenie_cegla.x += szer_obiekt;
						cegla_sciana.setPosition(polozenie_cegla);
					}
					else {
						vector_sciana_wiersz.push_back(pusty);
						polozenie_cegla.x += szer_obiekt;
						cegla_sciana.setPosition(polozenie_cegla);
					}
				}


		}
		polozenie_cegla.y += wys_obiekt;
		polozenie_cegla.x = 0;
		cegla_sciana.setPosition(polozenie_cegla);
		vector_sciana.push_back(vector_sciana_wiersz);
		vector_sciana_wiersz.clear();
	}


	while(true) { // utworzenie nieskończonej pętli programu



		if (okno_gry == 1) {

			// wyczyszczenie okna i zapełnienie go kolorem
			okno_aplikacja.clear(Color::Black);
			// rozpoczęcie nasłuchiwania zdarzenia
			okno_aplikacja.pollEvent(zdarzenie_1);


			// obsługa zdarzeń klawiatury i okna gry ( dotyczy trybu okienkowego )
			if (zdarzenie_1.type == Event::Closed) {
				okno_aplikacja.close();
				break;
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::Right) && polozenie.x < szer_obiekt * 45) {
				polozenie.x += 7.5;
				ob1.setPosition(polozenie);
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::Left) && polozenie.x > szer_obiekt) {
				polozenie.x -= 7.5;
				ob1.setPosition(polozenie);
			}

			// Obsługa ruchu piłeczki
			if (x_p < szer_obiekt) {
				wektor_ruchu.x = wektor_ruchu.x * -1;
			}
			else if (x_p > szer_obiekt * 48) {
				wektor_ruchu.x = wektor_ruchu.x * -1;
			}

			if (y_p < wys_obiekt) {
				wektor_ruchu.y = wektor_ruchu.y * -1;
			}
			else if (y_p > wys_obiekt * 30) {
				wektor_ruchu.y = wektor_ruchu.y * -1;
			}

			// odbicie piłki od rakietki
			if (y_p + wys_obiekt > wys_obiekt*28.5 && x_p + (szer_obiekt/2) > polozenie.x && x_p + (szer_obiekt / 2) < polozenie.x + (4 * szer_obiekt)) {
				if (x_p + (szer_obiekt / 2) > polozenie.x && x_p + (szer_obiekt / 2) < polozenie.x + czesc_rakietki) {
					wektor_ruchu.x = -3.9685;
					wektor_ruchu.y = -1.5;
				}
				else if (x_p + (szer_obiekt / 2) > polozenie.x + czesc_rakietki && x_p + (szer_obiekt / 2) < polozenie.x + (2 * czesc_rakietki)) {
					wektor_ruchu.x = -3;
					wektor_ruchu.y = -3;
				}
				else if (x_p + (szer_obiekt / 2) > polozenie.x + (2*czesc_rakietki) && x_p + (szer_obiekt / 2) < polozenie.x + (3 * czesc_rakietki)) {
					wektor_ruchu.x = 0;
					wektor_ruchu.y = -3;
				}
				else if (x_p + (szer_obiekt / 2) > polozenie.x + (3 * czesc_rakietki) && x_p + (szer_obiekt / 2) < polozenie.x + (4 * czesc_rakietki)) {
					wektor_ruchu.x = 3;
					wektor_ruchu.y = -3;
				}
				else if (x_p + (szer_obiekt / 2) > polozenie.x + (4 * czesc_rakietki) && x_p + (szer_obiekt / 2) < polozenie.x + (5 * czesc_rakietki)) {
					wektor_ruchu.x = 3.9685;
					wektor_ruchu.y = -1.5;
				}

			}


			x_p += wektor_ruchu.x;
			y_p += wektor_ruchu.y;

			pilka.setPosition(x_p, y_p);
			okno_aplikacja.draw(pilka);
			okno_aplikacja.draw(ob1);

			/* wyswietlenie blokow
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 15; j++) {
					okno_aplikacja.draw(vector_bloki[i][j]);
				}

			}



			// wypisanie na ekran obramowania planszy
			for (int i = 0; i < 30; i++) {
				for (int j = 0; j < 50; j++) {
					okno_aplikacja.draw(vector_sciana[i][j]);

				}
			}
			okno_aplikacja.draw(vector_sciana[0][0]);


			okno_aplikacja.display();


		}
		else if (okno_gry == 2) {

		}



   }*/
}

