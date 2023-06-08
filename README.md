# cabin-control-panel
Ce code permet de gérer le panneau de contrôle de l’installation interactive Hanami.  
Il permet de récupérer les informations des boutons et sélecteurs et de les envoyer en Serial au PC.  
On peut également piloter les différentes LED via des commande en Serial depuis le PC.
## Matériel
 - Teensy 4.1 ([https://www.pjrc.com/store/teensy41.html](https://www.pjrc.com/store/teensy41.html))
 - Un bouton d'arcade ([https://amzn.eu/d/fAatgzp](https://amzn.eu/d/fAatgzp))
 - 2 Slider ([https://fr.aliexpress.com/item/1005002402384760.html](https://fr.aliexpress.com/item/1005002402384760.html))
 - Un encodeur rotatif ([https://fr.aliexpress.com/item/1005005030680929.html](https://fr.aliexpress.com/item/1005005030680929.html))
 - Des bandeaux LED adressables 5V WS2812B ([https://fr.aliexpress.com/item/1005004133293477.html](https://fr.aliexpress.com/item/1005004133293477.html))
 - Des LED adressables 5V WS2812B ([https://fr.aliexpress.com/item/1005002653014067.html](https://fr.aliexpress.com/item/1005002653014067.html))
## La borne
### Face avant (en cours d'assemblage)
![Face Avant](https://ben-le-pirate.guerande-official.fr/control-panel-face.jpg)
### Face arrière
![Face Arrière](https://ben-le-pirate.guerande-official.fr/control-panel-back.jpg)
## Architecture du code
Le code se divise dans plusieurs fichier afin de faciliter la maintenance
Le fichier principal est **cabin-control-panel.ino**.
Tous les autres fichier en **.ino** sont au même niveau.
|Fichier|Utilisation|
|--|--|
| [cabin_control_panel.ino](https://github.com/Hanami-Interactivity/cabin-control-panel/blob/main/cabin_control_panel.ino "cabin_control_panel.ino") | Fichier principal, contient la loop et la gestion du timer |
| [SFX_Manager.ino](https://github.com/Hanami-Interactivity/cabin-control-panel/blob/main/SFX_Manager.ino "SFX_Manager.ino") | Toutes les fonctions relatives aux LED |
| [Serial_Manager.ino](https://github.com/Hanami-Interactivity/cabin-control-panel/blob/main/Serial_Manager.ino "Serial_Manager.ino") | Toutes les fonctions relatives à la communication Serial avec le PC |
| [IO_Manager.ino](https://github.com/Hanami-Interactivity/cabin-control-panel/blob/main/IO_Manager.ino "IO_Manager.ino") | Toute la gestion d'init, lecture et écriture des entrées sortie de la carte |
| [Variables.h](https://github.com/Hanami-Interactivity/cabin-control-panel/blob/main/Variables.h "Variables.h") | Toutes les variables, constantes, class utilisés par le projet |
Les autres fichiers sont là pour facilement setup le projet sur un environnement [Sloeber 4.4.1].(https://eclipse.baeyens.it/)
### Librairies 
| Nom | Utilisation | Lien|
|--|--|--|
| WS2812FX | Permet de gérer les allocations mémoires des LED et intègre déjà une cinquantaine d'effets. | [https://github.com/kitesurfer1404/WS2812FX](https://github.com/kitesurfer1404/WS2812FX) |
| WS2812b_Effect | Developper pour le projet, elle permet de gérer des effets de LED. Elle est basé sur la librairie WS2812FX | [https://github.com/Hanami-Interactivity/WS2812b_Effect](https://github.com/Hanami-Interactivity/WS2812b_Effect) |
| elapsedMillis.h | Permet de gérer le timer de la loop | [https://www.pjrc.com/teensy/td_timing_elaspedMillis.html](https://www.pjrc.com/teensy/td_timing_elaspedMillis.html) |



