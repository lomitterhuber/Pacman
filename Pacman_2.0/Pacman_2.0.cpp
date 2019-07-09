// Pacman.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include "BildschirmRoutinen.h"

#define MAX_GEISTER 10
#define CURSOR_TASTER 224
#define CURSOR_UP 72
#define CURSOR_DOWN 80
#define CURSOR_LEFT 75
#define CURSOR_RIGHT 77
#define SPACE 32

//========================================== Globale Variablen =======================================

int iLeben = 3;
int iBlinken = 0;
int iSpiel_Ende = 1;
int iZ_Punkt;
int iS_Punkt;
int iPunktestand = 0;
int iPunktestand_gesamt = 0;
int iPunktestand_max = 0;

//========================================== Funktionen ==============================================

//------------------------------------------Klasse Geist--------------------------------------------

class Geist
{
private:
	int iZ;
	int iS;
	int iR;
	int iZaehler_fuer_Richtungsaenderung;

public:
	Geist();
	void Geist_Init(void);
	void Geist_Anzeigen(void);
	void Geist_Loeschen(void);
	void Geist_Bewegen(void);

};

Geist::Geist(void)
{
	iZ = 0;
	iS = 0;
	iR = 0;
	iZaehler_fuer_Richtungsaenderung = 0;
}

void Geist::Geist_Init()
{
	int iIndex;
	char cData;

	for (iIndex = 0; iIndex < MAX_GEISTER; iIndex++)
	{

		for (;;)
		{
			// zufälllige Position vergeben
			iZ = Zufall(5, 20);
			iS = Zufall(20, 60);
			iR = Zufall(0, 3);

			//prüfen, ob Position frei
			cData = GetCharZS(iZ, iS);
			if (cData == ' ') break;
		}
	}
}

void Geist::Geist_Anzeigen(void)
{
	GotoZS(iZ, iS);
	printf("%c", 'G');
}

void Geist::Geist_Loeschen(void)
{
	GotoZS(iZ, iS);
	printf(" ");
}

void Geist::Geist_Bewegen(void)
{
	int iZneu = iZ;
	int iSneu = iS;
	char cData;

	if (iZaehler_fuer_Richtungsaenderung > 14)
	{
		iR = Zufall(0, 3);
		iZaehler_fuer_Richtungsaenderung = 0;
	}

	switch (iR)
	{
	case 0: iZneu = iZneu - 1; break;
	case 1: iSneu = iSneu - 1; break;
	case 2: iSneu = iSneu + 1; break;
	case 3: iZneu = iZneu + 1; break;
	default: iR = Zufall(0, 3); break;
	}

	cData = GetCharZS(iZneu, iSneu);
	if (cData == ' ')
	{
		iZ = iZneu;
		iS = iSneu;
		iZaehler_fuer_Richtungsaenderung++;
	}
	else
	{
		if (cData == 'P')
		{
			iLeben--;
			iBlinken = 5;
			iZ = iZneu;
			iS = iSneu;
		}
		else
		{
			iR = Zufall(0, 3);
		}

		iZaehler_fuer_Richtungsaenderung = 0;
	}
}

//------------------------------------------Punkt---------------------------------------------------

void Punktplatzierung(void)
{
	int cData;
	for (;;)
	{
		// zufälllige Position vergeben
		iZ_Punkt = Zufall(5, 20);
		iS_Punkt = Zufall(5, 75);

		//prüfen, ob Position frei
		cData = GetCharZS(iZ_Punkt, iS_Punkt);
		if (cData == ' ')
		{
			GotoZS(iZ_Punkt, iS_Punkt);
			printf("*");
			break;
		}
	}
}

void Punkt_Anzeigen(void)
{
	GotoZS(iZ_Punkt, iS_Punkt);
	printf("*");
}

void Punkt_Loeschen(void)
{
	GotoZS(iZ_Punkt, iS_Punkt);
	printf(" ");
}

//------------------------------------------Klasse Spieler------------------------------------------

