#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;



class Figura {
protected:
    string naziv;
    bool boja;
    int red, kolona;
public:
    Figura(bool boja, int red, int kolona):
        boja(boja), red(red), kolona(kolona) {}
    virtual ~Figura() {};
    string getNaziv() const {return naziv;}
    bool getBoja() const {return boja;}
    int getRed() const {return red;}
    int getKolona() const {return kolona;}
    virtual bool Igraj(int red, int kolona) = 0;
    virtual Figura* Clone() const = 0;
    virtual void Pomjeri(int r, int k) = 0;
    virtual bool DaLiJede(int k1, int k2) = 0;
    Figura& operator=(const Figura& f);
};

ostream& operator<<(ostream& ispis, Figura* f){
    ispis<<' '<<f->getNaziv()<<' ';
    return ispis;
}

Figura& Figura::operator=(const Figura& f){
    naziv = f.naziv;
    boja = f.boja;
    red = f.red;
    kolona = f.kolona;
    return *this;
}


class Kralj: public Figura {
public:
    Kralj(bool boja, int red, int kolona): Figura(boja, red, kolona)
    {
        if(boja == 1)
            this->naziv = "BK";
        else
            this->naziv = "CK";
    }
    bool Igraj(int red, int kolona);
    Figura* Clone() const {return new Kralj(*this);}
    void Pomjeri(int r, int k) {red = r; kolona = k;}
    bool DaLiJede(int k1, int k2) {}
};

inline bool Kralj::Igraj(int red, int kolona){
    if(red>8 || red<0 || kolona>8 || kolona<0)
        throw logic_error("neispravne koordinate!");
    if(abs(red - this->getRed()) > 1 || abs(kolona - this->getKolona()) > 1)
        return false;
    else
        return true;
}



class Dama: public Figura {
public:
    Dama(bool boja, int red, int kolona): Figura(boja, red, kolona)
    {
        if(boja == 1)
            this->naziv = "BD";
        else
            this->naziv = "CD";
    }
    bool Igraj(int red, int kolona);
    Figura* Clone() const {return new Dama(*this);}
    void Pomjeri(int r, int k) {red = r; kolona = k;}
    bool DaLiJede(int k1, int k2) {}
};

inline bool Dama::Igraj(int red, int kolona){
    if(red>8 || red<0 || kolona>8 || kolona<0)
        throw logic_error("neispravne koordinate!");
    if(red == this->getRed() || kolona == this->getKolona())
        return true;
    else if((red-kolona) == (this->getRed()-this->getKolona()))
        return true;
    else if((red+kolona) == (this->getRed()+this->getKolona()))
        return true;
    else
        return false;
}



class Laufer: public Figura {
public:
    Laufer(bool boja, int red, int kolona): Figura(boja, red, kolona)
    {
        if(boja == 1)
            this->naziv = "BL";
        else
            this->naziv = "CL";
    }
    bool Igraj(int red, int kolona);
    Figura* Clone() const {return new Laufer(*this);}
    void Pomjeri(int r, int k) {red = r; kolona = k;}
    bool DaLiJede(int k1, int k2) {}
};

inline bool Laufer::Igraj(int red, int kolona){
    if(red>8 || red<0 || kolona>8 || kolona<0)
        throw logic_error("neispravne koordinate!");
    if((red-kolona) == (this->getRed()-this->getKolona()))
        return true;
    else if((red+kolona) == (this->getRed()+this->getKolona()))
        return true;
    else
        return false;
}



class Skakac: public Figura {
public:
    Skakac(bool boja, int red, int kolona): Figura(boja, red, kolona)
    {
        if(boja == 1)
            this->naziv = "BS";
        else
            this->naziv = "CS";
    }
    bool Igraj(int red, int kolona);
    Figura* Clone() const {return new Skakac(*this);}
    void Pomjeri(int r, int k) {red = r; kolona = k;}
    bool DaLiJede(int k1, int k2) {}
};

inline bool Skakac::Igraj(int red, int kolona){
    if(red>8 || red<0 || kolona>8 || kolona<0)
        throw logic_error("neispravne koordinate!");
    if(abs(red - this->getRed()) == 1 && abs(kolona - this->getKolona()) == 2)
        return true;
    else if(abs(red - this->getRed()) == 2 && abs(kolona - this->getKolona()) == 1)
        return true;
    else
        return false;
}



class Top: public Figura {
public:
    Top(bool boja, int red, int kolona): Figura(boja, red, kolona)
    {
        if(boja == 1)
            this->naziv = "BT";
        else
            this->naziv = "CT";
    }
    bool Igraj(int red, int kolona);
    Figura* Clone() const {return new Top(*this);}
    void Pomjeri(int r, int k) {red = r; kolona = k;}
    bool DaLiJede(int k1, int k2) {}
};

