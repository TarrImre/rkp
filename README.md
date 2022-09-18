# Rendszerközeli programozás
## Feladat
C nyelven megírni egy programot, amely egy 1 bit színmélységű bmp fájlt hoz
létre.
A bmp fájl egy véletlenszerűen változó mennyiség időbeli változását
szemléltető grafikont ábrázol.
A program kétféle üzemmódban képes működni:
-Küldő: előállítja az adatokat
-Fogadó: ábrázolja az adatokat
Egyetlen program, de két folyamat. Folyamatok közötti kommunikáció
megvalósítása, vagy fájlkezeléssel vagy socket (hálózaton) keresztül. 
A program egy .bmp kiterjesztésű képet fog generálni.
A programot chart néven kell elindítani, másképp nem fog működni.
gcc controller.c main.c –o chart
Miután helyes nevet adtunk meg, a felhasználó az alábbi parancssori
argumentumokat használhatja:
--version
--help
-send
-receive
-file
-socket
|               | File | Socket |
| ------------- | ------------- | ------------- |
| Fogadó | ./chart -file -receive  | ./chart -socket -receive  |
| Küldő  | ./chart -file -send  | ./chart -socket -send  |