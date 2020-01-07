#pragma once
#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdio>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;
using namespace sf;

int tabela_rakordow(RenderWindow &okno_aplikacja, Event &zdarzenie, int rozdzielczosc_x, int rozdzielczosc_y, int &wybor);

void zeruj_bonus(rakietka &Rakieta, pilka &Pilka, float &szer_obiekt, bool &czy_kolizja_blok);

void brak_kolizji_blok(blok &Blok, pilka &Pilka, int &pkt, int &ilosc_blokow);

void kolizja_blok(blok &Blok, pilka &Pilka, int &pkt,int &ilosc_blokow);

void kolizja_rakietka(rakietka &Rakietka, pilka &Pilka);

bool kolizja_bonus_rakietka(bonus &blok_bonus, rakietka &Rakietka);

void ramka_stworz(float szerokosc_obiekt, float wysokosc_obiekt, int rozdzielczosc_x, int rozdzielczosc_y, vector<vector<obiekt_neutralny>> &ramka);

void pasek_zycia_aktualizacja(pasek_zycia &pasek_gracz, pilka &Pilka, int &rozdzielczosc_y, bool &rozpoczecie_gry);

string podaj_nazwe_gracza(RenderWindow &okno_aplikacja, Event &zdarzenie, int rozdzielczosc_x, int rozdzielczosc_y);

int koniec_gry_porazka(RenderWindow &okno_aplikacja, Event &zdarzenie, int rozdzielczosc_x, int rozdzielczosc_y, int &punkty, int &poziom, string &nazwa_gracza);

int nastepny_poziom(RenderWindow &okno_aplikacja, Event &zdarzenie, int rozdzielczosc_x, int rozdzielczosc_y, int &punkty, int &poziom, string &nazwa_gracza, int &wybor);

void zapis_do_pliku(string nazwa_gracza, int punkty, int poziom);

void gra_pauza(RenderWindow &okno_aplikacja, Event &zdarzenie, int rozdzielczosc_x, int rozdzielczosc_y, int &wybor);