inline bool Top::Igraj(int red, int kolona){
    if(red>8 || red<0 || kolona>8 || kolona<0)
        throw logic_error("neispravne koordinate!");
    if(red == this->getRed() || kolona == this->getKolona())
        return true;
    else
        return false;
}



class Pijun: public Figura {
    bool prviPozez;
public:
    Pijun(bool boja, int red, int kolona): prviPozez(true), Figura(boja, red, kolona)
    {
        if(boja == 1)
            this->naziv = "BP";
        else
            this->naziv = "CP";
    }
    bool Igraj(int red, int kolona);
    Figura* Clone() const {return new Pijun(*this);}
    void Pomjeri(int r, int k) {red = r; kolona = k;}
    bool getPrviPotez() const {return prviPozez;}
    void setPrviPotez(bool b) {prviPozez = b;}
    bool DaLiJede(int k1, int k2) {if(++k1 == k2 || (k1 -= 2) == k2) return true; return false;}
};

inline bool Pijun::Igraj(int red, int kolona){
    if(red>8 || red<0 || kolona>8 || kolona<0)
        throw logic_error("neispravne koordinate!");
    if(this->getPrviPotez()){
        this->setPrviPotez(false);
        if(this->getNaziv() == "BP"){
            if((this->getRed() == red-2 && this->getKolona() == kolona) ||
               (this->getRed() == --red && this->getKolona() == kolona))
                return true;
            return false;
        }
        else{
            if((this->getRed() == red+2 && this->getKolona() == kolona) ||
               (this->getRed() == ++red && this->getKolona() == kolona))
                return true;
            return false;
        }
    }
    else{
        if(this->getNaziv() == "BP"){
            if(this->getRed() == --red && this->getKolona() == kolona)
                return true;
            if(this->getRed() == red && (this->getKolona() == --kolona || this->getKolona() == (kolona += 2)))
                return true;
            return false;
        }
        else{
            if(this->getRed() == ++red && this->getKolona() == kolona)
                return true;
            if(this->getRed() == red && (this->getKolona() == --kolona || this->getKolona() == (kolona += 2)))
                return true;
            return false;
        }
    }
}

struct PozicijaKralja {
    int red;
    int kolona;
    PozicijaKralja(int r, int k): red(r), kolona(k) {}
    int dajRed() const {return red;}
    int dajKolonu() const {return kolona;}
};

static int potez(0);

class SahovskaPloca {
    vector<vector<Figura*>> ploca;
    PozicijaKralja crni;
    PozicijaKralja bijeli;
    bool podSahom;
public:
    SahovskaPloca();
    void OdigrajPotez(int r1, int k1, int r2, int k2);
    void Ispisi();
    friend void Ispisi(const SahovskaPloca &s, ofstream &upis);
    bool DaLiPreskace(int r1, int k1, int r2, int k2);
    bool DaLiJeSah(Figura* figura);
};

inline SahovskaPloca::SahovskaPloca() : ploca(8, vector<Figura*>(8, nullptr)), bijeli(0,3), crni(7,3), podSahom(false) {
    try{
        ploca[0][0] = new Top(1,0,0);
        ploca[0][1] = new Skakac(1,0,1);
        ploca[0][2] = new Laufer(1,0,2);
        ploca[0][3] = new Kralj(1,0,3);
        ploca[0][4] = new Dama(1,0,4);
        ploca[0][5] = new Laufer(1,0,5);
        ploca[0][6] = new Skakac(1,0,6);
        ploca[0][7] = new Top(1,0,7);
        for(int i(0); i<8; i++)
            ploca[1][i] = new Pijun(1,1,i);
        ploca[7][0] = new Top(0,7,0);
        ploca[7][1] = new Skakac(0,7,1);
        ploca[7][2] = new Laufer(0,7,2);
        ploca[7][3] = new Kralj(0,7,3);
        ploca[7][4] = new Dama(0,7,4);
        ploca[7][5] = new Laufer(0,7,5);
        ploca[7][6] = new Skakac(0,7,6);
        ploca[7][7] = new Top(0,7,7);
        for(int i(0); i<8; i++)
            ploca[6][i] = new Pijun(0,6,i);
    }
    catch(bad_alloc){
        throw "nema memorije";
    }
}

