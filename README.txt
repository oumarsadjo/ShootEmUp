# PROCEDURE DE COMPILATION

Shoot Em Up Game - 2D

- Cloner le projet complet:
  
	git clone https://github.com/oumarsadjo/ShootEmUp
	cd ShootEmUp
	mkdir build && cd build
	cmake ..
	make
	./ShootEm

Pour faire tourner ce jeux sous linux, merci de suivre les etapes suivantes:

Etape 1: Installation de la bibliotheque SFML adaptee aux jeux 2D:

	-Commande pour l'installer:
 	sudo apt-get install libsfml-dev
- Note:	S'il vous demande le package, telecharger le en suivant ce lien-->
	-Lien vers le package a telecharge: https://www.sfml-dev.org/download.php

Etape 2: Installer le package .NET
	-La commande pour l'installer : 
	
	sudo apt update
	sudo apt install apt-transport-https
	sudo apt update
	sudo apt install dotnet-sdk
	
- Le lien pour choisir le package specifique a votre distribution:
https://learn.microsoft.com/fr-fr/dotnet/core/install/linux

Etape 3:Rassurez-vous d'avoir le CMakeFiles.txt dans le meme dossier
	-Suivez les instructions suivantes:
	
	mkdir build && cd build
	cmake ..
	make
	
	- En suite pour lancer:
 	./ShootEm
	
- Source des sons: https://pixabay.com/fr/sound-effects/search/jeu/
- Source des images: https://www.pngegg.com/en/png-ymocz
- Source des background: https://www.freepik.com/free-photos-vectors/2d-background

