# Rendszerközeli programozás
## Feladat
<p>C nyelven megírni egy programot, amely egy 1 bit színmélységű bmp fájlt hoz
létre.
A bmp fájl egy véletlenszerűen változó mennyiség időbeli változását
szemléltető grafikont ábrázol.</p>
A program kétféle üzemmódban képes működni:<br>
-Küldő: előállítja az adatokat<br>
-Fogadó: ábrázolja az adatokat<br><br>

<p>Egyetlen program, de két folyamat. Folyamatok közötti kommunikáció
megvalósítása, vagy fájlkezeléssel vagy socket (hálózaton) keresztül.
A program egy .bmp kiterjesztésű képet fog generálni.</p>

A programot chart néven kell elindítani, másképp nem fog működni.

**gcc controller.c main.c –o chart**
<br>
Miután helyes nevet adtunk meg, a felhasználó az alábbi parancssori
argumentumokat használhatja:<br>
--version<br>
--help<br>
-send<br>
-receive<br>
-file<br>
-socket<br>
<br>
|               | File | Socket |
| ------------- | ------------- | ------------- |
| Fogadó | ./chart -file -receive  | ./chart -socket -receive  |
| Küldő  | ./chart -file -send  | ./chart -socket -send  |
