#pragma once
#include <SFML/Graphics.hpp>

#define max_numer_wyborow_wstep 2
#define max_numer_wyborow_menu 4
#define max_numer_wyborow_koniec 5
#define max_numer_zasady 18

using namespace sf;

class Napisy {
protected:
	int indeks_wybranego_przycisku;
	Font czcionka;
	FloatRect wysrotkowanie_tekstu;

public:
	Napisy(float rozdzielczosc_x, float rozdzielczosc_y) {
		if (!czcionka.loadFromFile("./grafika/czcionka_1/Raleway-LightItalic.ttf")) {

		}

		indeks_wybranego_przycisku = 0;
	};
};

class Wstep : public Napisy {
private:
	Text tekst_wstep[max_numer_wyborow_wstep];

public:
	Wstep(float rozdzielczosc_x, float rozdzielczosc_y) : Napisy::Napisy(rozdzielczosc_x, rozdzielczosc_y) {
		if (!czcionka.loadFromFile("./grafika/czcionka_1/Raleway-LightItalic.ttf")) {

		}

		tekst_wstep[0].setFont(czcionka);
		tekst_wstep[0].setFillColor(Color::Red);
		tekst_wstep[0].setCharacterSize(150);
		tekst_wstep[0].setStyle(Text::Bold);
		tekst_wstep[0].setString("ARCANOID");
		wysrotkowanie_tekstu = tekst_wstep[0].getLocalBounds();
		tekst_wstep[0].setOrigin(wysrotkowanie_tekstu.width / 2, wysrotkowanie_tekstu.height / 2);
		tekst_wstep[0].setPosition(Vector2f(rozdzielczosc_x / 2.0f, rozdzielczosc_y / (max_numer_wyborow_wstep + 1) * 1));
		
		tekst_wstep[1].setFont(czcionka);
		tekst_wstep[1].setFillColor(Color::White);
		tekst_wstep[1].setString("Nacisnij Enter...");
		wysrotkowanie_tekstu = tekst_wstep[1].getLocalBounds();
		tekst_wstep[1].setOrigin(wysrotkowanie_tekstu.width / 2, wysrotkowanie_tekstu.height / 2);
		tekst_wstep[1].setPosition(Vector2f(rozdzielczosc_x / 2.0f, rozdzielczosc_y / (max_numer_wyborow_wstep + 1) * 2));

		indeks_wybranego_przycisku = 0;
	}

	~Wstep() { };

	void wypisz(RenderWindow &okno_aplikacja) {
		for (int i = 0; i < max_numer_wyborow_wstep; i++)
			okno_aplikacja.draw(tekst_wstep[i]);
	};

	int wybierz_przycisk() {
		return indeks_wybranego_przycisku;
	}
};

class Menu : public Napisy {
private:
	Text tekst_menu[max_numer_wyborow_menu];

public:
	Menu(float rozdzielczosc_x, float rozdzielczosc_y) : Napisy::Napisy(rozdzielczosc_x, rozdzielczosc_y) {
		if (!czcionka.loadFromFile("./grafika/czcionka_1/Raleway-LightItalic.ttf")) {

		}

		tekst_menu[0].setString("Graj");
		//tekst_menu[1].setString("gra dla 2 graczy");
		tekst_menu[1].setString("rekordy");
		tekst_menu[2].setString("zasady gry");
		tekst_menu[3].setString("wyjscie");
		
		for (int i = 0; i < max_numer_wyborow_menu; i++) {
			tekst_menu[i].setFont(czcionka);
			if (i > 0)
				tekst_menu[i].setFillColor(Color::White);
			else
				tekst_menu[i].setFillColor(Color::Red);
			wysrotkowanie_tekstu = tekst_menu[i].getLocalBounds();
			tekst_menu[i].setOrigin(wysrotkowanie_tekstu.width / 2, wysrotkowanie_tekstu.height / 2);
			tekst_menu[i].setPosition(Vector2f(rozdzielczosc_x / 2.0f, rozdzielczosc_y / (max_numer_wyborow_menu + 1) * (i + 1)));
		}

		indeks_wybranego_przycisku = 0;
	}

	~Menu() { };

	void wypisz(RenderWindow &okno_aplikacja) {
		for (int i = 0; i < max_numer_wyborow_menu; i++) 
			okno_aplikacja.draw(tekst_menu[i]);
	};

	void strzalka_w_gore() {
		if (indeks_wybranego_przycisku - 1 >= 0) {
			tekst_menu[indeks_wybranego_przycisku].setFillColor(Color::White);
			indeks_wybranego_przycisku--;
			tekst_menu[indeks_wybranego_przycisku].setFillColor(Color::Red);
		}
	};

	void strzalka_w_dol() {
		if (indeks_wybranego_przycisku + 1 < max_numer_wyborow_menu) {
			tekst_menu[indeks_wybranego_przycisku].setFillColor(Color::White);
			indeks_wybranego_przycisku++;
			tekst_menu[indeks_wybranego_przycisku].setFillColor(Color::Red);
		}
	};

	int wybierz_przycisk() {
		return indeks_wybranego_przycisku;
	}
};


