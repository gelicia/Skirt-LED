Code from http://www.arduino.cc/playground/Main/DirectDriveLEDMatrix

Modified to work on an LED array my dad wired up that required the row pins to be flipped.

You will need the same FrequencyTimer2 library available here http://arduino.cc/playground/Code/FrequencyTimer2 

Font implemented taken from http://www.dafont.com/minecraftia.font

pngreader is a file written by [slembcke](https://github.com/slembcke) that takes a black and white PNG file and exports it as an array of 1s and 0s. It's not a 2D array. Run it through the terminal pointing to a PNG like this: './pngreader < ~/Desktop/skirt2/pacman.png'

Several of the tricksy algorithms were also written by [slembcke](https://github.com/slembcke), who declined to putting them on his own github ;) 

Todo : 
Build out more animations and things
Finalize the final run of the program to allow toggling between animations using the arduino's reset button

