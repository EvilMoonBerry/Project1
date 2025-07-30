# Käyttöjärjestelmä ja systeemiohjelmoinnin kurssin projekti 1 warmup to C and Unix programming

## Tämän tehtävän tarkoitus on tehdä ohjelma joka lukee käyttäjältä syötetiedoston jonka sisällön ohjelma joko tulostaa käyttäjlle takaperin tai kirjottaa ulostulotiedostoon takaperin.
Ohjelma käy läpi syötetiedostona ja käy sen läpi rivi kerrallaan. Rivit lisätään linkitettyyn listaan ja tämä linkitetty lista tulostetaan takaperin käyttäjälle tai toiseen tiedostoon riippuen käyttäjän valinnoista. 

Kääntäjä:
```
gcc -o reverse reverse.c -Wall -Werror
```

Tukee komentoja:
- ./reverse
* ./reverse input.txt
+ ./reverse input.txt output.txt
