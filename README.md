# Digitální Electronika 2 - PROJEKT
Systém pro měření/ovládání/vizualizace prostředí tropických rostlin. Cílem tohoto projektu je vytvořit automatický systém pro zajištění vhodných podmínek pro pěstování tropických rostlin. Všechny komponenty kromě půdního senzoru jsou propojeny skrze I2C sériovou sběrnici.
## Členové týmu

* Petr Kaplan
* Marek Ivan
* Jakub Křivánek
* Miroslav Trchalík

## Popis Hardwaru
Použitý hardware:
* Deska Arduino Uno
* I2C teplotní a vlhkostní senzor DHT12
* Půdní analogový vlhkoměr s antikorozní sondou v2.0
* I2C OLED displej 1,3" 128 x 64
* Chladící ventilátor - 5V, 30 mm
* Senzor intenzity osvětlení BH1750
* NMOS tranzistor IRF540 TO-220
* Externí zdroj 5,4 V
* Bílá LED dioda
* Červená(IR) dioda
* Ochranné rezistory
* Tlačítka s aretací
* Kabely a propojovací pole

<br>

<div align="center">
 
 ![schéma zapojení](https://github.com/marek8l/DE2_projekt/blob/main/images/schema_zapojeni.jpg)
</div>
<div align="center"><i>obrázek č. 1 - Schéma zapojení</i></div>

### Senzor půdní vlhkosti (Půdní analogový vlhkoměr s antikorozní sondou v2.0)

Půdní senzor je připojen k analogovému vstupu A0. Jelikož senzor posílá pouze analogová data je nutné převést analogová data na digitální data pomocí ADC převodníku (ADC knihovna). Získaná digitální data jsou dále zpracována a využívána k určení stavu vlhkosti půdy. Aktuální stav vlhkosti je zobrazen na OLED displeji, stejně tak jako v konzoli pomocí sběrnice UART. V případě dostatečné vlhkosti je zobrazeno na displeji stav "WET". V opačném případě je zobrazen stav "DRY" a také se zobrazí výstražná zpráva "WATER ME" a dojde k blikání displeje.<br>

<div align="center">
 
![analog_senzor](https://github.com/marek8l/DE2_projekt/blob/main/images/analog_senzor.jpg)
<br>
<i>obrázek č. 2 - Senzor půdní vlhkosti</i>
</div>

### Teplotní a vlhkostní senzor DHT12

Pro snímání teploty a vlhkosti ovzduší používáme senzor DHT12. Tento senzor posílá digitální data, která dále zpracováváme a následně zobrazujeme na OLED displeji. Na OLED displeji tak zobrazujeme aktuální hodnoty teploty v °C a vlhkost ovzduší v %. Podle vyhodnocení těchto hodnot dojde při velké teplotě ke spuštění ventilátoru, který sníží teplotu. Naopak při nízké teplotě, dojde k rozsvícení LED diody, která reprezentuje IR ohřívač (vyhřívání). Již zmíněný ventilátor je napájen pomocí externího zdroje s napětím 5,4V. K Jeho ovládání byl použit NMOS tranzistor IRF540 TO-220, který je připojen k digitálnímu vstupu 9.<br>

<div align="center">
 
![Teplotní a vlhkostní senzor DHT12](https://github.com/marek8l/DE2_projekt/blob/main/images/dht12.jpg)
<br>
<i>obrázek č. 3 - Teplotní a vlhkostní senzor DHT12</i>
<br>
![Ventilátor](https://github.com/marek8l/DE2_projekt/blob/main/images/ventilátor.jpg)
<br>
<i>obrázek č. 4 - DC ventilátor (5V)</i>
<br>

</div>

### Senzor intenzity osvětlení BH1750

Dále snímáme intenzitu osvětlení pomocí senzoru intenzity osvětlení BH1750, získaná data zobrazujeme na OLED displeji. Tato data jsou používána k ovládání další LED diody (digitální PIN 10), která slouží k navýšení intenzity osvětlení. V případě nízké intenzity osvětlení dojde k rozsvícení diody. Pokud je hodnota intenzity osvětlení dostačující, dioda zůstává vypnuta.<br>

<div align="center">
 
![Senzor intenzity osvětlení](https://github.com/marek8l/DE2_projekt/blob/main/images/bh1750.jpg)
<br>
<i>obrázek č. 5 - Senzor intenzity osvětlení</i>
<br>
</div>

### OLED displej 
OLED displej s řadičem SH1106 se využívá k zobrazení všech hodnot naměřených veličin. Také se používá k zobrazení hodnot, které chceme nastavit jako hranice, u kterých dojde ke spuštění procesů jako jsou chlazení, ohřev atd.<br>

<div align="center">
 
![OLED displej](https://github.com/marek8l/DE2_projekt/blob/main/images/oled.jpg)
<br>
<i>obrázek č. 6 - OLED displej </i>
<br>
</div>

### NMOS tranzistor IRF540 TO-220
NMOS tranzistor plní funkci spínače. Při překročení thresholdu se vyšle signál z PINu 9 na GATE tranzistoru, což otevře tranzistor, a tím se spustí ventilátor.

<div align="center">

![IRF540](https://github.com/marek8l/DE2_projekt/blob/main/images/IFR540.jpg)
<br>
<i>obrázek č. 7 - NMOS IRF540 </i>
<br>
</div>

## Popis Softwaru
<div align="center">
</div>
<br>
Knihovny a src soubory:<br>

* [ADC knihovna](https://github.com/marek8l/DE2_projekt/tree/main/tropical_plants/lib/adc)<br>

* [GPIO knihovna](https://github.com/marek8l/DE2_projekt/tree/main/tropical_plants/lib/gpio)<br>

* [OLED knihovna](https://github.com/marek8l/DE2_projekt/tree/main/tropical_plants/lib/oled)<br>

* [TWI knihovna](https://github.com/marek8l/DE2_projekt/tree/main/tropical_plants/lib/twi)<br>

* [UART knihovna](https://github.com/marek8l/DE2_projekt/tree/main/tropical_plants/lib/uart)<br>

* [Include soubor timer.h](https://github.com/marek8l/DE2_projekt/blob/main/tropical_plants/include/timer.h)<br>

* [Incude soubor config.h](https://github.com/marek8l/DE2_projekt/blob/main/tropical_plants/include/config.h)<br>

* [SRC soubor(main)](https://github.com/marek8l/DE2_projekt/blob/main/tropical_plants/src/main.c)<br><br><br>

Stavový diagram:<br>

<div align="center">
 
![Diagram](https://github.com/marek8l/DE2_projekt/blob/main/images/vdiagram.jpg)

<br>
<i>obrázek č. 8 - Stavový diagram </i>
<br>
</div>

## Instrukce a fotky

1.	Zasuneme kapacitní senzor vlhkosti půdy do půdy tak, aby nad povrchem byla viditelná pouze indikační ponorová čára.
2.	Zapojíme zbývající senzory (DHT12, OLED, BH1750).
3.	Vhodně zapojíme diody reprezentující IR ohřívač a umělé osvětlení.
4.	Dále připojíme řídící tranzistor IRF540 TO-220, který je potřebný k ovládání ventilátoru.
5.	Připojíme ventilátor k externímu zdroji a k řídícímu tranzistoru.
6.	Ventilátor nastavíme do vhodné chladící polohy.
7.	V dalším kroku můžeme připojit tlačítka s aretací k ventilátoru a LED diodě reprezentující umělé osvětlení, pomocí kterých můžeme trvale vypnout dané prvky například při potřebě částečné manipulace s rostlinou, která nevyžaduje vypnutí celého systému.
8.	Připojíme desku Arduino k napájecímu zdroji.
9.	Spustíme program.
10.	Pro úpravu hranic pro sepnutí externích zařízení, upravíme makra v souboru config.h.
<br>

<div align="center">
<br>
 
![ilustrační fotografie](https://github.com/marek8l/DE2_projekt/blob/main/images/ilustracni_foto.jpg)
<br>
<i>obrázek č. 9 - Ilustrační fotografie</i>
<br>

[![Video ukázka funkce projektu](https://github.com/marek8l/DE2_projekt/blob/main/images/uvodni_fotka.png)](https://youtube.com/shorts/QAH41s4pTNU?feature=share)
<br>
<i>Ilustrační video</i>
<br>
</div>

<br>


##  Reference a nástroje

1. [Datasheet of Ambient Light Sensor I2C](https://www.mouser.com/datasheet/2/348/bh1750fvi-e-186247.pdf?srsltid=AfmBOopXsNbrXH805bf72KnvAvOjhtHIuWU8JnSg7seawDr_eOblLK1S)<br>
2. [Tomas Fryza's DE2 repository](https://github.com/tomas-fryza/avr-course)<br>
3. [Datasheet of Soil moisture sensor v2.0](https://dratek.cz/docs/produkty/1/1862/1531824339.pdf)<br>
4. [Datasheet of ATmega328p](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)<br>
5. [Datasheet of Temperature and Humidity sensor DHT12](https://www.datasheet4u.com/datasheet-pdf/Aosong/DHT12/pdf.php?id=1147840)<br>
6. [Source of all pictures used in Hardware description](https://dratek.cz/)<br>
7. [Datasheet of NMOS transistor IRF540 TO-220](https://www.vishay.com/docs/91021/irf540.pdf)<br>
8. [Source about plant environment](https://www.rostlinky.cz/blog/tropicke-rostliny-navod-na-pestovani.html)<br>
9. [Tool for state diagram](https://app.diagrams.net/)<br>
