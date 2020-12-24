
#include <iostream>
#include <regex>

using namespace std;

class Atolye{
public:	
	Atolye();
	Atolye(string _ad, string _adres, int _uretim);
	int getBosMakineSayisi();
	void setParca(int parca);
	string getAd();
	void makineYazdir();

private:
	string ad = "";
	string adres = "";
	int makine[21];
	int uretim = 0;
	int parca = 0;
	int bosMakine = 21;
};

Atolye::Atolye()
{

}

Atolye::Atolye(string _ad, string _adres, int _uretim){
	ad = _ad;
	adres = _adres;
	uretim = _uretim;
	for(int i = 0; i < 21; i++){
		makine[i] = 0;
	}
}

string Atolye::getAd(){
	return ad;
}

void Atolye::makineYazdir(){
	for(int i = 0; i < 21; i++){
		std::cout << makine[i] << "-";
	}
	std::cout << std::endl;
}

int Atolye::getBosMakineSayisi(){
	return bosMakine;
}

void Atolye::setParca(int parca){	
	for(int i = 0; i < 21; i++){
		int geciciParca = parca;
		int isAta = uretim / 21;
		geciciParca -= isAta;
		if(geciciParca < 0){
			bosMakine--;
			makine[i] = parca;
			break;
		}
		else{
			bosMakine--;
			makine[i] = isAta;
		}
		parca -= isAta;
	}
}

int main(){
	Atolye a("bill01", "3. Cadde no:21", 210);
	Atolye b("bill02", "4. Cadde no:1", 105);
	Atolye c;
	a.setParca(25);
	b.setParca(59);
	int aBos = a.getBosMakineSayisi();
	int bBos = b.getBosMakineSayisi();
	a.makineYazdir();
	b.makineYazdir();
	cout << a.getAd() << " deki bos makine sayisi: " << aBos << endl;
	

	if(aBos > bBos){
		std::cout << a.getAd() << b.getAd() << " birbirinden farkli" << std::endl;
		std::cout << "Daha verimli olan: " << b.getAd() << std::endl;
		c = b;
	}
	else if(aBos == bBos){
		std::cout << a.getAd() << b.getAd() << " birbirine esit" << std::endl;
		c = b;
	}
	else{
		std::cout << a.getAd() << b.getAd() << " birbirinden farkli" << std::endl;
		std::cout << "Daha verimli olan: " << a.getAd() << endl;
		c = a;
	}

	return 0;
}
