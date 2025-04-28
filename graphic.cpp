#include <iostream>
#include <fstream>
#include <windows.h>
#include <chrono>
#include <thread>
#include <vector>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
using namespace std;
using namespace chrono;
using namespace this_thread;

unsigned short WIDTH = 800;
unsigned short HEIGHT = 600;
unsigned short oldWidth = 800;
unsigned short oldHeight = 600;

int FPSCap = 60;
bool isFullscreen = false;
bool isRunning = true;
uint64_t frame;
const Uint32 pixelFormat = SDL_PIXELFORMAT_ARGB8888;
const char* WindowName = "Graphics (SDL2)";

void screenshot(SDL_Renderer* render, const char* file) {
	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, WIDTH, HEIGHT, 32, pixelFormat);
	SDL_RenderReadPixels(render, NULL, pixelFormat, surface->pixels, surface->pitch);
	IMG_SavePNG(surface, file);
	SDL_FreeSurface(surface);
}
void screenshotBMP(SDL_Renderer* render, const char* file) {
	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, WIDTH, HEIGHT, 32, pixelFormat);
	SDL_RenderReadPixels(render, NULL, pixelFormat, surface->pixels, surface->pitch);
	SDL_SaveBMP(surface, file);
	SDL_FreeSurface(surface);
}
void screenshotJPG(SDL_Renderer* render, const char* file) {
	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, WIDTH, HEIGHT, 32, pixelFormat);
	SDL_RenderReadPixels(render, NULL, pixelFormat, surface->pixels, surface->pitch);
	IMG_SaveJPG(surface, file, 99);
	SDL_FreeSurface(surface);
}
string roundToAndStringify(double input, uint8_t accuracy) {
	return to_string(int(round(input * pow(10, accuracy)) / pow(10, accuracy))) + "." + to_string(int(round((input - int(input)) * pow(10, accuracy))));
}


vector<string> splitStr(string splitInput, char separator) {
	vector<string> output;
	string buffer;
	bool isString = false;
	for (int i = 0; i < splitInput.length(); i++) {
		if (splitInput[i] == '"') {
			isString ^= true;
		}
		if (splitInput[i] != separator) {
			buffer += splitInput[i];
		}
		else if (isString == false) {
			output.push_back(buffer);
			buffer = "";
		}
		else {
			buffer += splitInput[i];
		}
	}
	if (buffer != "") {
		output.push_back(buffer);
	}
	return output;
}