class Koniec : public Napisy {
private:
	Text tekst_koniec[max_numer_wyborow_koniec];

public:
	Koniec(float rozdzielczosc_x, float rozdzielczosc_y) : Napisy::Napisy(rozdzielczosc_x, rozdzielczosc_y) {
		if (!czcionka.loadFromFile("./grafika/czcionka_1/Raleway-LightItalic.ttf")) {

		}
		
		tekst_koniec[0].setString("KONIEC GRY");
		tekst_koniec[1].setString("restart");
		tekst_koniec[2].setString("zapisz wynik");
		tekst_koniec[3].setString("wyjscie");
		
		for (int i = 0; i < max_numer_wyborow_koniec; i++) {
			tekst_koniec[i].setFont(czcionka);
			if (i > 0)
				tekst_koniec[i].setFillColor(Color::White);
			else {
				tekst_koniec[i].setFillColor(Color::Red);
				tekst_koniec[0].setCharacterSize(150);
				tekst_koniec[0].setStyle(Text::Bold);
			}
			wysrotkowanie_tekstu = tekst_koniec[i].getLocalBounds();
			tekst_koniec[i].setOrigin(wysrotkowanie_tekstu.width / 2, wysrotkowanie_tekstu.height / 2);
			tekst_koniec[i].setPosition(Vector2f(rozdzielczosc_x / 2.0f, rozdzielczosc_y / (max_numer_wyborow_koniec + 1) * (i + 1)));
		}

		indeks_wybranego_przycisku = 0;
	}

	~Koniec() { };

	void wypisz(RenderWindow &okno_aplikacja) {
		for (int i = 0; i < max_numer_wyborow_koniec; i++) 
			okno_aplikacja.draw(tekst_koniec[i]);
	};

	void strzalka_w_gore() {
		if (indeks_wybranego_przycisku - 1 >= 1) {
			tekst_koniec[indeks_wybranego_przycisku].setFillColor(Color::White);
			indeks_wybranego_przycisku--;
			tekst_koniec[indeks_wybranego_przycisku].setFillColor(Color::Red);
		}
	};

	void strzalka_w_dol() {
		if (indeks_wybranego_przycisku + 1 < max_numer_wyborow_koniec) {
			tekst_koniec[indeks_wybranego_przycisku].setFillColor(Color::White);
			indeks_wybranego_przycisku++;
			tekst_koniec[indeks_wybranego_przycisku].setFillColor(Color::Red);
		}
	};

	int wybierz_przycisk() {
		return indeks_wybranego_przycisku;
	}
};

class Zasady_gry : public Napisy {
private:
	Text zasady[max_numer_zasady];

public:
	Zasady_gry(float rozdzielczosc_x, float rozdzielczosc_y) : Napisy::Napisy(rozdzielczosc_x, rozdzielczosc_y) {
		if (!czcionka.loadFromFile("./grafika/czcionka_1/Raleway-LightItalic.ttf")) {

		}

		zasady[0].setFont(czcionka);
		zasady[0].setFillColor(Color::Red);
		zasady[0].setCharacterSize(50);
		zasady[0].setStyle(Text::Bold);
		zasady[0].setString("ZASADY GRY");
		wysrotkowanie_tekstu = zasady[0].getLocalBounds();
		zasady[0].setOrigin(wysrotkowanie_tekstu.width / 2, wysrotkowanie_tekstu.height / 2);
		zasady[0].setPosition(Vector2f(rozdzielczosc_x / 2.0f, rozdzielczosc_y / (max_numer_zasady + 1) * 0.6));

		zasady[1].setString("Celem gry jest niedopuszczenie do wydostania sie pileczki poza obszar gry");
		zasady[2].setString("oraz odbijanie jej w taki sposob, aby zbic wszystkie bloki");
		zasady[3].setString("rozmieszczone wewnatrz pola gry.");
		zasady[4].setString("Gracz zaczyna gre z 3 szansami (zyciami).");
		zasady[5].setString("Gdy pilka wydostanie sie poza obszar gry gracz traci 1 zycie.");
		zasady[6].setString("Gra konczy sie w momencie gdy gracz straci wszystkie zycia.");
		zasady[7].setString("Za zbicie kazdego bloku graczowi przyznawane sa punkty.");
		zasady[8].setString("Bloki maja 3 rozne kolory:");
		zasady[9].setString("zolty - 1 zbicie, niebieski - 2 zbicia, czerwony - 3 zbicia.");
		zasady[10].setString("Gdy gracz zbije wszystki bloki, przechodzi do kolejnego poziomu.");
		zasady[11].setString("Trudnosc poziomu wzrasta wraz z jego numerem.");
		zasady[12].setString("Z blokow wylatuja bonusy, ktore gracz moze zbierac.");
		zasady[13].setString("Dobre bonusy (kwadraciki koloru zielonego) - przyspieszenie rakietki,");
		zasady[14].setString("rozszerzenie rakietki, extra zycie, extra punkty, przenikanie pileczki.");
		zasady[15].setString("Zle bonusy (kwadraciki koloru bialego) - zwolnienie rakietki,");
		zasady[16].setString("zmniejszenie rakietki, ujemne zycie, ujemne punkty.");
		
		for (int i = 1; i < max_numer_zasady; i++) {
			zasady[i].setFont(czcionka);
			zasady[i].setCharacterSize(30);
			zasady[i].setFillColor(Color::White);
			wysrotkowanie_tekstu = zasady[i].getLocalBounds();
			zasady[i].setOrigin(wysrotkowanie_tekstu.width / 2, wysrotkowanie_tekstu.height / 2);
			zasady[i].setPosition(Vector2f(rozdzielczosc_x / 2.0f, rozdzielczosc_y / (max_numer_zasady + 1) * (i + 1)));
		}

		zasady[17].setFont(czcionka);
		zasady[17].setFillColor(Color::Green);
		zasady[17].setCharacterSize(30);
		zasady[17].setString("Powrot do menu ->");

		indeks_wybranego_przycisku = 0;
	}

	~Zasady_gry() { };

	void wypisz(RenderWindow &okno_aplikacja) {
		for (int i = 0; i < max_numer_zasady; i++) {
			okno_aplikacja.draw(zasady[i]);
		}
	};

	int wybierz_przycisk() {
		return indeks_wybranego_przycisku;
	}
};