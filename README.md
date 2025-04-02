# FROG-VENTURE: Adventure Of The Frog

Dieses lustige Spiel zum Zeitvertreib handelt von einem kleinen Frosch, der gerne grüne Kristalle futtert. Doch aufgepasst: Merkwürdige rote Seeigel mit pieksigen Stacheln schwirren durch die Gegend. Schaffst du es, ihnen geschickt auszuweichen und den neuen Highscore aufzustellen?


## Starten des Spiels

Um das Spiel zu kompilieren, führe folgende Befehle aus, während du dich im root-Ordner des Projektes befindest:

```bash
cmake -B build
cmake --build build
./build/bin/main
```

## Spielmechanik

- **Kristalle essen:** Fütter den Frosch mit den Kristallen, indem du ihn zu ihnen hin bewegst. Kristalle geben so viele Punkte wie die Zahl, die auf ihnen angezeigt wird. Deinen Score siehst du oben links. Die grünen Kristalle schrumpfen mit der Zeit, also beeil dich, sie einzufangen! Je wertvoller die Kristalle sind, desto schneller schrumpfen sie.
- **Seeigeln ausweichen:** Vermeide das Berühren von Seeigeln, da du dadurch ein Leben (kleine grüne Herzen in der oberen Ecke) verlierst. Wenn du keine Leben mehr übrig hast, ist das Spiel vorbei.
- **Herzen einsammeln:** Seltener als die grünen Kristalle spawnen zufällig kleine Herz-Kristalle. Diese geben dir zusätzliche Leben.

_Die Grafiken sind KI-generiert._


