#include <iostream>
#include <fstream>
#include <windows.h>
#include <chrono>
#include <thread>
#include <vector>
#include <cmath>
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
int scrollX = 0;
int scrollY = 0;


const short graphLen = 3840;
int graphList1[graphLen] = {};
int graph1Max = 0;
int graph1Min = 0;
int graphList2[graphLen] = {};
int graph2Max = 0;
int graph2Min = 0;

int FPSCap = 600;
bool isFullscreen = false;
bool isRunning = true;
uint64_t frame;
const Uint32 pixelFormat = SDL_PIXELFORMAT_ARGB8888;
const char* WindowName = "Graphics (SDL2)";

class rgba8Colour {
public:
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
};
class spriteData {
public:
	uint16_t x;
	uint16_t y;
	uint16_t sizeX;
	uint16_t sizeY;
	uint8_t jumpLeft;
	//float yAccel;
	//float xAccel;
	float yReal;
	float xReal;
	bool isMovingW = false;
	bool isMovingA = false;
	bool isMovingS = false;
	bool isMovingD = false;
	bool isJumping = false;
	bool isSneaking = false;
	bool isStillJumping = false;
	bool isMidAir = false;
};
class Line {
public:
	uint16_t x1;
	uint16_t y1;
	uint16_t x2;
	uint16_t y2;
};
class thickLine : public Line {
public:
	uint16_t thickness;
};
void moveMainSprite(spriteData &mainSprite) {
	float jumpedDistance = 0.0f;
	// execute moving
	while (isRunning) {
		if (mainSprite.isMovingA) {
			if (mainSprite.x > 0) {
				mainSprite.xReal -= 1.8;
			}
		}
		if (mainSprite.isMovingD) {
			if (mainSprite.x < WIDTH - mainSprite.sizeX) {
				mainSprite.xReal += 1.8;
			}
		}
		if (mainSprite.isMovingS) {
			if (mainSprite.y < HEIGHT - mainSprite.sizeY) {
				if (!mainSprite.isStillJumping) {
					mainSprite.yReal += 1.8;
				}
			}
		}
		if (mainSprite.isMovingW) {
			if (mainSprite.y > 0) {
				if (!mainSprite.isStillJumping) {
					mainSprite.yReal -= 1.8;
				}
			}
		}
		if (mainSprite.isJumping) {
			if (!mainSprite.isStillJumping) {
				mainSprite.isStillJumping = true;
				mainSprite.jumpLeft = 0;
			}
		}
		if (mainSprite.isStillJumping) {
			if (mainSprite.jumpLeft <= 133) {
				if (mainSprite.yReal > 0) {
					if (mainSprite.yReal > 0.01) {
						jumpedDistance += sin(mainSprite.jumpLeft / 21) * 2;
					}
					mainSprite.yReal -= sin(mainSprite.jumpLeft / 21) * 2;
				}
				else {
					mainSprite.jumpLeft = 133 - mainSprite.jumpLeft;
				}
				mainSprite.jumpLeft += 1;
			}
			else {
				mainSprite.yReal += jumpedDistance; // 3.48708f
				mainSprite.isStillJumping = false;
				mainSprite.isJumping = false;
				jumpedDistance = 0;
			}
		}
		if (mainSprite.yReal < 0) {
			mainSprite.yReal = 0.01;
		}
		if (mainSprite.xReal < 0) {
			mainSprite.xReal = 0;
		}
		mainSprite.x = round(mainSprite.xReal);
		mainSprite.y = round(mainSprite.yReal);
		sleep_for(5ms);
	}
}
vector<string> split(const string& text, char sep) {
	vector<string> tokens;
	size_t start = 0, end = 0;
	while ((end = text.find(sep, start)) != string::npos) {
		tokens.push_back(text.substr(start, end - start));
		start = end + 1;
	}
	tokens.push_back(text.substr(start));
	return tokens;
}
int ignoreBufferLength;
vector<string> csvExtract(string csvName) {
	vector<string> VSBuffer;
	string CSVBuffer;
	vector<string> rawCSV;
	ifstream csvIn(csvName);
	getline(csvIn, CSVBuffer);
	ignoreBufferLength = split(CSVBuffer, ',').size();
	while (getline(csvIn, CSVBuffer)) {
		VSBuffer = split(CSVBuffer, ',');
		for (int i = 0; i < VSBuffer.size(); i++) {
			rawCSV.push_back(VSBuffer[i]);
		}
		rawCSV.push_back("60000");
	}
	csvIn.close();
	return rawCSV;
}
vector<int> V_StrToV_Int(vector<string> Vinput) {
	vector<int> V_Intputemp;
	for (int i = ignoreBufferLength; i < Vinput.size(); i++) {
		try {
			int intemp = stoi(Vinput[i]);
			if (intemp != 60000) {
				V_Intputemp.push_back(intemp);
			}
		}
		catch (...) {
			cout << "Converting failed! - \"" << Vinput[i] << "\"";
		}
	}
	return V_Intputemp;
}
void SDL_DrawThickLine(SDL_Renderer* render, unsigned short x1, unsigned short y1,
	unsigned short x2, unsigned short y2,
	rgba8Colour colour, int8_t thickness) {
	thickness--;
	SDL_SetRenderDrawColor(render, colour.red, colour.green, colour.blue, colour.alpha);
	for (int ix = thickness * -1; ix <= thickness; ix++) {
		if (x1 == x2) {
			ix = thickness;
		}
		for (int iy = thickness * -1; iy <= thickness; iy++) {
			if (y1 == y2) {
				iy = thickness;
			}
			SDL_RenderDrawLine(render, x1 + ix, y1 + iy, x2 + ix, y2 + iy);
		}
	}
}
void SDL_DrawThickLine(SDL_Renderer* render, unsigned short x1, unsigned short y1,
	unsigned short x2, unsigned short y2, int8_t thickness) {

	thickness--;
	for (int ix = thickness * -1; ix <= thickness; ix++) {
		for (int iy = thickness * -1; iy <= thickness; iy++) {
			SDL_RenderDrawLine(render, x1 + ix, y1 + iy, x2 + ix, y2 + iy);
		}
	}
}
void MDL_DrawCircle(SDL_Renderer* renderer, short x1, short y1, unsigned short radii) {
	float distance = 0;
	bool secondhalf = false;
	for (int x = -radii - 1; x < radii + 2; x++) {
		for (int y = -radii - 1; y < radii + 2; y++) { 
		distance = sqrt(pow(x,2) + pow(y,2));
			if (radii + 1.5f > distance && distance > radii + 0.5f) {
				SDL_RenderDrawPoint(renderer, x + x1, y + y1 + radii);
			}
		}
	}
} // more than 2x slower
void DrawCircle(SDL_Renderer* renderer, int x, int y, int r)
{
	double angle, x1, y1;
	for (angle = 0; angle < 360; angle += 9.0/ r)
	{
		x1 = r * cos(angle * M_PI / 180);
		y1 = r * sin(angle * M_PI / 180);
		SDL_RenderDrawPoint(renderer, x + x1, y + y1);
	}
}
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
int main(int argc, char* argv[]) {
	cout << "Witaj w graphic!\nWersja SDL2: " << SDL_GetRevision() << "\n";
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
		cout << "Error SDL2 Initialization : " << SDL_GetError();
		return 1;
	}
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		cout << "Error SDL2 Initialization audio";
		return 2;
	}
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8* wavBuffer;
	SDL_LoadWAV("example.wav", &wavSpec, &wavBuffer, &wavLength);
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
//	SDL_Surface* image_sur = SDL_LoadBMP("nicetest.bmp");
//	SDL_Surface* image_sur = IMG_Load("Images/nicetest.png");
	SDL_Surface* image_sur = IMG_Load("Images/white.png");
	if (image_sur == NULL) {
		cout << "Error loading image: " << IMG_GetError();
		return 5;
	}
	// Create image texture from bg load
	SDL_Texture* image_tex = SDL_CreateTextureFromSurface(renderer, image_sur);
	if (image_tex == NULL) {
		cout << "Error creating texture";
		return 6;
	}
	// load other images
	SDL_Surface* sprite_sur = IMG_Load("Images/sprite.png");
	if (sprite_sur == NULL) {
		cout << "Error loading image: " << IMG_GetError();
		return 5;
	}
	SDL_Texture* sprite_tex = SDL_CreateTextureFromSurface(renderer, sprite_sur);
	if (sprite_tex == NULL) {
		cout << "Error creating texture";
		return 6;
	}
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
	if (argc > 1) {
		cout << "\nWykryto argumenty.\n Argumenty:\n";
		for (int i = 0; argc > i; ++i) {
			cout << i << " - \"" << argv[i] << "\"";
			if (argv[i] == "-F") {
				SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
				isFullscreen = true;
				cout << " - Fullscreen\n";
			}
			if (argv[i] == "-f") {
				SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
				isFullscreen = true;
				cout << " - REAL Fullscreen\n";
			}
			if (argv[i] == "-C") {
				i += 1;
				try {
					FPSCap = stoi(argv[i]);
				}
				catch (...) {
					cout << " - " << argv[i] << " - Invalid!\n";
				}
				cout << " - FPS Cap set to "<< argv[i] <<"\n";
			}
			else {
				cout << "\n";
			}
		}
	}
	// Pixel drawing
	//SDL_Texture* PxTexture = SDL_CreateTexture(renderer,
	//	pixelFormat, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);
	//Uint32* pixels = new Uint32[WIDTH * HEIGHT];
	// Pixel drawing: White background
	//memset(pixels, 255, WIDTH * HEIGHT * sizeof(Uint32));
	// Pixel drawing: Mouse position
	//bool LeftClick = false;

	short mouseX = 256;
	short mouseY = 256;

	// Graph list randomise
	// 'Smooth random' graph lists
	ofstream csvdebugfile("debug.csv");
	srand((unsigned int)duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count());
	graphList1[0] = (rand() % (HEIGHT - 18))+1;
	srand((unsigned int)duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch()).count());
	graphList2[0] = (rand() % (HEIGHT - 18)) + 1;
	csvdebugfile << graphList1[0] << "," << graphList2[0] << "\n";
	for (int i = 1; i < graphLen; i++) {
		srand((int)duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count());
		graphList1[i] = graphList1[i - 1] + ((rand() % 7) - 3);
		srand((int)duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count());
		graphList2[i] = graphList2[i - 1] + ((rand() % 9) - 4);
		csvdebugfile << graphList1[i] << "," << graphList2[i] << "\n";
		if (graphList1[i] <= 0) {
			graphList1[i] = (rand() % 20) + 1;
		}
		if (graphList2[i] <= 0) {
			graphList2[i] = (rand() % 20);
		}
	}
	csvdebugfile.close();
	// Find max and min
	for (int i = 0; i < graphLen; i++) {
		if (graphList1[i] > graph1Max) {
			graph1Max = graphList1[i];
		}
		if (graphList1[i] < graph1Min) {
			graph1Min = graphList1[i];
		}
		if (graphList2[i] > graph2Max) {
			graph2Max = graphList2[i];
		}
		if (graphList2[i] < graph2Min) {
			graph2Min = graphList2[i];
		}
	}
	// Load map
	vector<int> mapData = V_StrToV_Int(csvExtract("Maps/map.csv"));
	vector<thickLine> collisonMapData;

	// Play audio
	SDL_QueueAudio(deviceId, wavBuffer, wavLength);
	SDL_PauseAudioDevice(deviceId, 0);
	// Text
	SDL_Color FColour = {0, 0, 0}; // 0 to 255 on r,g,b
	SDL_Surface* TTFsurface = TTF_RenderText_Solid(Arial, "Klatka: " + frame, FColour);
	SDL_Texture* TTFtexture = SDL_CreateTextureFromSurface(renderer, TTFsurface);
	int texW = 0;
	int texH = 0;
	// Last steps
	spriteData mainSprite{};
	mainSprite.xReal = 256;
	mainSprite.yReal = 256;
	mainSprite.sizeX = 80;
	mainSprite.sizeY = 80;
	thread moveSprite(moveMainSprite, ref(mainSprite));
	int WindowX = 0;
	int WindowY = 0;
	SDL_QueryTexture(TTFtexture, NULL, NULL, &texW, &texH);
	SDL_Rect sprrect = { mainSprite.x, mainSprite.y, mainSprite.sizeX, mainSprite.sizeY };
	SDL_Rect txtrect = { 0, 0, texW, texH };
	SDL_LoadWAV("press.wav", &wavSpec, &wavBuffer, &wavLength); // fix - load when needed
	// Main display loop
	while (!false) {
		auto start1 = high_resolution_clock::now();
		SDL_Event event;
		// Użyj SDL_WaitEvent(&event), by czekać do wejścia, a SDL_PollEvent(&event), by nie czekać
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				isRunning = false;
				moveSprite.join();
//				SDL_CloseAudioDevice(deviceId); // disables audio
				return 0;
			}
		}
		switch (event.type) {
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) {
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Mouse Press",
					(to_string(mouseX) + "," + to_string(mouseY)).c_str(), window);
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {

			}
			break;
		case SDL_MOUSEMOTION:
			mouseX = (int16_t)event.motion.x;
			mouseY = (int16_t)event.motion.y;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_a:
				mainSprite.isMovingA = true;
				break;
			case SDLK_d:
				mainSprite.isMovingD = true;
				break;
			case SDLK_w:
				mainSprite.isMovingW = true;
				break;
			case SDLK_s:
				mainSprite.isMovingS = true;
				break;
			case SDLK_SPACE:
				mainSprite.isJumping = true;
				break;
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
			case SDLK_t:
				SDL_QueueAudio(deviceId, wavBuffer, wavLength);
				SDL_PauseAudioDevice(deviceId, 0);
				break;
			case SDLK_r:
				SDL_ClearQueuedAudio(deviceId);
				SDL_PauseAudioDevice(deviceId, 1);
				break;
			case SDLK_QUOTE:
				screenshot(renderer, ("Screenshots/screen@" + to_string(time(NULL)) + ".png").c_str());
				break;
			case SDLK_l:
				mapData = V_StrToV_Int(csvExtract("Maps/map.csv"));
				break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym) {
			case SDLK_a:
				mainSprite.isMovingA = false;
				break;
			case SDLK_d:
				mainSprite.isMovingD = false;
				break;
			case SDLK_w:
				mainSprite.isMovingW = false;
				break;
			case SDLK_s:
				mainSprite.isMovingS = false;
				break;
			case SDLK_SPACE:
				mainSprite.isJumping = false;
				break;
			}
			break;
		}
		SDL_RenderClear(renderer);
		if (GetKeyState('C') & 0x8000/*Check if high-order bit is set*/) {
			frame = 1;
		}

		//if (GetKeyState('I') & 0x8000/*Check if high-order bit is set*/) {
		//	memset(pixels, 255, WIDTH * HEIGHT * sizeof(Uint32));
		//}
		
		// Res measurement
		cout << "Res:" << SDL_GetWindowSurface(window)->w << ", ";
		cout << SDL_GetWindowSurface(window)->h << endl;
		WIDTH = (uint16_t)SDL_GetWindowSurface(window)->w;
		HEIGHT = (uint16_t)SDL_GetWindowSurface(window)->h;

		// Image render
		if (SDL_RenderCopy(renderer, image_tex, NULL, NULL) != 0) {
			cout << "Error SDL_RenderCopy-ing: " << SDL_GetError();
			return -2;
		}
		
		// Game Data Process

		for (size_t i = 0; i < mapData.size(); i = i + 6) {
			SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
			if (mapData[i + 5] <= 1) {
				SDL_DrawThickLine(renderer, mapData[i], mapData[i + 1], mapData[i + 2], mapData[i + 3], mapData[i + 4]);
				if (mapData[i + 5] == 1) {
					thickLine tempLine = { mapData[i], mapData[i + 1], mapData[i + 2], mapData[i + 3], mapData[i + 4] };
					collisonMapData.push_back(tempLine);
				}
			}
			else {
				for (int j = 0; j < mapData[i + 4]; j++) {
					DrawCircle(renderer, mapData[i], mapData[i + 1], mapData[i + 2] + j);
				}
			}
		}
		// Minimum window size
		SDL_GetWindowPosition(window, &WindowX, &WindowY);
		if (WIDTH < 200) {
			SDL_SetWindowSize(window, 200, HEIGHT);
			SDL_SetWindowPosition(window, WindowX, WindowY);
		}
		if (HEIGHT < 200) {
			SDL_SetWindowSize(window, WIDTH, 200);
			SDL_SetWindowPosition(window, WindowX, WindowY);
		}

		// Line render - Background
		/*
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderDrawLine(renderer, 20, 30, 20, HEIGHT - 18);
		SDL_RenderDrawLine(renderer, 20, HEIGHT - 18, WIDTH - 20, HEIGHT - 18);

		SDL_SetRenderDrawColor(renderer, 127, 127, 127, 127);
		SDL_RenderDrawLine(renderer, 21, HEIGHT - 18, WIDTH - 20, 31);

		SDL_SetRenderDrawColor(renderer, 192, 192, 192, 127);
		SDL_RenderDrawLine(renderer, 20, 30, WIDTH - 20, 30);
		SDL_RenderDrawLine(renderer, WIDTH - 20, 30, WIDTH - 20, HEIGHT - 18);*/
		// Line render - Graph
		// Graphable area should be: 21,31 to 780,581 -> 759;550
		// 0,0 is top left
		/*
		for (int i = 1; i < WIDTH - 42; i++) {
			SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
			SDL_DrawThickLine(renderer, 20 + i, (HEIGHT - 20) - graphList1[i - 1], 22 + i, (HEIGHT - 20) - graphList1[i], 2);
//			SDL_RenderDrawLine(renderer, 20 + i, (HEIGHT - 20) - graphList1[i - 1], 22 + i, (HEIGHT - 20) - graphList1[i]);
			SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
			SDL_DrawThickLine(renderer, 20 + i, (HEIGHT - 20) - graphList2[i - 1], 22 + i, (HEIGHT - 20) - graphList2[i], 3);
//			SDL_RenderDrawLine(renderer, 20 + i, (HEIGHT - 20) - graphList2[i - 1], 22 + i, (HEIGHT - 20) - graphList2[i]);
		}
		*/

		// Pixel render
		//SDL_UpdateTexture(PxTexture, NULL, pixels, 800 * sizeof(Uint32));
		//SDL_RenderCopy(renderer, PxTexture, NULL, NULL);

		// Sprite render
		sprrect = { mainSprite.x,mainSprite.y,80,80 };
		if (SDL_RenderCopy(renderer, sprite_tex, NULL, &sprrect) != 0) {
			cout << "Error SDL_RenderCopy-ing:" << SDL_GetError();
			return -2;
		}


		// frame count
		string framestr = to_string(frame);
		TTFsurface = TTF_RenderText_Solid(Arial, framestr.c_str(), FColour);
		TTFtexture = SDL_CreateTextureFromSurface(renderer, TTFsurface);
		SDL_QueryTexture(TTFtexture, NULL, NULL, &texW, &texH);
		txtrect = { 0, 0, texW, texH };
		if (SDL_RenderCopy(renderer, TTFtexture, NULL, &txtrect) != 0) {
			cout << "Error SDL_RenderCopy-ing: " << SDL_GetError();
			return -2;
		}
		//framestr = "FPS Cap: " + to_string(FPSCap);
		//TTFsurface = TTF_RenderText_Solid(Arial, framestr.c_str(), FColour);
		//TTFtexture = SDL_CreateTextureFromSurface(renderer, TTFsurface);
		//SDL_QueryTexture(TTFtexture, NULL, NULL, &texW, &texH);
		//txtrect = { WIDTH - texW - 5, 0, texW, texH };
		//if (SDL_RenderCopy(renderer, TTFtexture, NULL, &txtrect) != 0) {
		//	cout << "Error SDL_RenderCopy-ing: " << SDL_GetError();
		//	return -2;
		//}

		// "submit"
		SDL_RenderPresent(renderer);

		// cleanup
		SDL_DestroyTexture(TTFtexture);
		SDL_FreeSurface(TTFsurface);

		// measurement
		auto stop1 = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop1 - start1);
		if ((double)duration.count() > 1000000) {
			cout << "Frame time: " << (double)duration.count() / 1000000 << "s";
		} else if ((double)duration.count() > 1000) {
			cout << "Frame time: " << (double)duration.count() / 1000 << "ms";
		} else {
			cout << "Frame time: " << (double)duration.count() << " microseconds";
		}
		if (((double)1000 / FPSCap) - (double)duration.count() / 1000 > 0) {
			SDL_Delay((uint32_t)floor(((double)1000 / FPSCap) - (double)duration.count() / 1000));
			cout << " - Wait time: " << ((double)1000 / FPSCap) - (double)duration.count() / 1000;
		}
		cout << " - FPS: " << 1000 / ((double)duration.count() / 1000) << " - FPS Cap: " << FPSCap << " - Frame: " << frame;
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