# TGA_Picture_Editor

Editor for .tga files that can do a variety of blends and changes to pixels

## Functionality

* Read in a number .TGA files in a binary format
* Process the image data store within those files in a variety of ways using the designed blends
* Write out new .TGA files in the same binary format

### Different blending modes

* Vertical Flip
* Multiply blend
* Subtract blend
* Screen blend
* Overlay blend
* AddChange
* Multiply change
* Split red
* Split blue
* Split green
* Merge

To learn more about these blending modes:
* http://www.simplefilter.de/en/basics/mixmods.html

## TGA File Format

### File Header

|ID Length                   |1 byte          |Size of the Image ID field         |
|Color Map Type              |1 byte          |Is a color map included?           |
|Image Type                  |1 byte          |Compressed? True Color? Greyscale? |
|Color Map Specifications    |5 bytes         |2 bytes: Color Map Origin          |
|                            |                |2 bytes: Color Map Length          |
|                            |                |1 byte: Color Map Depth            |
|Image Specification         |10 bytes        |2 bytes: X-origin                  |
|                            |                |2 bytes: Y-origin                  |
|                            |                |2 bytes: Image width               |
|                            |                |2 bytes: Image height              |
|                            |                |1 byte: Pixel depth                |
|                            |                |1 byte: Image Descriptor           |


## File Descriptions

### /examples/

TGA files that are to be tested against to ensure code is working as intended

### /input/

Where to store files that are to be editted

### /output/

Where exported filesa are stored

### Header.cpp / Header.h

Defines the **Header** object that holds information about the TGA's header

### Makefile

Used to compile program

### Pixel.cpp / Pixel.h

Defines the **Pixel** object that holds the RGB values of an individual pixel

### TGAPicture.cpp / TGAPicture.h

Defines the **TGAPicture** object that holds the **Header**, **Pixel**s, and all associated functions, such as blends, exporting TGA images, etc.

### main.cpp

1. Load one or more files from the “input” folder
2. Perform some operation(s) on the loaded file(s)
3. Write the results to a new .TGA file (named part#.tga) in the “output” folder. The “examples” folder has completed versions which you can use to test against your files. If your file is identical to its counterpart in the Examples folder, you’re done with that part!

### Tests
1. Use the Multiply blending mode to combine “layer1.tga” (top layer) with “pattern1.tga” (bottom layer).
2. Use the Subtract blending mode to combine “layer2.tga” (top layer) with “car.tga” (bottom layer). This mode subtracts the top layer from the bottom layer.
3. Use the Multiply blending mode to combine “layer1.tga” with “pattern2.tga”, and store the results temporarily. Load the image “text.tga” and, using that as the top layer, combine it with the previous results of layer1/pattern2 using the Screen blending mode.
4. Multiply “layer2.tga” with “circles.tga”, and store it. Load “pattern2.tga” and, using that as the top layer, combine it with the previous result using the Subtract blending mode.
5. Combine “layer1.tga” (as the top layer) with “pattern1.tga” using the Overlay blending mode.
6. Load “car.tga” and add 200 to the green channel.
7. Load “car.tga” and scale (multiply) the red channel by 4, and the blue channel by 0. This will increase the intensity of any red in the image, while negating any blue it may have.
8. Load “car.tga” and write each channel to a separate file: the red channel should be “part8_r.tga”, the green channel should be “part8_g.tga”, and the blue channel should be “part8_b.tga”
9. Load “layer_red.tga”, “layer_green.tga” and “layer_blue.tga”, and combine the three files into one file. The data from “layer_red.tga” is the red channel of the new image, layer_green is green, and layer_blue is blue.
10. Load “text2.tga”, and rotate it 180 degrees, flipping it upside down.

## Author

* Simon Frank
* linkedin.com/in/simon-frank/
* github.com/SimonBFrank/