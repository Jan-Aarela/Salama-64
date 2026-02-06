<i>

# Vanha kunnon possu... <b>ISONA</b>

Esimerkiksi kämpän seinälle loistamaan.

! WIP !

  <details>
  <summary><b> SKEEMA  </b></summary>
<img src="skeema.svg" alt="alt" width="100%">
</details>

<details>
  <summary><b> LEVYT  </b></summary>
<!-- <img src="skeema.svg" alt="alt" width="100%"> -->
WIP
</details>

## OSALUETTELO
|KPL | MITÄ               | Esim    |
|:---|:---                |---:     |
| 1  | Attiny a861 SOIC   |         |
| 64 | 5mm sin. DIP LED   |         |
| 8  | 110 Ohm 1206        |         |
| 1  | 10 uF SMD           |         |

| Muuta?  |
|:---|
| Joku johto virransyöttä varten |
| Virtalähde 5V DC |
| 2 lyhyttä virtakaapelia levyjen yhdistämiseen|
| Fläshäykseen Arduino ja 6-PIN rima |
| 2 puoleisia piirilevyjä esim. jyrsimällä |
| Jotain materiaalia taustapanelia varten |


``` bash
# Fuse asetukset
# https://www.engbedded.com/fusecalc/
avrdude -c avrips -p t861 -P /dev/ttyUSB0 -b 19200 -U lfuse:w:0xe2:m -U hfuse:w:0x5f:m
```

``` bash
# Fuse asetuksien nollaaminen 
```
