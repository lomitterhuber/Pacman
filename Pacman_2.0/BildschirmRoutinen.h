// -----------------------------------------------------------------------------------------------------------------
// Ansteuerungsroutinen für das FSST-Board
// Stand: 2016-03-05
// DI Mag(FH) Klingler
//
// Achtung: Visual Studio
// 1) Library Ws2_32.lib muss inkludiert werden
//    Project => Project Properties => Linker :: Input Additional Dependencies - im Dropdown-Menu hinzu fügen
// 2) Precompiled Header deaktivieren
//    > entweder beim Erstellen des Projektes oder
//    > Project => Properties => C/C++ => Precompiled Header :: Precompiled Headers = Not Using Precompiled Headers
// -----------------------------------------------------------------------------------------------------------------

#ifndef BILDSCHIRMSTEUERUNG_H
#define BILDSCHIRMSTEUERUNG_H

void Delay     (int iMilliSekunden);                           // verzögern
void InitZufall(void);										   // Zufallsgenerator initialisieren
int  Zufall    (int iMin, int iMax);						   // Zufallszahl zwischen min und max erzeugen

void GotoXY    (short iX, short iY );						   // Cursor an die Bildschirm-Position XY
char GetCharXY (int iX, int iY);                               // Einlesen des Zeichens an der Bildschirm-Position XY
void GotoZS    (short iZeile, short iSpalte);    			   // Cursor an die Bildschirm-Position Zeile|Spalte
char GetCharZS (int iZeile, int iSpalte);                      // Einlesen des Zeichens an der Bildschirm-Position Zeile|Spalte
void ClrScr    (void);                                         // Bildschirm löschen
void SetColor(int iFG, int iBG);							   // Console-Farbe: iFG .. Text, iBG .. Hintergrund

#define BLACK 0
#define DARKBLUE 1
#define DARKGREEN 2
#define DARKCYAN 3
#define DARKRED 4
#define DARKMAGENTA 5
#define DARKYELLOW 6
#define GRAY 7
#define DARKGRAY 8
#define BLUE 9
#define GREEN 10
#define CYAN 11
#define RED 12
#define MAGENTA 13
#define YELLOW 14
#define WHITE 15

#endif
