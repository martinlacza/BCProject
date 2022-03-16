Pre fungovanie programu je potrebne mat nainstalovany najnovsi kompilator MinGW:
http://mingw-w64.org/doku.php

Po nainstalovani sa moze program spustit v Dev C++, Codeblocks, a mal by byt spustitelny aj v Visual Studio.

Ak ho chcete spustit z prikazoveho riadku, treba spustat s standardom c++11. Niektore novsie prikazy sa neskompiluju v starsom standarde
Prikaz potom vyzera takto:
g++ main.cpp -o main.exe -std=c++11

Pri spusteni sa mozu pridat argumenty:
main.exe [pocet vrcholov] [pocet opakovani]

Kvoli dlhsiemu casu ktory je potrebny na uskutocnenie stromov s viac vrcholmi, odporuca sa neprekrocit velkost stromov 100 a pocet opakovani 1000
