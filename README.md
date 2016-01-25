# Editor

Ce projet est un complément de l'engine :
https://github.com/WorldsParticle/Engine

Il contient un context opengl pour le rendu, et propose une interface pour editer une scène.

# Compilation

## Avec Qt creator

Lancez Qt creator et ouvrez le fichier Editor.pro,
ou depuis le terminal :

---shell
qtcreator Editor.pro
---

Puis cliquez sur la flèche verte, ou bien utilisez le raccourci 'ctrl-r'.

## Depuis le terminal (linux only)

---shell
mkdir build ; cd build
qmake ..
make
---
