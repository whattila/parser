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
// TODO: operator[] helyett lehet jobb lenne az at függvény. De ezt egyelõre hagyjuk meg a statikus elemzõnek...

/*
TODO: Van sok warning, jellemzõen lefelé castolás miatti lehetséges adatvesztés miatt

"a fejlesztés során a biztonsággal kapcsolatos részekre, a saját terveitek megvalósítására, valamint a megfelelõ tesztelésre tudjatok fókuszálni."
"A projekt célja a tanult input validációs módszerek alkalmazása a gyakorlatban, egy biztonságkritikus szoftverkomponens fejlesztése kapcsán."
"A parser alapos biztonsági tesztelése javasolt, mivel az értékelés során is ellenõrizni fogjuk, hogy képes-e megfelelõen kezelni rosszul formázott fájlokat. A webshop abban az esetben sem állhat le, ha valaki szándékosan hibás fájlt próbál feltölteni."
Threats:
    A CIFF/CAFF Parser sosem fejezi be a feldolgozást és nem válaszol több kérésre. - A saját függvényeimben a ciklusok futásának mindig van felsõ határa, így ott elvileg nem lehet ilyen gond. A gif.h-ban viszont elvileg elõfordulhat...
Biztonsági funkcionalitások:
    Bement validáció és filterezés whitelist módszerrel - DONE
    Regex kerülése - DONE
    Idõtúllépés mechanizmus kritikus komponensekben
    Biztonságos memóriakezelés natív komponensekben
    Komponensek leltárazása, friss komponensek használatának ellenõrzése (titkosító algoritmusok, protokollok, programkönyvtárak)
    Injection elleni intézkedések (prepared statements, code review)
Tesztelési terv
    Code Review: SAST eszköz használata javasolt, akár az egész kódra (mivel jól skálázódik), de fõleg a kritikusnak jelölt funkciók kódjaira és a fájlfeldolgozóra.
    szimbolikus elemzés
    fuzzing (mutation-based)

Elõadások: 1, 3, 5
Kell/tudunk még valami logolást csinálni azon túl, hogy kiírjuk hogy milyen kivétel jött?
TODO-k!
WARNINGOK!
*/
