# Digitální Electronika 2 - PROJEKT
Systém pro měření/ovládání/vizualizace prostředí tropických rostlin.<br>
Cílem tohoto projektu je vytvořit automatický systém pro zajištění vhodných podmínek pro pěstování tropických rostlin. Všechny komponenty kromě půdního senzoru jsou propojeny skrze I2C sériovou sběrnici.
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
* NMOS tranzistor IRF540 TO-220

<br>

<div align="center">
 
 ![schéma zapojení](https://github.com/marek8l/DE2_projekt/blob/main/schema_zapojeni.jpg)
</div>
<div align="center"><i>obrázek č. 1 - schéma zapojení</i></div>

### Senzor půdní vlhkosti (Půdní analogový vlhkoměr s antikorozní sondou v2.0)

Půdní senzor je připojen k analogovému vstupu A0, jelikož získáváme analogová data, je nutné je převést na digitální pomocí ADC převodníku (ADC knihovna). Získaná digitální data jsou dále zpracována a využívána k určení stavu vlhkosti půdy. Aktuální stav vlhkosti je zobrazen na OLED displeji, stejně tak jako v konzoli pomocí sběrnice UART. V případě dostatečné vlhkosti je zobrazeno na displeji stav "WET". V opačném případě je zobrazen stav "DRY" a také se zobrazí výstražná zpráva  "WATER ME" a dojde k blikání displeje.<br>

<div align="center">
 
![analog_senzor](https://github.com/marek8l/DE2_projekt/blob/main/analog_senzor.jpg) <br>
<i>obrázek č. 2 - Senzor půdní vlhkosti</i>
</div>

### Teplotní a vlhkostní senzor DHT12

Pro snímání teploty a vlhkosti ovzduší používáme senzor DHT12. Tento senzor posílá digitální data, která dále zpracováváme a následně zobrazujeme na OLED displeji aktuální hodnoty teploty v °C a vlhkost ovzduší v %. Podle vyhodnocení těchto hodnot dojde při velké teplotě k spuštění ventilátoru, který sníží teplotu. Naopak při nízké teplotě, dojde k rozsvícení LED diody, která reprezentuje IR ohřívač (vyhřívání). Již zmíněný ventilátor je napájen pomocí externího zdroje s napětím 5,4V. K Jeho ovládání byl použit NMOS tranzistor IRF540 TO-220, který je připojen k digitálnímu vstupu 9.<br>

<div align="center">
 
![Teplotní a vlhkostní senzor DHT12](https://github.com/marek8l/DE2_projekt/blob/main/dht12.jpg) <br>
<i>obrázek č. 3 - Teplotní a vlhkostní senzor DHT12</i> <br>
![Ventilátor](https://github.com/marek8l/DE2_projekt/blob/main/ventil%C3%A1tor.jpg) <br>
<i>obrázek č. 4 - DC ventilátor (5V)</i> <br>

</div>

### Senzor intenzity osvětlení BH1750

Dále snímáme intenzitu osvětlení pomocí senzoru světla BH1750, získaná data zobrazujeme na OLED displeji. Tato data jsou zde používána k ovládání další LED diody (digitální PIN 10), která slouží k navýšení intenzity světla. V případě nizké intenzity světla dojde k rozsvícení diody. Pokud je hodnota světla dostačující, dioda zůstává vypnuta.<br>

![Senzor intenzity osvětlení](https://github.com/marek8l/DE2_projekt/blob/main/bh1750.jpg)
<i>obrázek č. 5 - Senzor intenzity osvětlení</i> 

### OLED displej 
OLED dispej s řadičem SH1106 se využívá k zobrazení všech hodnot změřených veličin. Také se používá k zobrazení hodnot, které chceme nastavit, jako hranice u kterých dojde k spuštění procesů jako jsou chlazení, ohřev atd.<br>

![OLED displej](https://github.com/marek8l/DE2_projekt/blob/main/oled.jpg)
<i>obrázek č. 6 - OLED displej </i> 

## Popis Softwaru

Include flowcharts/state diagrams of your algorithm(s) and direct links to the source files in PlatformIO `src` or `lib` folders. Present the libraries you used in the project.

## Instrukce a fotky

1. Zasuňte kapacitní senzor vlhkosti do půdy tak, aby nad povrchem byla viditelná pouze varovná linie.<br>
2. Připojíme ventilátor k externímu zdroji a nastavíme ho tak, aby správně chladil.<br>
3. Připojte desku Arduino k napájecímu zdroji.<br>
4. V konzoli nastavíme hodnoty na které se nás zeptá UART.<br>
5. Pokud budeme chtít hodnoty změnit, zmáčkneme tlačítko RESET na desce arduina a znovu provedeme krok 4.<br>
 Add photos or videos of your application.<br>

##  Reference a nástroje

1. Put here the references and online tools you used.
2. ...
