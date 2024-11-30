# Digitální Electronika 2 - PROJEKT
Měření/Ovládání/Vizualizace prostředí tropických kytek

## Členové týmu

* Petr Kaplan
* Marek Ivan
* Jakub Křivánek
* Miroslav Trchalík

## Popis Hardwaru
Použitý hardware:
* I2C teplotní a vlhkostní senzor DHT12
* Půdní analogový vlhkoměr s antikorozní sondou v2.0
* I2C OLED displej 1,3" 128 x 64
* Chladící ventilátor - 5V, 30 mm
* Senzor intenzity světla BH1750

* Zde bude fotka celého zapojení
* Připsat Piny k LED atd.
  
<br>
Cílem projektu je vytvořit automatický systém pro zajištění vhodných podmínek pro pěstování tropických rostlin. Všechny komponenty kromě půdního senzoru jsou propojeny skrze I2C sériovou sběrnici.
<br>
## Půdní senzor
Půdní senzor je připojen k analogovému vstupu A0, jelikož získáváme analogová data, je nutné je převést na digitální pomocí ADC převodníku (ADC knihovna). Získaná digitální data jsou dále zpracována a využívána k určení stavu vlhkosti půdy. Aktuální stav vlhkosti je zobrazen na OLED displeji, stejně tak jako v konzoli pomocí sběrnice UART. V případě dostatečné vlhkosti je zobrazeno na displeji stav "WET". V opačném případě je zobrazen stav "DRY" a také se zobrazí výstražná zpráva  "WATER ME" a dojde k blikání displeje. Pro snímání teploty a vlhkosti ovzduší používáme senzor DHT12. Tento senzor posílá digitální data, která zpracováváme a následně zobrazujeme na OLED displeji aktuální hodnoty teploty v °C a vlhkost ovzduší v %. Dále snímáme intenzitu osvětlení pomocí senzoru světla BH1750, získaná data zobrazujeme na OLED displeji.
<br>

a také jsou používána k ovládání další LED diody (digitální PIN 10), která slouží k navýšení intenzity světla. V případě nizké intenzity světla dojde k rozsvícení diody. Pokud je hodnota světla dostačující, dioda zůstává vypnuta.

Podle vyhodnocení těchto hodnot, dojde při velké teplotě k spuštění ventilátoru, který by měl snížit teplotu. Naopak při nízké teplotě, dojde k rozsvícení LED diody, která reprezentuje IR ohřívač (vyhřívání). Již zmíněný ventilátor je napájen pomocí externího zdroje 5,4V a k jeho ovládání byl použit NMOS tranzistor IRF540 TO-220, jeho k digitálnímu vstupu 9.

## Popis Softwaru

Include flowcharts/state diagrams of your algorithm(s) and direct links to the source files in PlatformIO `src` or `lib` folders. Present the libraries you used in the project.

## Instrukce a fotky

Describe how to use the application. Add photos or videos of your application.

##  Reference a nástroje

1. Put here the references and online tools you used.
2. ...
