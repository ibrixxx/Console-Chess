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
    string getNaziv() {return naziv;}
    bool getBoja() {return boja;}
    int getRed() {return red;}
    int getKolona() {return kolona;}
    virtual bool Igraj(int red, int kolona) = 0;
    virtual Figura* Clone() const = 0;
    virtual void Pomjeri(int r, int k) = 0;
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
};

inline bool Pijun::Igraj(int red, int kolona){
    if(red>8 || red<0 || kolona>8 || kolona<0)
        throw logic_error("neispravne koordinate!");
    if(prviPozez){
        this->prviPozez = false;
        if(this->getNaziv() == "BP"){
            if((this->getRed() == red-2 && this->getKolona() == kolona) ||
               (this->getRed() == --red && this->getKolona() == kolona))
                return true;
            else
                return false;
        }
        else{
            if((this->getRed() == red+2 && this->getKolona() == kolona) ||
               (this->getRed() == ++red && this->getKolona() == kolona))
                return true;
            else
                return false;
        }
    }
    else{
        if(this->getNaziv() == "BP"){
            if(this->getRed() == --red && this->getKolona() == kolona)
                return true;
            else
                return false;
        }
        else{
            if(this->getRed() == ++red && this->getKolona() == kolona)
                return true;
            else
                return false;
        }
    }
}



class SahovskaPloca {
    vector<vector<Figura*>> ploca;
public:
    SahovskaPloca();
    void OdigrajPotez(int r1, int k1, int r2, int k2);
    void Ispisi();
    friend void Ispisi(const SahovskaPloca &s, ofstream &upis);
    bool DaLiPreskace(int r1, int k1, int r2, int k2);
};

inline SahovskaPloca::SahovskaPloca() : ploca(8, vector<Figura*>(8, nullptr)) {
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
    if(ploca[r1][k1] == nullptr)
        cout<<"polje ["<<r1<<", "<<k1<<"] je prazno!"<<endl;
    if(ploca[r1][k1]->Igraj(r2,k2)){
        if(!(DaLiPreskace(r1, k1, r2, k2))){
            if(ploca[r2][k2] == nullptr){
                ploca[r2][k2] = ploca[r1][k1]->Clone();
                ploca[r2][k2]->Pomjeri(r2, k2);
                delete ploca[r1][k1];
                ploca[r1][k1] = nullptr;
            }
            else{
                if(ploca[r2][k2]->getBoja() != ploca[r1][k1]->getBoja()){
                    delete ploca[r2][k2];
                    ploca[r2][k2] = ploca[r1][k1]->Clone();
                    ploca[r2][k2]->Pomjeri(r2, k2);
                    delete ploca[r1][k1];
                    ploca[r1][k1] = nullptr;
                }
                else
                    cout<<"na polju ["<<r1<<", "<<k1<<"] je figura iste boje i ne moze se jesti!"<<endl;
            }
        }
        else
            cout<<"figura "<<ploca[r1][k1]->getNaziv()<<" ne smije da preskoèi drugu figuru, pokušajte ponovo"<<endl;
    }
    else
        cout<<"neispravan potez za figuru "<<ploca[r1][k1]->getNaziv()<<endl;
}

bool SahovskaPloca::DaLiPreskace(int r1, int k1, int r2, int k2){
    int minR(min(r1,r2));
    int maxR(max(r1,r2));
    int minK(min(k1,k2));
    int maxK(max(k1,k2));
    string imeFigure(ploca[r1][k1]->getNaziv());
    if(imeFigure == "CP" || imeFigure == "BP")
        if(ploca[r2][k2] != nullptr)
            return true;
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

void SahovskaPloca::Ispisi(){
    for(int i(0); i<8; i++){
        for(int j(0); j<8; j++){
            if(ploca[i][j] == nullptr)
                cout<<" [] ";
            else
                cout<<ploca[i][j];
        }
        cout<<endl;
        cout<<endl;
    }
}

void Ispisi(const SahovskaPloca &s, ofstream &upis){
    for(int i(0); i<8; i++){
        for(int j(0); j<8; j++){
            if(s.ploca[i][j] == nullptr)
                upis<<" [] ";
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
        sah.OdigrajPotez(2,2,3,2);
        sah.OdigrajPotez(8,6,7,7);
        sah.OdigrajPotez(3,1,4,3);
        sah.OdigrajPotez(7,7,1,1);
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
