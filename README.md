# Projet QCM dynamique

## Présentation du projet

Le système est composé de 3 parties : 

- D'une application mobile
- D'un serveur web
- D'un système de traitement

Le serveur web permettra de configurer et créer les QCM et les participants qui auront leur carton pour répondre. 
De plus, le serveur sera équipé d'une webcam qui permet de prendre en photo les participants avec leur réponses. 
Il affichera les résultats du QCM. L'application mobile lui permettra que de configurer les QCM et les participants. 
La prise de photo s'effectuera à l'aide du capteur de photo et les résultats du QCM s'affichera sur l'application mobile. 
Enfin, le système de traitement d'image permettra d'analyser les cartons afin de déduire les réponses des participants 
qui seront envoyé à une base de donnée dans laquelle le serveur web et l'application mobile pourront faire les requêtes pour récupérer les réponses. 
Les parties du système communiquent au sein d'un réseau local à l'aide d'une borne wifi.

## Le Système de traiatement de l'image

Pour ma part, j'ai dû concevoir dans le système de traitement d'image : 

- il fallait d'abord recevoir et stocker l'image contenant les cartons. Ensuite, 
- j'ai dû coder un module pour localiser les cartons dans l'image et de les reconnaitre. 
- Par ailleurs, une fois localisés, il faut analyser les cartons afin de construire les réponses des participants. 
- Enfin ces réponses seront envoyées à la base de données.

## Installation

- Vérifier bien que vois avez installé [OpenCV](https://opencv.org/)
- Cloner le dépôt sur votre machine locale
- Compiller le programme avec le comilateur de votre choix (C/C++)
- Executer le programme en mettant en argument l'image de votre choix (format PNG/JPG)
