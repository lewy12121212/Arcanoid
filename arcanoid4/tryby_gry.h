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


void gra_tryb_gracz1(int &rozdzielczosc_x, int  &rozdzielczosc_y, RenderWindow &okno_aplikacja, float &szer_obiekt, float &wys_obiekt, Event &zdarzenie, int &wybor, string &nazwa_gracza, int &poziom, int &pkt);

//void gra_tryb_gracz2(int &rozdzielczosc_x, int  &rozdzielczosc_y, RenderWindow &okno_aplikacja, float &szer_obiekt, float &wys_obiekt, Event &zdarzenie);

void zasady_gry_funkcja(RenderWindow &okno_aplikacja, Event &zdarzenie, int &wybor, string &nazwa_gracza);

int menu_glowne_funkcja(RenderWindow &okno_aplikacja, Event &zdarzenie, int &wybor, string &nazwa_gracza);