class Spieler
{
private:
	int iZ;
	int iS;

public:
	int iTaste;
	Spieler();
	void Spieler_Init(void);
	void Spieler_Abfragen(void);
	void Spieler_Anzeigen(void);
	void Spieler_Loeschen(void);
	void Spieler_Bewegen(void);
};

Spieler::Spieler(void)
{
	iZ = 0;
	iS = 0;
}

void Spieler::Spieler_Init(void)
{
	int cData;
	for (;;)
	{
		// zufälllige Position vergeben
		iZ = Zufall(5, 20);
		iS = Zufall(5, 75);

		//prüfen, ob Position frei
		cData = GetCharZS(iZ, iS);
		if (cData == ' ')
		{
			break;
		}
	}
}

void Spieler::Spieler_Abfragen(void)
{
	if (_kbhit() != 0)
	{
		iTaste = _getch();

		if (iTaste == 224)
		{
			iTaste = _getch();
		}
	}
}

void Spieler::Spieler_Anzeigen(void)
{
	GotoZS(iZ, iS);
	printf("%c", 'P');
}

void Spieler::Spieler_Loeschen(void)
{
	GotoZS(iZ, iS);
	printf(" ");
}

void Spieler::Spieler_Bewegen(void)
{
	int iZ_Spieler_neu = iZ;
	int iS_Spieler_neu = iS;
	char cData;

	switch (iTaste)
	{
	case 72: iZ_Spieler_neu = iZ - 1; break;
	case 75: iS_Spieler_neu = iS - 1; break;
	case 77: iS_Spieler_neu = iS + 1; break;
	case 80: iZ_Spieler_neu = iZ + 1; break;
	default: break;
	}

	cData = GetCharZS(iZ_Spieler_neu, iS_Spieler_neu);
	if (cData == 32)
	{
		iZ = iZ_Spieler_neu;
		iS = iS_Spieler_neu;
	}
	else
	{
		if (cData == 'G')
		{
			iLeben--;
			iBlinken = 5;
			iZ = iZ_Spieler_neu;
			iS = iS_Spieler_neu;
		}
		if (cData == '*')
		{
			iZ = iZ_Spieler_neu;
			iS = iS_Spieler_neu;
			iPunktestand++;
			Punktplatzierung();
		}
	}


	GotoZS(iZ, iS);
	printf("%c", 'P');
}

//------------------------------------------sonstige Funktionen-------------------------------------

void Menue(void)
{
	GotoZS(15, 55);
	printf("Pacman\n");
	GotoZS(16, 55);
	printf("======\n\n");
	GotoZS(18, 43);
	printf("Zum Starten beliebige Taste druecken...");
	_getch();
	ClrScr();
}

void Labrinth_zeichnen()
{
	//printf("01234567890123456789012345678901234567890123456789012345678901234567890123456789\n\r");
	printf("\n                                   Labyrinth\n\n\r");
	printf("   ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\r");
	printf("   ++                                      +++                                   ++\n\r");
	printf("   +                   +++                                     +++                +\n\r");
	printf("   +                                                                              +\n\r");
	printf("   +                                                                              +\n\r");
	printf("   +                                        +                                     +\n\r");
	printf("   +                                        +                                     +\n\r");
	printf("   +                                        +                                     +\n\r");
	printf("   +                                        +                                     +\n\r");
	printf("   +                                        +                                     +\n\r");
	printf("   +                    +                  +++                   +                +\n\r");
	printf("   +++                 +++      ++++++++++++++++++++++++++      +++             +++\n\r");
	printf("   +                    +                  +++                   +                +\n\r");
	printf("   +                                        +                                     +\n\r");
	printf("   +                                        +                                     +\n\r");
	printf("   +                                        +                                     +\n\r");
	printf("   +                                        +                                     +\n\r");
	printf("   +                                        +                                     +\n\r");
	printf("   +                                                                              +\n\r");
	printf("   +                                                                              +\n\r");
	printf("   +                   +++                                     +++                +\n\r");
	printf("   ++                                      +++                                   ++\n\r");
	printf("   ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\r");
}