void SahovskaPloca::OdigrajPotez(int r1, int k1, int r2, int k2){
    r1--;
    k1--;
    r2--;
    k2--;
    if(ploca[r1][k1] == nullptr){
        cout<<"polje ["<<r1<<", "<<k1<<"] je prazno!"<<endl;
        return;
    }
    if(potez % 2 == 1 && ploca[r1][k1]->getBoja()){
        cout<<"crni je na redu"<<endl;
        return;
    }
    if(!(ploca[r1][k1]->getBoja()) && potez % 2 == 0){
        cout<<"bijeli je na redu"<<endl;
        return;
    }
    if(ploca[r1][k1]->Igraj(r2,k2)){
        if(!(DaLiPreskace(r1, k1, r2, k2))){
            if(!(podSahom)){
                if(ploca[r2][k2] == nullptr){
                    if((ploca[r1][k1]->getNaziv() == "CP" || ploca[r1][k1]->getNaziv() == "BP") && ploca[r1][k1]->DaLiJede(k1,k2))
                        cout<<"neispravan potez za pijuna"<<endl;
                    else{
                        ploca[r2][k2] = ploca[r1][k1]->Clone();
                        ploca[r2][k2]->Pomjeri(r2, k2);
                        delete ploca[r1][k1];
                        ploca[r1][k1] = nullptr;
                        if(DaLiJeSah(ploca[r2][k2])){
                            podSahom = true;
                        }
                        if(ploca[r2][k2]->getNaziv() == "CK"){
                            crni.red = r2;
                            crni.kolona = k2;
                        }
                        if(ploca[r2][k2]->getNaziv() == "BK"){
                            bijeli.red = r2;
                            bijeli.kolona = k2;
                        }
                    }
                }
                else{
                    if(ploca[r2][k2]->getBoja() != ploca[r1][k1]->getBoja()){
                        delete ploca[r2][k2];
                        ploca[r2][k2] = ploca[r1][k1]->Clone();
                        ploca[r2][k2]->Pomjeri(r2, k2);
                        delete ploca[r1][k1];
                        ploca[r1][k1] = nullptr;
                        if(DaLiJeSah(ploca[r2][k2])){
                            podSahom = true;
                        }
                        if(ploca[r2][k2]->getNaziv() == "CK"){
                            crni.red = r2;
                            crni.kolona = k2;
                        }
                        if(ploca[r2][k2]->getNaziv() == "BK"){
                            bijeli.red = r2;
                            bijeli.kolona = k2;
                        }
                    }
                    else
                        cout<<"na polju ["<<r1<<", "<<k1<<"] je figura iste boje i ne moze se jesti!"<<endl;
                }
            }
            else{
                cout<<"Kralj vam je pod šahom!"<<endl;
                if(ploca[r2][k2] == nullptr){
                    if((ploca[r1][k1]->getNaziv() == "CP" || ploca[r1][k1]->getNaziv() == "BP") && ploca[r1][k1]->DaLiJede(k1,k2))
                        cout<<"neispravan potez za pijuna"<<endl;
                    else{
                        ploca[r2][k2] = ploca[r1][k1]->Clone();
                        ploca[r2][k2]->Pomjeri(r2, k2);
                        if(!(DaLiJeSah(ploca[r2][k2]))){
                            delete ploca[r1][k1];
                            ploca[r1][k1] = nullptr;
                            podSahom = false;
                        }
                        else{
                            ploca[r2][k2] = nullptr;
                            cout<<"pod šahom ste!"<<endl;
                        }
                        if(ploca[r2][k2]->getNaziv() == "CK"){
                            crni.red = r2;
                            crni.kolona = k2;
                        }
                        if(ploca[r2][k2]->getNaziv() == "BK"){
                            bijeli.red = r2;
                            bijeli.kolona = k2;
                        }
                    }
                }
                else{
                    if(ploca[r2][k2]->getBoja() != ploca[r1][k1]->getBoja()){
                        Figura* pom = ploca[r2][k2];
                        ploca[r2][k2] = ploca[r1][k1]->Clone();
                        ploca[r2][k2]->Pomjeri(r2, k2);
                        if(!(DaLiJeSah(ploca[r2][k2]))){
                            delete ploca[r2][k2];
                            delete ploca[r1][k1];
                            ploca[r1][k1] = nullptr;
                            podSahom = false;
                        }
                        else{
                            ploca[r2][k2] = pom;
                            delete pom;
                            cout<<"pod šahom ste!"<<endl;

                        }
                        if(ploca[r2][k2]->getNaziv() == "CK"){
                            crni.red = r2;
                            crni.kolona = k2;
                        }
                        if(ploca[r2][k2]->getNaziv() == "BK"){
                            bijeli.red = r2;
                            bijeli.kolona = k2;
                        }
                    }
                    else
                        cout<<"na polju ["<<r1<<", "<<k1<<"] je figura iste boje i ne moze se jesti!"<<endl;
                }
            }
        }
        else
            cout<<"figura "<<ploca[r1][k1]->getNaziv()<<" ne smije da preskoči drugu figuru, pokušajte ponovo"<<endl;
    }
    else
        cout<<"neispravan potez za figuru "<<ploca[r1][k1]->getNaziv()<<endl;
    potez++;
}

