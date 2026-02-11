<i>

# Vanha kunnon possu... <b>ISONA!</b>

<img src="proto.gif" alt="alt" width="50%">

## SKEMA
Vanha tuttu possusalaman skema, paitsi tässä tuplasti ledejä 8x8 multiplex setupilla.  
Fuse asetus ajaa RESET pinnin IO pinniksi, jonka jälkeen koodin uudelleen puskeminen ei enään onnistu.  

<img src="skema.svg" alt="alt" width="100%">

## Protolevy mk2
| Etupuoli <sub>tirsk</sub> | Takapuoli <sub>tirsk</sub> |
|:---|:---                |
| <img src="etu.jpg" alt="alt" width="100%">  | <img src="taka.jpg" alt="alt" width="100%"> 


## OSALUETTELO
|KPL | MITÄ               | Huomiot    |
|:---|:---                |---:     |
| 1  | Attiny 861A SOIC   |       **U** malli ainakin toimii  |
| 64 | 5 mm DIP LED         | malli kappaleessa XL-502UBC ledit  |
| 8  | 110 Ohm 1206        |    Eipä siinä oikeastaan ole väliä    |
| 1  | 10 uF SMD           |    Virtalähteen virran tasoitusta varten (Ei pakko)    |

| Muuta?  |
|:---|
| Joku johto virransyöttä varten |
| Virtalähde 5V DC |
| Fläshäykseen Arduino ja 6 pinninen rima |
| 2 puolinen piirilevy, mallikappele on jyrsitty |
| Läpivientiniittejä, esim. 0.4 mm niitit 0.8 mm porauksille ja 0.8 mm 1.2 mm...  |



## Koodi
```bash
# Koodin kääntäminen
cd src/
avr-gcc -mmcu=attiny861 main.c -I./ -Os -DF_CPU=8000000UL
```


``` bash
# Fuse asetukset
# https://www.engbedded.com/fusecalc/
avrdude -c avrips -p t861 -P /dev/ttyUSB0 -b 19200 -U lfuse:w:0xe2:m -U hfuse:w:0x5f:m
```

## Fuse asetuksien nollaaminen
Tyliin joku 12V high voltage fuse resetter setuppi tai laita vaan uusi pirii tilalle :D
