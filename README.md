# Digital Electronics 2 - PROJEKT
Measurement/Control/Visualization of the environment for tropical plants

## Team members

* Petr Kaplan
* Marek Ivan
* Jakub Křivánek
* Mirek Trchalík

## Hardware description
Použitý hardware:
* I2C teplotní a vlhkostní senzor DHT12
* Půdní analogový vlhkoměr s antikorozní sondou v2.0
* I2C OLED displej 1,3" 128 x 64
* Chladící ventilátor - 5V, 30 mm
* Senzor intenzity světla BH1750

* Zde bude fotka celého zapojení

Všechny komponenty kromě půdního senzoru jsou propojeny skrze I2C sériovou sběrnici. Půdní senzor je připojen k analogovému vstupu A0, jelikož získáváme analogová data, je nutné je převést na digitální pomocí ADC převdníku. Získaná digitální data jsou dále zpracována a využívána k určení stavu vlhkosti půdy. Aktuální stav vlhkosti je zobrazen na OLED displeji, stejně tak jako v konzoli pomocí sběrnice UART. V případě dostatečné vlhkosti je zobrazeno na displeji stav "WET". V opačném případě je zobrazen stav "DRY" a také se zobrazí výstražná zpráva  "WATER ME" a dojde k blikání displeje. Pro snímání teploty a vlhkosti ovzduší používáme senzor DHT12. Tento senzor posílá digitální data, která zpracováváme a následně zobrazujeme na OLED displeji aktuální hodnoty teploty v °C a vlhkost ovzduší v %. Podle vyhodnocení těchto hodnot, dojde při velké teplotě k spuštění ventilátoru, který by měl snížit teplotu. Naopak při nízké teplotě, dojde k rozsvícení LED diody, která reprezentuje vyhřívání.



Describe your implementation and include block or circuit diagram(s).

## Software description

Include flowcharts/state diagrams of your algorithm(s) and direct links to the source files in PlatformIO `src` or `lib` folders. Present the libraries you used in the project.

## Instructions and photos

Describe how to use the application. Add photos or videos of your application.

## References and tools

1. Put here the references and online tools you used.
2. ...
