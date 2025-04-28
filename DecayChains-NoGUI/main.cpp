#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;
using namespace chrono;
using namespace this_thread;


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

int main() {

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

	while (getline(getStart, listOutput)) {
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
		cout << "\n-----------------------------------------\n";
		decayChain.clear();
		alternateDecayChains.clear();
		
	}
}