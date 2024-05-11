#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

// Kintamuosius kuriuos reikia ávesti ir iðvesti norodþiau èia
int m;
int taðkai[100][2];
int atkarpos[100][4];
int trikampiai[100][6];
int lygiagrecios = 0;
double suma = 0;
double tats = 1000;
int trumpx1, trumpy1, trumpx2, trumpy2;
double perimetruSuma = 0;

void LygiagreciosAtkarpos(int& ux1, int& ux2, int& lygiagrecios) {
	if (ux1 == ux2) {
		lygiagrecios++;
	}
}

double AtkarposAtstumas(int& ux1, int& uy1, int& ux2, int& uy2) {
	return sqrt(pow(ux2 - ux1, 2) + pow(uy2 - uy1, 2));
}

void AtkarpuIlgiuSuma(int& ux1, int& uy1, int& ux2, int& uy2, double& suma) {
	if ((ux1 > 0 && ux2 < 0) || (ux1 < 0 && ux2 > 0)) {
		suma += AtkarposAtstumas(ux1, uy1, ux2, uy2);
	}
}

bool ArPriklausoKetvirtamKetvirciui(int ux1, int uy1, int ux2, int uy2) {
	return (ux1 > 0 && ux2 > 0 && uy1 < 0 && uy2 < 0);
}

void TrumpiausiaAtkarpa(int& ux1, int& uy1, int& ux2, int& uy2, double& tats, int& trumpx1, int& trumpy1, int& trumpx2, int& trumpy2) {
	if (ArPriklausoKetvirtamKetvirciui(ux1, uy1, ux2, uy2))
	{
		if (AtkarposAtstumas(ux1, uy1, ux2, uy2) < tats)
		{
			tats = AtkarposAtstumas(ux1, uy1, ux2, uy2);
			trumpx1 = ux1;
			trumpy1 = uy1;
			trumpx2 = ux2;
			trumpy2 = uy2;
		}
	}
}

int TrikampioPerimetras(int& ox1, int& oy1, int& ox2, int& oy2, int& ox3, int& oy3) {
	return sqrt(pow(ox2 - ox1, 2) + pow(oy2 - oy1, 2)) + sqrt(pow(ox3 - ox1, 2) + pow(oy3 - oy1, 2)) + sqrt(pow(ox3 - ox2, 2) + pow(oy3 - oy2, 2));
}

void PerimetruSuma(int& ox1, int& oy1, int& ox2, int& oy2, int& ox3, int& oy3, double& perimetruSuma) {
	if (ox3 == 0) {
		perimetruSuma += TrikampioPerimetras(ox1, oy1, ox2, oy2, ox3, oy3);
	}
}

void IvedimasIsFailo() {
	ifstream fin("Duomenys.txt");
	fin >> m;

	for (int i = 0; i < m; i++) {
		int a;
		fin >> a;

		if (a == 2) {
			fin >> taðkai[i][0] >> taðkai[i][1];
		}
		else if (a == 4) {
			fin >> atkarpos[i][0] >> atkarpos[i][1] >> atkarpos[i][2] >> atkarpos[i][3];
		}
		else if (a == 6) {
			fin >> trikampiai[i][0] >> trikampiai[i][1] >> trikampiai[i][2] >> trikampiai[i][3] >> trikampiai[i][4] >> trikampiai[i][5];
		}
	}
}

void IsvedimasIFaila() {
	ofstream fout("Rezultatai.txt");

	fout << "-------------- Rezultatai -------------" << endl;
	fout << "Figûra    |  Koordinatës (x, y)" << endl;
	fout << "---------------------------------------" << endl;

	for (int i = 0; i < m; i++) {
		if (taðkai[i][0] != 0) {
			fout << "Taðkas    |  (" << taðkai[i][0] << ", " << taðkai[i][1] << ")" << endl;
		}
		if (atkarpos[i][0] != 0) {
			fout << "Atkarpa   |  (" << atkarpos[i][0] << ", " << atkarpos[i][1] << "); (" << atkarpos[i][2] << ", " << atkarpos[i][3] << ")" << endl;
		}
		if (trikampiai[i][0] != 0) {
			fout << "Trikampis |  (" << trikampiai[i][0] << ", " << trikampiai[i][1] << "); (" << trikampiai[i][2] << ", " << trikampiai[i][3] << "); (" << trikampiai[i][4] << ", " << trikampiai[i][5] << ")" << endl;
		}
	}

	fout << "---------------------------------------" << endl;
	fout << endl << "Atkarpø lygiagreèiø y aðiai: " << lygiagrecios << endl;
	fout << "Atkarpø, kertanèiø y aðá, ilgiø suma: " << suma << endl;
	if (tats == 1000) {
		fout << "Trumpiausios atkarpos, priklausanèios ketvirtam ketvirèiui, nëra" << endl;
	}
	else {
		fout << "Trumpiausios atkarpos, priklausanèios ketvirtam ketvirèiui, koordinatës: (" << trumpx1 << ", " << trumpy1 << "), (" << trumpx2 << ", " << trumpy2 << ")" << endl;
	}
	fout << "Trikampiø perimetrø suma: " << perimetruSuma << endl;
}

int main() {
	setlocale(LC_ALL, "lithuanian");

	IvedimasIsFailo();

	for (int i = 0; i < m; i++) {
		if (atkarpos[i][0] != 0) {
			int ux1 = atkarpos[i][0], uy1 = atkarpos[i][1], ux2 = atkarpos[i][2], uy2 = atkarpos[i][3];
			LygiagreciosAtkarpos(ux1, ux2, lygiagrecios);
			AtkarpuIlgiuSuma(ux1, uy1, ux2, uy2, suma);
			TrumpiausiaAtkarpa(ux1, uy1, ux2, uy2, tats, trumpx1, trumpy1, trumpx2, trumpy2);
		}
		if (trikampiai[i][0] != 0) {
			int ox1 = trikampiai[i][0], oy1 = trikampiai[i][1], ox2 = trikampiai[i][2], oy2 = trikampiai[i][3], ox3 = trikampiai[i][4], oy3 = trikampiai[i][5];
			perimetruSuma += TrikampioPerimetras(ox1, oy1, ox2, oy2, ox3, oy3);
		}
	}

	IsvedimasIFaila();

	return 0;
}