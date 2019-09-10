#include <iostream>
#include <string>
#include <limits>
#include <fstream>

using namespace std;

class Produto
{
private:
  string nome;
  unsigned preco;
public:
  inline Produto(const string& N="", unsigned P=0): nome(N), preco(P) {}

  bool ler(istream &I);
  void salvar(ostream &O) const;
  void digitar();
  // Define a funcao imprimir como sendo salvar em cout
  inline void imprimir() const {salvar(cout);}
};

bool Produto :: ler(istream &I){

     unsigned valor=0, sob=0;

     I.ignore(numeric_limits <streamsize>::max(), '"');
     getline(I, nome, '"');
     I.ignore(numeric_limits <streamsize>::max(), ';');
     I.ignore(numeric_limits <streamsize>::max(), '$');
     I >> valor;
     I.ignore(numeric_limits <streamsize>::max(), '.');
     I >> sob;
     preco = valor*100 + sob;
}

void Produto :: salvar(ostream &O) const{
    unsigned Prec, res;
    Prec = preco/100;
    res = preco%100;
     O << '"' << nome << '"' << ';' << '$' << Prec << '.' << res << ';';
}

void Produto :: digitar(){
   int teste;
   cout << "Digite o nome do Produto: ";
   getline(cin,nome);
   do{
   cout << "Digite o Preco do Produto: ";
   cin >> teste;
   }while(teste < 0);
   preco = teste;
}



inline istream& operator>>(istream &I, Produto &P) {P.digitar(); return I;}
inline ostream& operator<<(ostream &O, const Produto &P) {P.salvar(O); return O;}

class DVD: public Produto{

private:
    unsigned duracao;
public:
    inline DVD(const string& N="", unsigned P=0, int D=0): Produto(N,P), duracao(D) {}
    bool ler (istream &L);
    void salvar(ostream &S) const;
    void digitar();
    void imprimir() const;
};

bool DVD :: ler(istream &I){

  //   if(arq.is_open) verifica se o arquivo pode ser aberto
     string teste;
     getline(I, teste, ' ');
     cout << teste <<endl;
     if (teste == "D:"){
     Produto :: ler(I);
    I.ignore(numeric_limits <streamsize>::max(), ';');
     I >> duracao;
     }
     else return false;
}

void DVD :: salvar(ostream &S)const{
     S << "D: ";
     Produto :: salvar(S);
     S << duracao;

}

void DVD :: digitar(){
    int teste;
    Produto :: digitar();
    do{
    cout << "Digite a duracao do DVD: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> teste;
    }while(teste < 0);
    duracao = teste;
}

void DVD :: imprimir() const{
    cout << "D: ";
    Produto :: imprimir();
    cout << duracao;

}

inline istream& operator>>(istream &I, DVD &C) {C.digitar(); return I;}
inline ostream& operator<<(ostream &S, const DVD &C) {C.salvar(S); return S;}

int main()
{ //ofstream arq("saida.txt");
   ifstream arq2("saida.txt");
    DVD P;
    P.ler(arq2);
    P.imprimir();

    return 0;
}
