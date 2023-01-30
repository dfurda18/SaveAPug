# SaveAPug
This is a block-break game where you must free trapped pugs.
It has three types of powerups: Multiball, Extra Life, and Trapped Pug. You must catch the required amount of pugs to finish the level.
The levels are created in separated files so it is easy to make more.
The format is:
```
<number of blocks>
<number of pugs needed to save>
<type of block> <x> <y>
... Repeated for the <number of blocks>
```
The block numbers are:
```
0 = blue
1 = green | Multiball
2 = grey
3 = black | Trapped pug
4 = red | Extra Life
5 = yellow
```
A level editor is included in this project in a separate folder. The controls are the following:
```
0 = blue tile
1 = green tile
2 = grey tile
3 = black tile
4 = red tile
5 = yellow tile
s = Save
l = load
ESC = quit
```

The levels will be saved and loaded at the level.txt file just rename it to <level number>.txt and paste it in the Levels folder. Make sure that all levels are named in sequence.
