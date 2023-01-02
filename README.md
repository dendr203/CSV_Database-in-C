# CSV_Database-in-C
V tomto readme souboru najdete stručné vysvětlení k fungování mého projektu do předmětu UPR v prvním semestru. Za úkol jsem dostal naprogramovat "lidl" excel pro práci s CSV databázemi.

## Fukce programu
Celý program je rozdělen do více souborů:
- **start.c**
  - zde se oveřuje text, napsaný při spuštění programu
  - také je zde funkce *stats* která spočítá počet řádků a sloupců ve vstupním souboru

- **exit.c**
  - v tomto souboru jsou funkce pro ukončení programu, hlavně tedy pro zpátečné uvolnění paměti
 
- **funkcions.c**
  - tady jsou všechny potřebné funkce pro hlavní fungování programu
  
- **main.c**
  - hlavní program
  
  
Program si neprve načte ze zadaného textu při spuštění programu vstupní soubor a načte si ho do dynamicky alokovaného 2D pole. Pokud se zadá špatný vstupní soubor, který neexistuje, nebo nelze otevřít, program se ukončí a vypíše chybovou hlášku.

Pro práci s celou databází jsem použil dynamicky alokované 2D pole, protože se mi s ním lépe pracovalo než se strukturou. I když v tomto případě by bylo použití obojího velmi podobné. Tím, že jsem používat 2D pole, tedy si ukládám do každého řádku pole jednotlivý řádek csv souboru, tak jsem poté při další manipulaci s polem potřeboval občas řádky rozdělit. Při použítí strtok na tyto řádky v poli se mi tyto řádky zničily (strtok je rozdělil, ale na konci nechal jen jedno slovo), proto, když jsem manipuloval s řádky v poli, tak jsem si nejdříve vytvořil pomocné 1D dynamicky alokované pole, které jsem pro každý řádek realokoval a na něj jsem mohl použít strtok, bez toho aniž by mi to zničilo moje originální 2D pole.

Po načtení inputu a zkontrolování všech potřebných věcí se spustí hlavní smyčka. Zde může uživatel psát všechny příkazy, které program dovede. Před provedením jednotlivých příkazů si vždy zkontroluje, zda je příkaz zapsán správně, aby poté nedošlo k chybám. Uvedené příkazy jsou:
  - addrow - ověří se, zda zadáváte spravný počet sloupců a řádek se přídá do 2D pole
  - addcol - ověří se, zda zadáváte správný počet řádků a sloupec se přidá do 2D pole
  - average - ověří si, zda zadáváte existující sloupec a vypíše výsledek v desetinném čísle s jednou desetinonu přestností
            - nečíselné hodnoty se převedou na 0
  - max - stejné jako average, jen se najde maximum ve sloupci
  - min - stejné jako max, jen hledá minimum (zde jsem pro prvotní porovnání použil maximální hodnotu 32b intiger čísla)
  - sum - sečte hodnoty zadaného sloupce
  - exit - ukončí hlavní smyčku
  
 Pokud v hlavní smyčce napíšete cokoli jiného program vám oznámí že příkaz neexistuje. Jedinné ukončení souboru je příkazem **exit**.
 Po ukončení smyčky se upravené 2D pole vpíše do námi na začátku specifikovaného souboru, program uvolní všechnu svou pamět a ukončí se.

