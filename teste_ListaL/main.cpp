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


class ListaLivro: public Livro
{
private:
  Livro *x;
  unsigned N;
public:
  // Inclua os construtores, destrutor e operadores necessarios
  inline ListaLivro (const string& O="", unsigned P=0, const string &M="", Livro *X = NULL, unsigned n=0): Livro(O,P,M), x(X), N(n) {}
  ListaLivro(const ListaLivro &LL);
  ~ListaLivro ();
  void operator=(const ListaLivro &L);

//  istream& operator>>(istream &I, ListaLivro &L);
  //ostream& operator<<(ostream &S, const ListaLivro &L);

  void incluir(const Livro &L);
  bool excluir(unsigned id);

  bool ler(istream &I);
  void salvar(ostream &O) const;
  void imprimir() const;
};

ListaLivro :: ListaLivro ( const ListaLivro &LL){

if(LL.N != 0){
        N = LL.N;
     for (unsigned i=0; i<N; i++) {
        x[i] = LL.x[i];
        }
}
}

ListaLivro :: ~ListaLivro(){

if (x!=NULL) delete[] x;
  N = 0;
  x = NULL;
}

void ListaLivro :: incluir(const Livro &L){
      unsigned Num=N;
      Livro *prov = new Livro[Num+1];
      for (unsigned i=0; i<Num; i++) prov[i] = x[i];
      prov[N] = L;
      Num++;
      N = Num;
      if (x != NULL) delete[] x;
      x = NULL;
      x = prov;
      prov = NULL;

}

bool ListaLivro :: ler(istream &I){
     string pc("");
     getline(I, pc, ' ');
     I >> N;
     if (pc == "LISTALIVRO" && N != 0){
     for (unsigned i=0; i<N; i++){
     Livro :: ler(I);
     return true;
     }
     }
     else return false;
}

void ListaLivro :: salvar(ostream &O) const{
      O << "LISTALIVRO " << N << endl;
      for (unsigned i=0; i<N; i++){
            Livro :: salvar(O);
            O << endl;
          }
}

void ListaLivro :: imprimir()const{
    unsigned i;
    cout << ">> LIVROS:" << N << endl;

    for(i=0; i<N; i++){
        cout << i << ") ";
        Livro :: imprimir();
        cout << endl;
}
}

int main()
{   ofstream arq("saida.txt");
  //  ifstream arq2("saida.txt");
    ListaLivro P;
    Livro L;
    L.digitar();
    L.imprimir();
    P.incluir(L);
    P.imprimir();

    return 0;
}

