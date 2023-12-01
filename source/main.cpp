#include <iostream>
#include "file_reader.h"
#include "caff_parser.h"
#include "gif.h"
#include "metadata.h"

using namespace std;

/* Running parser requires 3 params
       -  1. param: relative path to the input file
       -  2. param: relative path to where gif will be generated
       -  3. param: relative path to where a json with the additional data will be generated (creator, etc.)
*/
int main(int argc, char const *argv[]) {
    // check whether we got all params
    if (argc != 4) {
        cout << "4 parameters expected but received " + to_string(argc) << endl;
        return -1;
    }

    caffFileData caffData;
    CAFF caff;
    try {
        caffData = readCAFFFile(argv[1]);
        caff = parseCAFFFile(caffData);
    }
    catch (const std::exception& e) {
        cerr << e.what();
        return -1;
    }
    catch (...) {
        cerr << "Some unknown error occured!";
        return -1;
    }

    GifWriter gifWriter;
    bool gifSuccess = GifBegin(&gifWriter, argv[2], caff.ciffBlocks[0].width, caff.ciffBlocks[0].heigth, caff.ciffBlocks[0].duration);
    if (!gifSuccess) {
        cerr << "Error when creating gif file!";
        return -1;
    }
    for (uint64_t i = 0; i < caff.ciffBlocks.size(); i++) {
        gifSuccess = GifWriteFrame(&gifWriter, caff.ciffBlocks[i].image.data(), caff.ciffBlocks[i].width, caff.ciffBlocks[i].heigth, caff.ciffBlocks[i].duration);
        if (!gifSuccess) {
            cerr << "Error when creating gif file!";
            return -1;
        }
    }
    gifSuccess = GifEnd(&gifWriter);
    if (!gifSuccess) {
        cerr << "Error when creating gif file!";
        return -1;
    }

    try {
        createCAFFMetadata(argv[3], caff);
    }
    catch (const std::exception& e) {
        cerr << e.what();
        return -1;
    }
    catch (...) {
        cerr << "Some unknown error occured!";
        return -1;
    }

    return 0;
}

// TODO: a captionben milyen karakter megengedett?
// TODO: operator[] helyett lehet jobb lenne az at f�ggv�ny. De ezt egyel�re hagyjuk meg a statikus elemz�nek...

/*
TODO: Van sok warning, jellemz�en lefel� castol�s miatti lehets�ges adatveszt�s miatt

"a fejleszt�s sor�n a biztons�ggal kapcsolatos r�szekre, a saj�t terveitek megval�s�t�s�ra, valamint a megfelel� tesztel�sre tudjatok f�kusz�lni."
"A projekt c�lja a tanult input valid�ci�s m�dszerek alkalmaz�sa a gyakorlatban, egy biztons�gkritikus szoftverkomponens fejleszt�se kapcs�n."
"A parser alapos biztons�gi tesztel�se javasolt, mivel az �rt�kel�s sor�n is ellen�rizni fogjuk, hogy k�pes-e megfelel�en kezelni rosszul form�zott f�jlokat. A webshop abban az esetben sem �llhat le, ha valaki sz�nd�kosan hib�s f�jlt pr�b�l felt�lteni."
Threats:
    A CIFF/CAFF Parser sosem fejezi be a feldolgoz�st �s nem v�laszol t�bb k�r�sre. - A saj�t f�ggv�nyeimben a ciklusok fut�s�nak mindig van fels� hat�ra, �gy ott elvileg nem lehet ilyen gond. A gif.h-ban viszont elvileg el�fordulhat...
Biztons�gi funkcionalit�sok:
    Bement valid�ci� �s filterez�s whitelist m�dszerrel - DONE
    Regex ker�l�se - DONE
    Id�t�ll�p�s mechanizmus kritikus komponensekben
    Biztons�gos mem�riakezel�s nat�v komponensekben
    Komponensek lelt�raz�sa, friss komponensek haszn�lat�nak ellen�rz�se (titkos�t� algoritmusok, protokollok, programk�nyvt�rak)
    Injection elleni int�zked�sek (prepared statements, code review)
Tesztel�si terv
    Code Review: SAST eszk�z haszn�lata javasolt, ak�r az eg�sz k�dra (mivel j�l sk�l�z�dik), de f�leg a kritikusnak jel�lt funkci�k k�djaira �s a f�jlfeldolgoz�ra.
    szimbolikus elemz�s
    fuzzing (mutation-based)

El�ad�sok: 1, 3, 5
Kell/tudunk m�g valami logol�st csin�lni azon t�l, hogy ki�rjuk hogy milyen kiv�tel j�tt?
TODO-k!
WARNINGOK!
*/
