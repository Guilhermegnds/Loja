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
     Produto :: ler(I);
     I.ignore(numeric_limits <streamsize>::max(), '"');
     getline(I, autor, '"');
}

void Livro :: salvar(ostream &S)const{

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

    Produto :: imprimir();
    cout << '"' << autor << '"';

}

inline istream& operator>>(istream &I, Livro &L) {L.digitar(); return I;}
inline ostream& operator<<(ostream &S, const Livro &L) {L.salvar(S); return S;}


class ListaLivro: public Produto
{
private:
  Livro *x;
  unsigned N;
public:
  // Inclua os construtores, destrutor e operadores necessarios
  inline ListaLivro (const string& N="", unsigned P=0, const string &M="", Livro &X = NULL, unsigned n=0): x(X), N(n) {}
  explicit ListaLivro(ListaLivro &LL);
  ~ListaLivro ();
  void operator=(const ListaLivro &L);

  istream& operator>>(istream &I, ListaLivro &L);
  ostream& operator<<(ostream &S, const ListaLivro &L);

  void incluir(const Livro &L);
  bool excluir(unsigned id);

  bool ler(istream &I);
  void salvar(ostream &O) const;
  void imprimir() const;
};

explicit ListaLivro :: ListaLivro (ListaLivro &LL){

if(LL.N != 0){
        N = LL.N
    for (unsigned i = 0, i<N, i++ ) x[i] = LL.x[i]
}
}

~ListaLivro :: ListaLivro(ListaLivro &LL){

if (x!=NULL) delete[] x;
  N = 0;
  x = NULL;
}

void operator=(const ListaLivro &L){

N = L.N
for (unsigned i=0; i<N; i++) x[i]=L.x[i];

}

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