bool SahovskaPloca::DaLiPreskace(int r1, int k1, int r2, int k2){
    int minR(min(r1,r2));
    int maxR(max(r1,r2));
    int minK(min(k1,k2));
    int maxK(max(k1,k2));
    string imeFigure(ploca[r1][k1]->getNaziv());
    if(imeFigure == "CD" || imeFigure == "BD" || imeFigure == "CT" || imeFigure == "BT")
    {
        for(int i(minR+1); i<maxR; i++)
            if(ploca[i][k1] != nullptr)
                return true;
        for(int i(minK+1); i<maxK; i++)
            if(ploca[r1][i] != nullptr)
                return true;
    }
    if(imeFigure == "CD" || imeFigure == "BD" || imeFigure == "CL" || imeFigure == "BL")
    {
        if(r1 < r2)
            if(k1 < k2)
                for(int i(minR+1); i<maxR; i++)
                    if(ploca[i][k1+i-r1] != nullptr)
                        return true;
            else
                for(int i(minR+1); i<maxR; i++)
                    if(ploca[i][k1-i+r1] != nullptr)
                        return true;
        else
            if(k1 < k2)
                for(int i(maxR-1); i>=minR; i--)
                    if(ploca[i][k1+i-r1] != nullptr)
                        return true;
            else
                for(int i(maxR-1); i>=minR; i--)
                    if(ploca[i][k1-i+r1] != nullptr)
                        return true;
    }
    return false;
}

bool SahovskaPloca::DaLiJeSah(Figura* figura){
    if(figura->getBoja())
        if(figura->Igraj(crni.dajRed(), crni.dajKolonu()) && (DaLiPreskace(figura->getRed(),figura->getKolona(),crni.dajRed(),crni.dajKolonu())))
            return true;
    if(figura->Igraj(bijeli.dajRed(), bijeli.dajKolonu()) && (DaLiPreskace(figura->getRed(),figura->getKolona(),bijeli.dajRed(),bijeli.dajKolonu())))
        return true;
    return false;
}

void SahovskaPloca::Ispisi(){
    for(int i(0); i<9; i++){
        if(i == 0)
            cout<<setw(4)<<setfill(' ');
        else
            cout<<setw(4)<<i;
    }
    cout<<endl;
    for(int i(0); i<8; i++){
        cout<<i+1;
        for(int j(0); j<8; j++){
            if(ploca[i][j] == nullptr){
                if((i+j) % 2 == 0)
                    cout<<" [] ";
                else
                    cout<<" ## ";
            }
            else
                cout<<ploca[i][j];
        }
        cout<<endl;
        cout<<endl;
    }
}

void Ispisi(const SahovskaPloca &s, ofstream &upis){
    for(int i(0); i<9; i++){
        if(i == 0)
            upis<<setw(4)<<setfill(' ');
        else
            upis<<setw(4)<<i;
    }
    upis<<endl;
    for(int i(0); i<8; i++){
        upis<<i+1;
        for(int j(0); j<8; j++){
            if(s.ploca[i][j] == nullptr){
                if((i+j) % 2 == 0)
                    upis<<" [] ";
                else
                    upis<<" ## ";
            }
            else
                upis<<s.ploca[i][j];
        }
        upis<<'\n';
        upis<<'\n';
    }
}

int main(){
    try{
        SahovskaPloca sah;
        sah.Ispisi();
        cout<<setw(32)<<setfill('-')<<'-'<<endl;
        sah.OdigrajPotez(1,2,3,1);
        sah.OdigrajPotez(7,7,5,7);
        sah.OdigrajPotez(2,6,4,6);
        sah.OdigrajPotez(5,7,4,6);
        sah.OdigrajPotez(2,2,4,2);
        sah.OdigrajPotez(8,6,7,7);
        sah.OdigrajPotez(2,7,3,7);
        sah.OdigrajPotez(7,7,1,1);
        sah.OdigrajPotez(3,7,4,6);
        sah.OdigrajPotez(8,5,8,6);
        sah.OdigrajPotez(2,5,4,5);
        sah.OdigrajPotez(8,6,7,7);
        sah.OdigrajPotez(4,5,5,5);
        sah.OdigrajPotez(7,7,4,7);
        sah.OdigrajPotez(1,5,2,5);
        sah.Ispisi();
        ofstream ispis;
        ispis.open("sah.txt");
        Ispisi(sah, ispis);
        ispis.close();
    }
    catch(...){
    }

    return 0;
}
