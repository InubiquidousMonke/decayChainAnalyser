# About

decayChainAnalyser is a minimal, (*hopefully*) useful utility for visualizing decay chains of an atom. Fully monochromatic - *definitely* not because I had no idea how else I could visualize such a thing.
Written using the SDL library.
# What's included?
In this repository, you will also find:
- An "Unstable_isotopes.csv" file required for full functionality - The data inside comes from List of nuclides, [https://en.wikipedia.org/w/index.php?title=List_of_nuclides&oldid=1286734358](https://en.wikipedia.org/w/index.php?title=List_of_nuclides&oldid=1286734358) (last visited Apr. 28, 2025)., so this file I'm also making available under GPLv3 - a [CC-BY-SA compatible license](https://creativecommons.org/share-your-work/licensing-considerations/compatible-licenses/). 
- A correctly formatted input type - start.txt - containing the data for the isotope 205At.
# How to use?
## Libraries
- SDL: disclosed later
- SDL_image: [here](https://github.com/libsdl-org/SDL_image?tab=Zlib-1-ov-file)
- SDL_ttf: [here](https://github.com/libsdl-org/SDL_ttf)
## Using the precompiled .exe file

Just make sure all the files and folders included are in the same folder.
## Using the .sln file

For development, I was using the files included in Vulkan. Make sure all the libraries are linked correctly, including the .dll and .lib files.
## Compiling with something else than VS
glhf
For all seriousness though, some help would be appreciated - including some compile errors or irresponsible code decisions.

# Legal

I have literally learned the things required in a day. Please check the data before proper usage (especially if you are using the included csv file).

The license for the SDL library and related are in [zlib-SDL-LICENSE.txt](https://github.com/InubiquidousMonke/decayChainAnalyser/blob/main/zlib-SDL-LICENSE.txt "zlib-SDL-LICENSE.txt")

If you have some issues regarding this project, write an issue. I am open to switching this project to private should it be necessary.