class atom {
public:
	int16_t Nuclides = 0; // the left upper number in isotope notation
	int16_t AtomicNumber = 0; // the left lower number in normal notation (eg. Cs -> 55, H -> 1)
	uint16_t Identifier = 0;
	void clear() {
		Nuclides = 0;
		AtomicNumber = 0;
	}
	enum AtomicNumberToSymbol {
		H = 1,
		He = 2,
		Li = 3,
		Be = 4,
		B = 5,
		C = 6,
		N = 7,
		O = 8,
		F = 9,
		Ne = 10,
		Na = 11,
		Mg = 12,
		Al = 13,
		Si = 14,
		P = 15,
		S = 16,
		Cl = 17,
		Ar = 18,
		K = 19,
		Ca = 20,
		Sc = 21,
		Ti = 22,
		V = 23,
		Cr = 24,
		Mn = 25,
		Fe = 26,
		Co = 27,
		Ni = 28,
		Cu = 29,
		Zn = 30,
		Ga = 31,
		Ge = 32,
		As = 33,
		Se = 34,
		Br = 35,
		Kr = 36,
		Rb = 37,
		Sr = 38,
		Y = 39,
		Zr = 40,
		Nb = 41,
		Mo = 42,
		Tc = 43,
		Ru = 44,
		Rh = 45,
		Pd = 46,
		Ag = 47,
		Cd = 48,
		In = 49,
		Sn = 50,
		Sb = 51,
		Te = 52,
		I = 53,
		Xe = 54,
		Cs = 55,
		Ba = 56,
		La = 57,
		Ce = 58,
		Pr = 59,
		Nd = 60,
		Pm = 61,
		Sm = 62,
		Eu = 63,
		Gd = 64,
		Tb = 65,
		Dy = 66,
		Ho = 67,
		Er = 68,
		Tm = 69,
		Yb = 70,
		Lu = 71,
		Hf = 72,
		Ta = 73,
		W = 74,
		Re = 75,
		Os = 76,
		Ir = 77,
		Pt = 78,
		Au = 79,
		Hg = 80,
		Tl = 81,
		Pb = 82,
		Bi = 83,
		Po = 84,
		At = 85,
		Rn = 86,
		Fr = 87,
		Ra = 88,
		Ac = 89,
		Th = 90,
		Pa = 91,
		U = 92,
		Np = 93,
		Pu = 94,
		Am = 95,
		Cm = 96,
		Bk = 97,
		Cf = 98,
		Es = 99,
		Fm = 100,
		Md = 101,
		No = 102,
		Lr = 103,
		Rf = 104,
		Db = 105,
		Sg = 106,
		Bh = 107,
		Hs = 108,
		Mt = 109,
		Ds = 110,
		Rg = 111,
		Cn = 112,
		Nh = 113,
		Fl = 114,
		Mc = 115,
		Lv = 116,
		Ts = 117,
		Og = 118
	};
	string getElementSymbol() {
		switch (AtomicNumber) {
		case H: return "H";
		case He: return "He";
		case Li: return "Li";
		case Be: return "Be";
		case B: return "B";
		case C: return "C";
		case N: return "N";
		case O: return "O";
		case F: return "F";
		case Ne: return "Ne";
		case Na: return "Na";
		case Mg: return "Mg";
		case Al: return "Al";
		case Si: return "Si";
		case P: return "P";
		case S: return "S";
		case Cl: return "Cl";
		case Ar: return "Ar";
		case K: return "K";
		case Ca: return "Ca";
		case Sc: return "Sc";
		case Ti: return "Ti";
		case V: return "V";
		case Cr: return "Cr";
		case Mn: return "Mn";
		case Fe: return "Fe";
		case Co: return "Co";
		case Ni: return "Ni";
		case Cu: return "Cu";
		case Zn: return "Zn";
		case Ga: return "Ga";
		case Ge: return "Ge";
		case As: return "As";
		case Se: return "Se";
		case Br: return "Br";
		case Kr: return "Kr";
		case Rb: return "Rb";
		case Sr: return "Sr";
		case Y: return "Y";
		case Zr: return "Zr";
		case Nb: return "Nb";
		case Mo: return "Mo";
		case Tc: return "Tc";
		case Ru: return "Ru";
		case Rh: return "Rh";
		case Pd: return "Pd";
		case Ag: return "Ag";
		case Cd: return "Cd";
		case In: return "In";
		case Sn: return "Sn";
		case Sb: return "Sb";
		case Te: return "Te";
		case I: return "I";
		case Xe: return "Xe";
		case Cs: return "Cs";
		case Ba: return "Ba";
		case La: return "La";
		case Ce: return "Ce";
		case Pr: return "Pr";
		case Nd: return "Nd";
		case Pm: return "Pm";
		case Sm: return "Sm";
		case Eu: return "Eu";
		case Gd: return "Gd";
		case Tb: return "Tb";
		case Dy: return "Dy";
		case Ho: return "Ho";
		case Er: return "Er";
		case Tm: return "Tm";
		case Yb: return "Yb";
		case Lu: return "Lu";
		case Hf: return "Hf";
		case Ta: return "Ta";
		case W: return "W";
		case Re: return "Re";
		case Os: return "Os";
		case Ir: return "Ir";
		case Pt: return "Pt";
		case Au: return "Au";
		case Hg: return "Hg";
		case Tl: return "Tl";
		case Pb: return "Pb";
		case Bi: return "Bi";
		case Po: return "Po";
		case At: return "At";
		case Rn: return "Rn";
		case Fr: return "Fr";
		case Ra: return "Ra";
		case Ac: return "Ac";
		case Th: return "Th";
		case Pa: return "Pa";
		case U: return "U";
		case Np: return "Np";
		case Pu: return "Pu";
		case Am: return "Am";
		case Cm: return "Cm";
		case Bk: return "Bk";
		case Cf: return "Cf";
		case Es: return "Es";
		case Fm: return "Fm";
		case Md: return "Md";
		case No: return "No";
		case Lr: return "Lr";
		case Rf: return "Rf";
		case Db: return "Db";
		case Sg: return "Sg";
		case Bh: return "Bh";
		case Hs: return "Hs";
		case Mt: return "Mt";
		case Ds: return "Ds";
		case Rg: return "Rg";
		case Cn: return "Cn";
		case Nh: return "Nh";
		case Fl: return "Fl";
		case Mc: return "Mc";
		case Lv: return "Lv";
		case Ts: return "Ts";
		case Og: return "Og";
		default: return "Unknown";
		}
	}
};
class decayingAtom : public atom {
public:
	enum decayTypes {
	unknown = 0,
	betaPlus = 1,
	betaMinus = 2,
	alpha = 3,
	spontainousFusion = 10,
	isoFusion = 11,
	electronCapture = 12,
	doubleBetaPlus = 21,
	doubleBetaMinus = 22
};
	vector<int8_t> decayTypes;
	long double halfLife; // in secs
	void clear() {
		halfLife = 0;
		decayTypes.clear();
		Nuclides = 0;
		AtomicNumber = 0;
	}
	void echoDecayTypes() {
		for (int i = 0; i < decayTypes.size(); i++) {
			switch (decayTypes[i]) {
			case betaPlus:
				cout << "Beta+, ";
				break;
			case betaMinus:
				cout << "Beta-, ";
				break;
			case alpha:
				cout << "Alpha, ";
				break;
			case doubleBetaMinus:
				cout << "2Beta-, ";
				break;
			case doubleBetaPlus:
				cout << "2Beta+, ";
				break;
			case electronCapture:
				cout << "EC, ";
				break;
			case isoFusion:
				cout << "IT, ";
				break;
			case spontainousFusion:
				cout << "SF [*], ";
				break;
			case unknown:
				cout << "unknown, ";
				break;
			default:
				cout << int(decayTypes[i]);
				break;
			}
		}
	}
};

const atom electron = { 0, -1 };
const atom positron = { 0, 1 };
const atom neutron = { 0, 0 };
const atom helium = { 4, 2 };

int xOffset, yOffset = 0;
bool w, a, s, d = false;

double FPS = 0;
vector<double> FPSQueue;

