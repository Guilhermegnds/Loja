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

class Livro: public Produto{

private:
    string autor;

public:
    inline Livro(const string& N="", unsigned P=0, const string &M=""): Produto(N,P), autor(M) {}
    bool ler (istream &L);
    void salvar(ostream &S) const;
    void digitar();
    void imprimir() const;
};

bool Livro :: ler(istream &I){

  //   if(arq.is_open) verifica se o arquivo pode ser aberto
     string teste;
     getline(I, teste, ' ');
     cout << teste <<endl;
     if (teste == "L:"){
     Produto :: ler(I);
     I.ignore(numeric_limits <streamsize>::max(), '"');
     getline(I, autor, '"');
     }
     else return false;
}

void Livro :: salvar(ostream &S)const{

     S << "L: ";
     Produto :: salvar(S);
     S << '"' << autor << '"';

}

void Livro :: digitar(){

    Produto :: digitar();

    cout << "Digite o nome do autor: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, autor, '\n');
}

void Livro :: imprimir() const{

    cout << "L: ";
    Produto :: imprimir();
    cout << '"' << autor << '"';

}


inline istream& operator>>(istream &I, Livro &L) {L.digitar(); return I;}
inline ostream& operator<<(ostream &S, const Livro &L) {L.salvar(S); return S;}

int main()
{  // ofstream arq("saida.txt");
    ifstream arq2("saida.txt");
    Livro P;
    P.ler(arq2);
    P.imprimir();

    return 0;
}