void Status_Anzeigen(void)
{
	GotoZS(27, 5);
	printf("Punktestand: %i", iPunktestand);
	GotoZS(28, 5);
	printf("Lebenspunkte: %i", iLeben);
}

void Endstatus(void)
{
	ClrScr();
	iPunktestand_gesamt = iPunktestand + iPunktestand_gesamt;
	if (iPunktestand > iPunktestand_max) iPunktestand_max = iPunktestand;
	GotoZS(14, 55);
	printf("Game Over");
	GotoZS(16, 55);
	printf("Punktestand: %i", iPunktestand);
	GotoZS(17, 55);
	printf("Highscore: %i", iPunktestand_max);
	GotoZS(18, 55);
	printf("gesamter Punktestand: %i", iPunktestand_gesamt);
	GotoZS(20, 55);
	printf("Noch eine Runde spielen?");
	GotoZS(21, 59);
	printf("Ja (1)");
	GotoZS(22, 59);
	printf("Nein (beliebige Taste)");
	GotoZS(24, 55);
	scanf_s("%i", &iSpiel_Ende);
	if (iSpiel_Ende == 1)
	{
		iLeben = 3;
		iPunktestand = 0;

	}
}

//==========================================Hauptprogramm===========================================

int main()
{

	int iIndex;
	int Geister_Im_Einsatz;
	Geist oGeist[MAX_GEISTER];
	Spieler oSpieler;

	Geister_Im_Einsatz = MAX_GEISTER;
	Menue();

	InitZufall();

	while (iSpiel_Ende == 1)
	{
		GotoZS(0, 0);
		ClrScr();

		Labrinth_zeichnen();
		for (iIndex = 0; iIndex < Geister_Im_Einsatz; iIndex++)
		{
			oGeist[iIndex].Geist_Init();
		}

		oSpieler.Spieler_Init();
		Punktplatzierung();

		for (iIndex = 0; iIndex < Geister_Im_Einsatz; iIndex++)
		{
			oGeist[iIndex].Geist_Anzeigen();
		}
		for (iIndex = 0; iIndex < 5; iIndex++)
		{
			oSpieler.Spieler_Anzeigen();
			Delay(100);
			oSpieler.Spieler_Loeschen();
			Delay(100);
		}


		while (iSpiel_Ende == 1)
		{
			for (iIndex = 0; iIndex < Geister_Im_Einsatz; iIndex++)
			{
				oGeist[iIndex].Geist_Anzeigen();
			}

			oSpieler.Spieler_Anzeigen();
			
			Punkt_Loeschen();
			if (iBlinken > 0)
			{
				Delay(25);
				/*
				oSpieler.Spieler_Loeschen();
				Delay(50);
				*/
			}
			else
			{
				Delay(50);
			}

			if (iBlinken > 0)
			{
				oSpieler.Spieler_Loeschen();
				Delay(50);
			}

			for (iIndex = 0; iIndex < Geister_Im_Einsatz; iIndex++)
			{
				oGeist[iIndex].Geist_Loeschen();
				oGeist[iIndex].Geist_Bewegen();
				oGeist[iIndex].Geist_Anzeigen();
			}
			if (iBlinken > 0)
			{
				oSpieler.Spieler_Anzeigen();
				iBlinken--;
			}

			Punkt_Anzeigen();
			if (iBlinken > 0)
			{
				Delay(25);
			}
			else
			{
				Delay(50);
			}

			oSpieler.Spieler_Abfragen();
			oSpieler.Spieler_Loeschen();
			oSpieler.Spieler_Bewegen();
			oSpieler.Spieler_Anzeigen();
			oSpieler.iTaste = 0;			// Rücksetzen von iTaste (notwendig aufgrund Globalitaet)
			if (iLeben <= 0)
			{
				iSpiel_Ende = 0;
			}
			Status_Anzeigen();
		}
		Endstatus();
	}

	return 0;
}