int main(int argc, char* argv[]) {
	// Get revision (PL)
	cout << "Witaj w graphic!\nWersja SDL2: " << SDL_GetRevision() << "\n";
	// Load SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
		cout << "Error SDL2 Initialization : " << SDL_GetError();
		return 1;
	}
	// Load audio
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		cout << "Error SDL2 Initialization audio";
		return 2;
	}
	SDL_AudioSpec wavSpec{};
	//	Uint32 wavLength{}; // use if playing audio
	Uint8* wavBuffer{};
	SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
	// Create window
	SDL_Window* window = SDL_CreateWindow(WindowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (window == NULL) {
		cout << "Error window creation";
		return 3;
	}
	// Create renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		cout << "Error renderer creation";
		return 4;
	}
	// Load background
	SDL_Surface* image_sur = IMG_Load("Images/white.png");
	if (image_sur == NULL) {
		cout << "Error loading image: " << IMG_GetError();
		return 5;
	}
	// Create image texture from background
	SDL_Texture* image_tex = SDL_CreateTextureFromSurface(renderer, image_sur);
	if (image_tex == NULL) {
		cout << "Error creating texture";
		return 6;
	}

	// TODO: Load other images

	// TTF init
	if (TTF_Init() != 0) {
		cout << "Warning True Type Font Initialization\n";
	}
	// Load font 'arial'
	TTF_Font* Arial = TTF_OpenFont("Fonts/arial.ttf", 24);
	if (Arial == NULL) {
		cout << "Warning opening Fonts/arial.ttf";
		sleep_for(seconds(1));
		//		return 7;
	}
	TTF_Font* bigArial = TTF_OpenFont("Fonts/arial.ttf", 56);
	if (bigArial == NULL) {
		cout << "Warning opening Fonts/arial.ttf";
		sleep_for(seconds(1));
		//		return 7;
	}
	// Optional: Initialize local variables for mouse location
	short mouseX = 256;
	short mouseY = 256;
	// Text
	SDL_Color FColour = { 0, 0, 0 }; // 0 to 255 on r,g,b
	SDL_Surface* TTFsurface = TTF_RenderText_Solid(Arial, "Klatka: " + frame, FColour);
	SDL_Texture* TTFtexture = SDL_CreateTextureFromSurface(renderer, TTFsurface);
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(TTFtexture, NULL, NULL, &texW, &texH);
	SDL_Rect txtrect = { 0, 0, texW, texH };

	vector<decayingAtom> unstableAtoms; // contains all unstable isotopes from the csv file named accordingly
	vector<decayingAtom> decayChain; // contains THE decay chain
	vector<vector<decayingAtom>> alternateDecayChains; // contains decay chains
	vector<string> posOutput;
	vector<string> inputAtom;
	decayingAtom temporaryAtom{};
	string listOutput = "";
	string mantissa = "";
	decayingAtom consideredAtom{};

	ifstream getStart("start.txt");
	ifstream unstableIsotopes("Unstable_Isotopes.csv");
	// Extracting all unstable isotopes from .csv
	while (unstableIsotopes.peek() != EOF) {
		getline(unstableIsotopes, listOutput);
		posOutput.clear();
		posOutput = splitStr(listOutput, ',');
		temporaryAtom.clear();
		temporaryAtom.Nuclides = stoi(posOutput[2]) + stoi(posOutput[3]);
		temporaryAtom.AtomicNumber = stoi(posOutput[3]);
		for (int i = 0; i < posOutput[4].length(); i++) {
			if (posOutput[4][i] != '*') {
				mantissa += posOutput[4][i];
			}
			else {
				if (posOutput[4][size_t(i) + 4] == '-') {
					temporaryAtom.halfLife = stod(mantissa) * pow(10, (posOutput[4][size_t(i) + 5] - 48) * -1); //x.xxx[*]10^22 (11) [NOW]
				}
				else if (posOutput[4].length() - i - 4 == 2) {
					temporaryAtom.halfLife = stod(mantissa) * pow(10, (posOutput[4][size_t(i) + 4] - 48) * 10 + (posOutput[4][size_t(i) + 5] - 48)); //x.xxx[*]10^22 (11) [NOW]
				}
				else {
					temporaryAtom.halfLife = stod(mantissa) * pow(10, posOutput[4][size_t(i) + 4] - 48); //x.xxx[*]10^22 (11) [NOW]
				}
				mantissa = "";
				break;
			}
		}
		try {
			if (posOutput[5][0] == '"') {
				posOutput[5].erase(0, 1);
				posOutput[5].erase(posOutput[5].length() - 1, 1);
			}
			inputAtom = splitStr(posOutput[5], ',');
			for (int i = 0; i < inputAtom.size(); i++) {
				if (inputAtom[i] == "beta+") {
					temporaryAtom.decayTypes.push_back(temporaryAtom.betaPlus);
				}
				else if (inputAtom[i] == "beta-") {
					temporaryAtom.decayTypes.push_back(temporaryAtom.betaMinus);
				}
				else if (inputAtom[i] == "alpha") {
					temporaryAtom.decayTypes.push_back(temporaryAtom.alpha);
				}
				else if (inputAtom[i] == "gammagamma" || inputAtom[i] == "gamma" || inputAtom[i] == "EC") {
					temporaryAtom.decayTypes.push_back(temporaryAtom.electronCapture);
				}
				else if (inputAtom[i] == "IT") {
					temporaryAtom.decayTypes.push_back(temporaryAtom.isoFusion);
				}
				else if (inputAtom[i] == "SF") {
					temporaryAtom.decayTypes.push_back(temporaryAtom.spontainousFusion);
				}
				else {
					temporaryAtom.decayTypes.push_back(temporaryAtom.unknown);
				}
			}
		}
		catch (...) {
			cout << "An error occured at type conversion\n";
			return 0;
		}
		unstableAtoms.push_back(temporaryAtom);
	}

	getline(getStart, listOutput);
	inputAtom = splitStr(listOutput, ',');
	consideredAtom.Nuclides = stoi(inputAtom[0]);
	consideredAtom.AtomicNumber = stoi(inputAtom[1]);
	int decayChainIterator = 1;
	for (int i = 0; i < unstableAtoms.size(); i++) {
		if (unstableAtoms[i].Nuclides == consideredAtom.Nuclides && unstableAtoms[i].AtomicNumber == consideredAtom.AtomicNumber) {
			consideredAtom = unstableAtoms[i];
			decayChain.push_back(consideredAtom);
			switch (consideredAtom.decayTypes[0]) {
			case consideredAtom.unknown:
				consideredAtom.Nuclides = -1;
				consideredAtom.AtomicNumber = -1;
				break;
			case consideredAtom.betaPlus:
				consideredAtom.AtomicNumber--;
				temporaryAtom.AtomicNumber = positron.AtomicNumber;
				temporaryAtom.Nuclides = positron.Nuclides;
				temporaryAtom.Identifier = decayChainIterator;
				alternateDecayChains.push_back({ temporaryAtom });
				break;
			case consideredAtom.betaMinus:
				consideredAtom.AtomicNumber++;
				temporaryAtom.AtomicNumber = electron.AtomicNumber;
				temporaryAtom.Nuclides = electron.Nuclides;
				temporaryAtom.Identifier = decayChainIterator;
				alternateDecayChains.push_back({ temporaryAtom });
				break;
			case consideredAtom.alpha:
				consideredAtom.AtomicNumber -= 2;
				consideredAtom.Nuclides -= 4;
				temporaryAtom.AtomicNumber = helium.AtomicNumber;
				temporaryAtom.Nuclides = helium.Nuclides;
				temporaryAtom.halfLife = INFINITY;
				temporaryAtom.Identifier = decayChainIterator;
				alternateDecayChains.push_back({ temporaryAtom });
				break;
			case consideredAtom.doubleBetaMinus:
				consideredAtom.AtomicNumber += 2;
				temporaryAtom.AtomicNumber = electron.AtomicNumber;
				temporaryAtom.Nuclides = electron.Nuclides;
				temporaryAtom.Identifier = decayChainIterator;
				alternateDecayChains.push_back({ temporaryAtom });
				break;
			case consideredAtom.doubleBetaPlus:
				consideredAtom.AtomicNumber -= 2;
				temporaryAtom.AtomicNumber = positron.AtomicNumber;
				temporaryAtom.Nuclides = positron.Nuclides;
				temporaryAtom.Identifier = decayChainIterator;
				alternateDecayChains.push_back({ temporaryAtom });
				break;
			case consideredAtom.electronCapture:
				consideredAtom.AtomicNumber--;
				temporaryAtom.AtomicNumber = electron.AtomicNumber;
				temporaryAtom.Nuclides = electron.Nuclides;
				temporaryAtom.Identifier = decayChainIterator * -1;
				alternateDecayChains.push_back({ temporaryAtom });
				break;
			case consideredAtom.isoFusion:
				consideredAtom.Nuclides = -1;
				consideredAtom.AtomicNumber = -1;
				break;
			case consideredAtom.spontainousFusion:
				consideredAtom.Nuclides = -1;
				consideredAtom.AtomicNumber = -1;
				break;
			}
			decayingAtom alternateAtom = unstableAtoms[i];
			for (int k = 1; k < alternateAtom.decayTypes.size(); k++) {
				switch (alternateAtom.decayTypes[k]) {
				case alternateAtom.unknown:
					alternateAtom.Nuclides = -1;
					alternateAtom.AtomicNumber = -1;
					break;
				case alternateAtom.betaPlus:
					alternateAtom.AtomicNumber--;
					temporaryAtom.AtomicNumber = positron.AtomicNumber;
					temporaryAtom.Nuclides = positron.Nuclides;
					temporaryAtom.Identifier = decayChainIterator;
					alternateDecayChains.push_back({ temporaryAtom });
					break;
				case alternateAtom.betaMinus:
					alternateAtom.AtomicNumber++;
					temporaryAtom.AtomicNumber = electron.AtomicNumber;
					temporaryAtom.Nuclides = electron.Nuclides;
					temporaryAtom.Identifier = decayChainIterator;
					alternateDecayChains.push_back({ temporaryAtom });
					break;
				case alternateAtom.alpha:
					alternateAtom.AtomicNumber -= 2;
					alternateAtom.Nuclides -= 4;
					temporaryAtom.AtomicNumber = helium.AtomicNumber;
					temporaryAtom.Nuclides = helium.Nuclides;
					temporaryAtom.Identifier = decayChainIterator;
					alternateDecayChains.push_back({ temporaryAtom });
					break;
				case alternateAtom.doubleBetaMinus:
					alternateAtom.AtomicNumber += 2;
					temporaryAtom.AtomicNumber = electron.AtomicNumber;
					temporaryAtom.Nuclides = electron.Nuclides;
					temporaryAtom.Identifier = decayChainIterator;
					alternateDecayChains.push_back({ temporaryAtom });
					break;
				case alternateAtom.doubleBetaPlus:
					alternateAtom.AtomicNumber -= 2;
					temporaryAtom.AtomicNumber = positron.AtomicNumber;
					temporaryAtom.Nuclides = positron.Nuclides;
					temporaryAtom.Identifier = decayChainIterator;
					alternateDecayChains.push_back({ temporaryAtom });
					break;
				case alternateAtom.electronCapture:
					alternateAtom.AtomicNumber--;
					temporaryAtom.AtomicNumber = electron.AtomicNumber;
					temporaryAtom.Nuclides = electron.Nuclides;
					temporaryAtom.Identifier = decayChainIterator * -1;
					alternateDecayChains.push_back({ temporaryAtom });
					break;
				case alternateAtom.isoFusion:
					alternateAtom.Nuclides = -1;
					alternateAtom.AtomicNumber = -1;
					break;
				case alternateAtom.spontainousFusion:
					alternateAtom.Nuclides = -1;
					alternateAtom.AtomicNumber = -1;
					break;
				}
				alternateAtom.decayTypes = { alternateAtom.decayTypes[k] };
				alternateAtom.Identifier = decayChainIterator;
				alternateDecayChains.push_back({ alternateAtom });
			}
			i = 0;
			decayChainIterator++;
		}
	}
	consideredAtom.halfLife = INFINITY;
	consideredAtom.decayTypes.clear();
	decayChain.push_back(consideredAtom);

	for (int j = 0; j < alternateDecayChains.size(); j++) {
		consideredAtom = alternateDecayChains[j][0];
		if (alternateDecayChains[j][0].Nuclides == 0 || (alternateDecayChains[j][0].Nuclides == 4 && alternateDecayChains[j][0].AtomicNumber == 2)) {
			continue;
		}
		for (int i = 0; i < unstableAtoms.size(); i++) {
			if (unstableAtoms[i].Nuclides == consideredAtom.Nuclides && unstableAtoms[i].AtomicNumber == consideredAtom.AtomicNumber) {
				consideredAtom = unstableAtoms[i];
				decayChainIterator = alternateDecayChains[j][0].Identifier;
				switch (consideredAtom.decayTypes[0]) {
				case consideredAtom.unknown:
					consideredAtom.Nuclides = -1;
					consideredAtom.AtomicNumber = -1;
					break;
				case consideredAtom.betaPlus:
					consideredAtom.AtomicNumber--;
					temporaryAtom.AtomicNumber = positron.AtomicNumber;
					temporaryAtom.Nuclides = positron.Nuclides;
					temporaryAtom.Identifier = decayChainIterator;
					alternateDecayChains.push_back({ temporaryAtom });
					break;
				case consideredAtom.betaMinus:
					consideredAtom.AtomicNumber++;
					temporaryAtom.AtomicNumber = electron.AtomicNumber;
					temporaryAtom.Nuclides = electron.Nuclides;
					temporaryAtom.Identifier = decayChainIterator;
					alternateDecayChains.push_back({ temporaryAtom });
					break;
				case consideredAtom.alpha:
					consideredAtom.AtomicNumber -= 2;
					consideredAtom.Nuclides -= 4;
					temporaryAtom.AtomicNumber = helium.AtomicNumber;
					temporaryAtom.Nuclides = helium.Nuclides;
					temporaryAtom.halfLife = INFINITY;
					temporaryAtom.Identifier = decayChainIterator;
					alternateDecayChains.push_back({ temporaryAtom });
					break;
				case consideredAtom.doubleBetaMinus:
					consideredAtom.AtomicNumber += 2;
					temporaryAtom.AtomicNumber = electron.AtomicNumber;
					temporaryAtom.Nuclides = electron.Nuclides;
					temporaryAtom.Identifier = decayChainIterator;
					alternateDecayChains.push_back({ temporaryAtom });
					break;
				case consideredAtom.doubleBetaPlus:
					consideredAtom.AtomicNumber -= 2;
					temporaryAtom.AtomicNumber = positron.AtomicNumber;
					temporaryAtom.Nuclides = positron.Nuclides;
					temporaryAtom.Identifier = decayChainIterator;
					alternateDecayChains.push_back({ temporaryAtom });
					break;
				case consideredAtom.electronCapture:
					consideredAtom.AtomicNumber--;
					temporaryAtom.AtomicNumber = electron.AtomicNumber;
					temporaryAtom.Nuclides = electron.Nuclides;
					temporaryAtom.Identifier = decayChainIterator * -1;
					alternateDecayChains.push_back({ temporaryAtom });
					break;
				case consideredAtom.isoFusion:
					consideredAtom.Nuclides = -1;
					consideredAtom.AtomicNumber = -1;
					break;
				case consideredAtom.spontainousFusion:
					consideredAtom.Nuclides = -1;
					consideredAtom.AtomicNumber = -1;
					break;
				}
				alternateDecayChains[j].push_back(consideredAtom);
				i = 0;
			}
		}
		alternateDecayChains[j][alternateDecayChains[j].size() - 1].halfLife = INFINITY;
		alternateDecayChains[j][alternateDecayChains[j].size() - 1].decayTypes.clear();
	}


	cout << "\nFull decay chain:\n";
	for (int i = 0; i < decayChain.size(); i++) {
		if (decayChain[i].halfLife == INFINITY) {
			cout << "\t" << i << ": " << decayChain[i].getElementSymbol() << ", " << decayChain[i].Nuclides << ", which is STABLE\n";
			break;
		}
		cout << "\t" << i << ": " << decayChain[i].getElementSymbol() << ", " << decayChain[i].Nuclides << ", Half-Life is: " << decayChain[i].halfLife << " seconds, decayes by "; decayChain[i].echoDecayTypes();
		cout << endl;
	}
	cout << "\nOther decay chains:\n";
	for (int j = 0; j < alternateDecayChains.size(); j++) {
		if (alternateDecayChains[j][0].Nuclides == 0 || alternateDecayChains[j][0].Nuclides == -1 || (alternateDecayChains[j][0].Nuclides == 4 && alternateDecayChains[j][0].AtomicNumber == 2)) {
			alternateDecayChains.erase(alternateDecayChains.begin() + j);
			continue;
		}
		bool isConverging = false;
		cout << "\n\tChain from number " << alternateDecayChains[j][0].Identifier - 1 << "\n";
		for (int i = 0; i < alternateDecayChains[j].size(); i++) {
			for (int k = 0; k < decayChain.size(); k++) {
				if (!isConverging && alternateDecayChains[j][i].AtomicNumber == decayChain[k].AtomicNumber && alternateDecayChains[j][i].Nuclides == decayChain[k].Nuclides) {
					cout << "\nHere lies a convergance\n";
					isConverging = true;
				}
			}
			if (alternateDecayChains[j][i].halfLife == INFINITY) {
				cout << "\t" << i << ": " << alternateDecayChains[j][i].getElementSymbol() << ", " << alternateDecayChains[j][i].Nuclides << ", which is STABLE\n";
				break;
			}
			cout << "\t" << i << ": " << alternateDecayChains[j][i].getElementSymbol() << ", " << alternateDecayChains[j][i].Nuclides << ", Half-Life is: " << alternateDecayChains[j][i].halfLife << " seconds, decayes by "; alternateDecayChains[j][i].echoDecayTypes();
			cout << endl;
		}
	}


	// Main display loop
	while (!false) {
		auto start1 = high_resolution_clock::now();
		SDL_Event event;
		// Użyj SDL_WaitEvent(&event), by czekać do wejścia, a SDL_PollEvent(&event), by nie czekać
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				isRunning = false;
				// TODO: Shutdown logic of your choice
				return 0;
			}
		}
		switch (event.type) {
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) {
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "You pressed somewhere!", (to_string(mouseX) + ", " + to_string(mouseY) + " (" + to_string(mouseX + xOffset) + ", " + to_string(mouseY + yOffset) + ")").c_str(), window);
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				// TODO: What to do when left click is pressed
			}
			break;
		case SDL_MOUSEMOTION:
			mouseX = (int16_t)event.motion.x;
			mouseY = (int16_t)event.motion.y;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_f:
				if (isFullscreen) {
					SDL_SetWindowFullscreen(window, 0);
					SDL_SetWindowSize(window, oldWidth, oldHeight);
					isFullscreen = false;
				}
				else {
					oldWidth = WIDTH;
					oldHeight = HEIGHT;
					SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
					isFullscreen = true;
				}
				break;
			case SDLK_QUOTE:
				screenshot(renderer, ("Screenshots/screen@" + to_string(time(NULL)) + ".png").c_str());
				break;
			case SDLK_w:
				w = true;
				break;
			case SDLK_a:
				a = true;
				break;
			case SDLK_s:
				s = true;
				break;
			case SDLK_d:
				d = true;
				break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym) {
			case SDLK_w:
				w = false;
				break;
			case SDLK_a:
				a = false;
				break;
			case SDLK_s:
				s = false;
				break;
			case SDLK_d:
				d = false;
				break;
			}
			break;
		}
		if (w) {
			yOffset += 5;
		}
		if (s) {
			yOffset -= 5;
		}
		if (a) {
			xOffset += 5;
		}
		if (d) {
			xOffset -= 5;
		}

		SDL_RenderClear(renderer);
		
		// Resolution measurement (Optional)
		WIDTH = (uint16_t)SDL_GetWindowSurface(window)->w;
		HEIGHT = (uint16_t)SDL_GetWindowSurface(window)->h;
		cout << "Res:" << SDL_GetWindowSurface(window)->w << ", " << SDL_GetWindowSurface(window)->h << endl;

		// Image render
		if (SDL_RenderCopy(renderer, image_tex, NULL, NULL) != 0) {
			cout << "Error SDL_RenderCopy-ing: " << SDL_GetError();
			return -2;
		}
		string framestr;
		double toRound = 0;
		FPSQueue.push_back(FPS);
		if (FPSQueue.size() > 18) {
			FPSQueue.erase(FPSQueue.begin());
			for (int i = 0; i < 18; i++) {
				toRound += FPSQueue[i];
			}
			framestr = to_string(frame) + ", " + roundToAndStringify(toRound / 18, 2) + "FPS";
		}
		else {
			framestr = to_string(frame) + ", " + roundToAndStringify(FPS, 2) + "FPS";
		}
		TTFsurface = TTF_RenderText_Solid(Arial, framestr.c_str(), FColour);
		TTFtexture = SDL_CreateTextureFromSurface(renderer, TTFsurface);
		SDL_QueryTexture(TTFtexture, NULL, NULL, &texW, &texH);
		txtrect = { 0, 0, texW, texH };
		if (SDL_RenderCopy(renderer, TTFtexture, NULL, &txtrect) != 0) {
			cout << "Error SDL_RenderCopy-ing: " << SDL_GetError();
			return -2;
		}

		SDL_Rect rect{};
		for (int i = 0; i < decayChain.size(); i++) {
			framestr = to_string(i);
			rect.x = xOffset;
			rect.y = 24 + yOffset + i * 160;
			rect.w = 128;
			rect.h = 128;
			SDL_RenderDrawLine(renderer, 64 + xOffset, (i+1) * 160 - 8 + yOffset, 64 + xOffset, (i + 1) * 160 + 24 + yOffset);
			SDL_RenderDrawRect(renderer, &rect);
			SDL_DestroyTexture(TTFtexture);
			SDL_FreeSurface(TTFsurface);
			TTFsurface = TTF_RenderText_Solid(Arial, framestr.c_str(), { 0, 0, 0 });
			TTFtexture = SDL_CreateTextureFromSurface(renderer, TTFsurface);
			SDL_QueryTexture(TTFtexture, NULL, NULL, &texW, &texH);
			txtrect = { xOffset, yOffset + i * 160, texW, texH };
			if (SDL_RenderCopy(renderer, TTFtexture, NULL, &txtrect) != 0) {
				cout << "Error SDL_RenderCopy-ing: " << SDL_GetError();
				return -2;
			}

			SDL_DestroyTexture(TTFtexture);
			SDL_FreeSurface(TTFsurface);
			framestr = to_string(decayChain[i].Nuclides);
			TTFsurface = TTF_RenderText_Solid(Arial, framestr.c_str(), { 0, 0, 0 });
			TTFtexture = SDL_CreateTextureFromSurface(renderer, TTFsurface);
			SDL_QueryTexture(TTFtexture, NULL, NULL, &texW, &texH);
			txtrect = { xOffset + 4, yOffset + i * 160 + 32, texW, texH };
			int rightAlignOffset = texW;
			if (SDL_RenderCopy(renderer, TTFtexture, NULL, &txtrect) != 0) {
				cout << "Error SDL_RenderCopy-ing: " << SDL_GetError();
				return -2;
			}

			SDL_DestroyTexture(TTFtexture);
			SDL_FreeSurface(TTFsurface);
			framestr = to_string(decayChain[i].AtomicNumber);
			TTFsurface = TTF_RenderText_Solid(Arial, framestr.c_str(), { 0, 0, 0 });
			TTFtexture = SDL_CreateTextureFromSurface(renderer, TTFsurface);
			SDL_QueryTexture(TTFtexture, NULL, NULL, &texW, &texH);
			txtrect = { xOffset + 4 + (rightAlignOffset - texW), yOffset + i * 160 + 112, texW, texH };
			if (SDL_RenderCopy(renderer, TTFtexture, NULL, &txtrect) != 0) {
				cout << "Error SDL_RenderCopy-ing: " << SDL_GetError();
				return -2;
			}

			SDL_DestroyTexture(TTFtexture);
			SDL_FreeSurface(TTFsurface);
			framestr = decayChain[i].getElementSymbol();
			TTFsurface = TTF_RenderText_Solid(bigArial, framestr.c_str(), { 0, 0, 0 });
			TTFtexture = SDL_CreateTextureFromSurface(renderer, TTFsurface);
			SDL_QueryTexture(TTFtexture, NULL, NULL, &texW, &texH);
			txtrect = { xOffset + 8 + rightAlignOffset, yOffset + i * 160 + 50, texW, texH };
			if (SDL_RenderCopy(renderer, TTFtexture, NULL, &txtrect) != 0) {
				cout << "Error SDL_RenderCopy-ing: " << SDL_GetError();
				return -2;
			}

			long double convertedHalfLife = decayChain[i].halfLife;
			char convertedHalfLifeUnit = 's';
			if (convertedHalfLife > 90) {
				convertedHalfLife /= 60;
				convertedHalfLifeUnit = 'm';
			}
			if (convertedHalfLife > 90) {
				convertedHalfLife /= 60;
				convertedHalfLifeUnit = 'h';
			}
			if (convertedHalfLife > 48) {
				convertedHalfLife /= 24;
				convertedHalfLifeUnit = 'd';
			}
			if (convertedHalfLife > 400) {
				convertedHalfLife /= 365.265;
				convertedHalfLifeUnit = 'y';
			}
			if (decayChain[i].halfLife != INFINITY) {
				framestr = to_string(uint64_t(convertedHalfLife)) + "." + to_string(uint64_t(round(convertedHalfLife * 100) / 100 - floor(convertedHalfLife))) + convertedHalfLifeUnit;
				SDL_DestroyTexture(TTFtexture);
				SDL_FreeSurface(TTFsurface);
				TTFsurface = TTF_RenderText_Solid(Arial, framestr.c_str(), { 0, 0, 0 });
				TTFtexture = SDL_CreateTextureFromSurface(renderer, TTFsurface);
				SDL_QueryTexture(TTFtexture, NULL, NULL, &texW, &texH);
				txtrect = { xOffset + 60, yOffset + i * 160 + 120, texW, texH };
				if (SDL_RenderCopy(renderer, TTFtexture, NULL, &txtrect) != 0) {
					cout << "Error SDL_RenderCopy-ing: " << SDL_GetError();
					return -2;
				}
			}

		}
		int stepX = 1;
		for (int i = 0; i < alternateDecayChains.size(); i++) {
			if (alternateDecayChains[i][0].Nuclides == 0 || alternateDecayChains[i][0].Nuclides == -1 || (alternateDecayChains[i][0].Nuclides == 4 && alternateDecayChains[i][0].AtomicNumber == 2)) {
				continue;
			}
			bool isConverging = false;
			for (int j = 0; j < alternateDecayChains[i].size(); j++) {
				for (int k = 0; k < decayChain.size(); k++) {
					if (!isConverging && alternateDecayChains[i][j].AtomicNumber == decayChain[k].AtomicNumber && alternateDecayChains[i][j].Nuclides == decayChain[k].Nuclides) {
						SDL_RenderDrawLine(renderer, 64 + xOffset + stepX * 160, (j + alternateDecayChains[i][0].Identifier) * 160 - 8 + yOffset, 64 + xOffset, (j + alternateDecayChains[i][0].Identifier) * 160 + 24 + yOffset);
						isConverging = true;
					}
				}
				if (!isConverging) {
					framestr = to_string(j) + " (" + to_string(alternateDecayChains[i][0].Identifier) + ")";
					rect.x = xOffset + stepX * 160;
					rect.y = 24 + yOffset + (j + alternateDecayChains[i][0].Identifier) * 160;
					rect.w = 128;
					rect.h = 128;
					SDL_RenderDrawLine(renderer, 64 + xOffset, (j + alternateDecayChains[i][0].Identifier) * 160 - 8 + yOffset, 64 + xOffset + stepX * 160, (j + alternateDecayChains[i][0].Identifier) * 160 + 24 + yOffset);
					SDL_RenderDrawRect(renderer, &rect);
					SDL_DestroyTexture(TTFtexture);
					SDL_FreeSurface(TTFsurface);
					TTFsurface = TTF_RenderText_Solid(Arial, framestr.c_str(), { 0, 0, 0 });
					TTFtexture = SDL_CreateTextureFromSurface(renderer, TTFsurface);
					SDL_QueryTexture(TTFtexture, NULL, NULL, &texW, &texH);
					txtrect = { rect.x, yOffset + (j + alternateDecayChains[i][0].Identifier) * 160, texW, texH };
					if (SDL_RenderCopy(renderer, TTFtexture, NULL, &txtrect) != 0) {
						cout << "Error SDL_RenderCopy-ing: " << SDL_GetError();
						return -2;
					}

					SDL_DestroyTexture(TTFtexture);
					SDL_FreeSurface(TTFsurface);
					framestr = to_string(alternateDecayChains[i][j].Nuclides);
					TTFsurface = TTF_RenderText_Solid(Arial, framestr.c_str(), { 0, 0, 0 });
					TTFtexture = SDL_CreateTextureFromSurface(renderer, TTFsurface);
					SDL_QueryTexture(TTFtexture, NULL, NULL, &texW, &texH);
					txtrect = { rect.x + 4, yOffset + (j + alternateDecayChains[i][0].Identifier) * 160 + 32, texW, texH };
					int rightAlignOffset = texW;
					if (SDL_RenderCopy(renderer, TTFtexture, NULL, &txtrect) != 0) {
						cout << "Error SDL_RenderCopy-ing: " << SDL_GetError();
						return -2;
					}

					SDL_DestroyTexture(TTFtexture);
					SDL_FreeSurface(TTFsurface);
					framestr = to_string(alternateDecayChains[i][j].AtomicNumber);
					TTFsurface = TTF_RenderText_Solid(Arial, framestr.c_str(), { 0, 0, 0 });
					TTFtexture = SDL_CreateTextureFromSurface(renderer, TTFsurface);
					SDL_QueryTexture(TTFtexture, NULL, NULL, &texW, &texH);
					txtrect = { rect.x + 4 + (rightAlignOffset - texW), yOffset + (j + alternateDecayChains[i][0].Identifier) * 160 + 112, texW, texH };
					if (SDL_RenderCopy(renderer, TTFtexture, NULL, &txtrect) != 0) {
						cout << "Error SDL_RenderCopy-ing: " << SDL_GetError();
						return -2;
					}

					SDL_DestroyTexture(TTFtexture);
					SDL_FreeSurface(TTFsurface);
					framestr = alternateDecayChains[i][j].getElementSymbol();
					TTFsurface = TTF_RenderText_Solid(bigArial, framestr.c_str(), { 0, 0, 0 });
					TTFtexture = SDL_CreateTextureFromSurface(renderer, TTFsurface);
					SDL_QueryTexture(TTFtexture, NULL, NULL, &texW, &texH);
					txtrect = { rect.x + 8 + rightAlignOffset, yOffset + (j + alternateDecayChains[i][0].Identifier) * 160 + 50, texW, texH };
					if (SDL_RenderCopy(renderer, TTFtexture, NULL, &txtrect) != 0) {
						cout << "Error SDL_RenderCopy-ing: " << SDL_GetError();
						return -2;
					}

					long double convertedHalfLife = alternateDecayChains[i][j].halfLife;
					char convertedHalfLifeUnit = 's';
					if (convertedHalfLife > 90) {
						convertedHalfLife /= 60;
						convertedHalfLifeUnit = 'm';
					}
					if (convertedHalfLife > 90) {
						convertedHalfLife /= 60;
						convertedHalfLifeUnit = 'h';
					}
					if (convertedHalfLife > 48) {
						convertedHalfLife /= 24;
						convertedHalfLifeUnit = 'd';
					}
					if (convertedHalfLife > 400) {
						convertedHalfLife /= 365.265;
						convertedHalfLifeUnit = 'y';
					}
					if (alternateDecayChains[i][j].halfLife != INFINITY) {
						framestr = to_string(uint64_t(convertedHalfLife)) + "." + to_string(uint64_t(round(convertedHalfLife * 100) / 100 - floor(convertedHalfLife))) + convertedHalfLifeUnit;
						SDL_DestroyTexture(TTFtexture);
						SDL_FreeSurface(TTFsurface);
						TTFsurface = TTF_RenderText_Solid(Arial, framestr.c_str(), { 0, 0, 0 });
						TTFtexture = SDL_CreateTextureFromSurface(renderer, TTFsurface);
						SDL_QueryTexture(TTFtexture, NULL, NULL, &texW, &texH);
						txtrect = { rect.x + 60, yOffset + (j + alternateDecayChains[i][0].Identifier) * 160 + 120, texW, texH };
						if (SDL_RenderCopy(renderer, TTFtexture, NULL, &txtrect) != 0) {
							cout << "Error SDL_RenderCopy-ing: " << SDL_GetError();
							return -2;
						}
					}
				}
			}
		}

		// "submit"
		SDL_RenderPresent(renderer);

		// cleanup
		SDL_DestroyTexture(TTFtexture);
		SDL_FreeSurface(TTFsurface);

		// Optional: measurement
		auto stop1 = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop1 - start1);
		FPS = 1000 / ((double)duration.count() / 1000);
		if ((double)duration.count() > 1000000) {
			cout << "Frame time: " << (double)duration.count() / 1000000 << "s";
		} else if ((double)duration.count() > 1000) {
			cout << "Frame time: " << (double)duration.count() / 1000 << "ms";
		} else {
			cout << "Frame time: " << (double)duration.count() << " microseconds";
		}
		if (((double)1000 / FPSCap) - (double)duration.count() / 1000 > 0) {
			SDL_Delay((uint32_t)floor((1000.0 / FPSCap) - (double)duration.count() / 1000));
			cout << " - Wait time: " << (1000.0 / FPSCap) - (double)duration.count() / 1000;
		}
		cout << " - FPS: " << FPS << " - FPS Cap: " << FPSCap << " - Frame: " << frame;
		cout << endl;
		frame++;
	}
	// Czyśćmy po sobie
	//delete[] pixels;
	SDL_CloseAudioDevice(deviceId); // disables audio
	SDL_FreeWAV(wavBuffer); // dodgy
	TTF_CloseFont(Arial);
	SDL_DestroyTexture(TTFtexture); // works at runtime :D
	SDL_FreeSurface(TTFsurface); // works at runtime :D
	SDL_FreeSurface(image_sur);
	SDL_DestroyTexture(image_tex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();	
	return 0;
}