# PROCEDURE DE COMPILATION

Shoot Em Up Game - 2D

- Cloner le projet complet:
  	```
	git clone https://github.com/oumarsadjo/ShootEmUp
	cd ShootEmUp
	mkdir build && cd build
	cmake ..
	make
	./ShootEm
  	```
### UTILISATION
- La touche de la direction de gauche __‘<’ pour diriger le joueur vers la gauche__ ;
- La touche de la direction de droite  __‘>’ pour diriger le joueur vers la droite__ ;
- La touche __‘S’ pour tirer les balles du joueur__ ;
- La touche __‘R’ pour relancer le jeu__ ;
- La touche __‘X’ pour quitter le jeu__ ;

Pour faire tourner ce jeux sous linux, merci de suivre les etapes suivantes:

__Etape 1: Installation de la bibliotheque SFML adaptee aux jeux 2D:__

 	sudo apt-get install libsfml-dev
- Note:	S'il vous demande le package, telecharger le en suivant ce lien-->
	-Lien vers le package a telecharge: https://www.sfml-dev.org/download.php

__Etape 2: Installer le package .NET__
	-La commande pour l'installer : 
	
	sudo apt update
	sudo apt install apt-transport-https
	sudo apt update
	sudo apt install dotnet-sdk
	
- Le lien pour choisir le package specifique a votre distribution:
https://learn.microsoft.com/fr-fr/dotnet/core/install/linux

__Etape 3:Rassurez-vous d'avoir le CMakeFiles.txt dans le meme dossier
	-Suivez les instructions suivantes:__
	
	mkdir build && cd build
	cmake ..
	make
 	./ShootEm
	
- Source des sons: https://pixabay.com/fr/sound-effects/search/jeu/
- Source des images: https://www.pngegg.com/en/png-ymocz
- Source des background: https://www.freepik.com/free-photos-vectors/2d-background
