// -----------------------------------------------------------------------------------------------------------------
// Ansteuerungsroutinen für das FSST-Board
// Stand: 2016-11-1
// DI Mag(FH) Klingler
//
// Achtung: Code::Blocks
// Library C:\Program Files (x86)\CodeBlocks\MinGW\lib\libws2_32.a muss inkludiert werden
// Settings => Compiler => Linker Settinges :: add
//
// Achtung: Visual Studio
// 1) Library Ws2_32.lib muss inkludiert werden
//    Project => Project Properties => Linker :: Input Additional Dependencies - im Dropdown-Menu hinzu fügen
// 2) Precompiled Header deaktivieren
//    > entweder beim Erstellen des Projektes oder
//    > Project => Properties => C/C++ => Precompiled Header :: Precompiled Headers = Not Using Precompiled Headers
// -----------------------------------------------------------------------------------------------------------------

#include "BildschirmRoutinen.h"
#include <time.h>
#include <Ws2tcpip.h>

// -----------------------------------------------------------------------------------------------------------------
// unterschiedliche String-Befehle zwischen Code::Blocks und Visual Studio
// -----------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
	#define STRCPY(a,b) strcpy_s(a,100,b)
    #define STRCAT strcat_s
    #define SPRINTF sprintf_s
    #define SSCANF sscanf_s
#else
    #define STRCPY strcpy
    #define STRCAT strcat
    #define SPRINTF sprintf
    #define SSCANF sscanf
#endif // _MSC_VER

// -----------------------------------------------------------------------------------------------------------------
/// <summary>
/// allgemeine Funktion (kein Board n&ouml;tig) <br>
/// <br>
/// Verz&ouml;gerung um Millisekunden [ms]
/// </summary>
/// <param name="iMilliSekunden">Verz&ouml;gerungszeit</param>
//-----------------------------------------------------------------------------------------------------------------
void Delay (int iMilliSekunden)
{
    unsigned __int64 iTicksProSekunde;
    unsigned __int64 iStartTicks;
    unsigned __int64 iAktuelleTicks;

    QueryPerformanceFrequency((LARGE_INTEGER*)&iTicksProSekunde);
    QueryPerformanceCounter((LARGE_INTEGER*)&iStartTicks);

    for (;;)
    {
        QueryPerformanceCounter((LARGE_INTEGER*)&iAktuelleTicks);

        if (iAktuelleTicks>(iStartTicks+iTicksProSekunde/1000*iMilliSekunden)) break;
    }
}

// -----------------------------------------------------------------------------------------------------------------
/// <summary>
/// allgemeine Funktion (kein Board n&ouml;tig) <br>
/// <br>
/// Initialisierung des Zufallsgenerators (am Programmstart) 
/// </summary>
/// <param name="iMin">Minimum</param>
/// <param name="iMax">Maximum</param>
/// <returns>Zufallszahl</returns>
//-----------------------------------------------------------------------------------------------------------------
void InitZufall(void)
{
	srand((unsigned int)time(NULL));
}

// -----------------------------------------------------------------------------------------------------------------
/// <summary>
/// allgemeine Funktion (kein Board n&ouml;tig) <br>
/// <br>
/// Liefert eine Zufallszahl Minimum <= Zufallszahl <= Maximum.
/// </summary>
/// <param name="iMin">Minimum</param>
/// <param name="iMax">Maximum</param>
/// <returns>Zufallszahl</returns>
//-----------------------------------------------------------------------------------------------------------------
int Zufall (int iMin, int iMax)
{
	return (int) (iMin+rand()%(iMax+1-iMin));
}

// -----------------------------------------------------------------------------------------------------------------
/// <summary>
/// Bildschirmsteuerung (kein Board n&ouml;tig) <br>
/// <br>
/// Liefert den ASCII-Code des Zeichens an der Bildschirmposition [iX|iY].
/// </summary>
/// <param name="iX">X-Koordinate (0-79)</param>
/// <param name="iY">Y-Koordinate (0-24)</param>
/// <returns>ASCII-Code des Zeichens</returns>
//-----------------------------------------------------------------------------------------------------------------
char GetCharXY (int iX, int iY)
{
	COORD coScrn;
	DWORD dwRead;
	char szRead[10];
	HANDLE hStdOut;

	coScrn.X = iX;
	coScrn.Y = iY;
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    #ifdef _MSC_VER
    ReadConsoleOutputCharacter(hStdOut,(LPWSTR) szRead, 1, coScrn, &dwRead);
	#else
    ReadConsoleOutputCharacter(hStdOut,(LPSTR) szRead, 1, coScrn, &dwRead);
	#endif

	return (szRead[0]);
};

// -----------------------------------------------------------------------------------------------------------------
/// <summary>
/// Bildschirmsteuerung (kein Board n&ouml;tig) <br>
/// <br>
/// Setzt den Cursor an die Position [iX|iY].
/// </summary>
/// <param name="iX">X-Koordinate (0-79)</param>
/// <param name="iY">Y-Koordinate (0-24)</param>
//-----------------------------------------------------------------------------------------------------------------
void GotoXY( short iX, short iY )
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE) ;
    COORD oPosition = { iX, iY } ;

    SetConsoleCursorPosition( hStdout, oPosition ) ;
}

// -----------------------------------------------------------------------------------------------------------------
/// <summary>
/// Bildschirmsteuerung (kein Board n&ouml;tig) <br>
/// <br>
/// Setzt den Cursor an die Position [iSpalte|iZeile].
/// </summary>
/// <param name="iZeile">Zeile (0-24)</param>
/// <param name="iSpalte">Spalte (0-79)</param>
//-----------------------------------------------------------------------------------------------------------------
void GotoZS(short iZeile, short iSpalte)
{
    GotoXY(iSpalte,iZeile);
}

// -----------------------------------------------------------------------------------------------------------------
/// <summary>
/// Bildschirmsteuerung (kein Board n&ouml;tig) <br>
/// <br>
/// Liefert den ASCII-Code des Zeichens an der Bildschirmposition [iSpalte|iZeile].
/// </summary>
/// <param name="iZeile">Zeile (0-24)</param>
/// <param name="iSpalte">Spalte (0-79)</param>
/// <returns>ASCII-Code des Zeichens</returns>
//-----------------------------------------------------------------------------------------------------------------
char GetCharZS(int iZeile, int iSpalte)
{
    return GetCharXY(iSpalte,iZeile);
};

// -----------------------------------------------------------------------------------------------------------------
/// <summary>
/// Bildschirmsteuerung (kein Board n&ouml;tig) <br>
/// <br>
/// L&ouml;scht den Bildschirm.
/// </summary>
//-----------------------------------------------------------------------------------------------------------------
void ClrScr (void)
{
    system ("cls");
}

void SetColor(int iFG, int iBG)
{
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, iFG+16*iBG);
};