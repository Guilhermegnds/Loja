#ifndef CLASSES_H_INCLUDED
#define CLASSES_H_INCLUDED
#include <iostream>
#include <string>
#include <limits>

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

class CD: public Produto{

private:
    int nf;
public:
    inline CD(const string& N="", unsigned P=0, int NF=0): Produto(N,P), nf(NF) {}
    bool ler (istream &L);
    void salvar(ostream &S) const;
    void digitar();
    void imprimir() const;
};

bool CD :: ler(istream &I){

  //   if(arq.is_open) verifica se o arquivo pode ser aberto
     Produto :: ler(I);
     I.ignore(numeric_limits <streamsize>::max(), '"');
     I >> nf;
}

void CD :: salvar(ostream &S)const{

     Produto :: salvar(S);
     S << nf;

}

void CD :: digitar(){

    Produto :: digitar();

    cout << "Digite o numero de faixas: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> nf;
}

void CD :: imprimir() const{

    Produto :: imprimir();
    cout << nf;

}

inline istream& operator>>(istream &I, CD &C) {C.digitar(); return I;}
inline ostream& operator<<(ostream &S, const CD &C) {C.salvar(S); return S;}

class DVD: public Produto{

private:
    int duracao;
public:
    inline DVD(const string& N="", unsigned P=0, int D=0): Produto(N,P), duracao(D) {}
    bool ler (istream &L);
    void salvar(ostream &S) const;
    void digitar();
    void imprimir() const;
};

bool DVD :: ler(istream &I){

  //   if(arq.is_open) verifica se o arquivo pode ser aberto
     Produto :: ler(I);
     I.ignore(numeric_limits <streamsize>::max(), '"');
     I >> duracao;
}

void DVD :: salvar(ostream &S)const{

     Produto :: salvar(S);
     S << '"' << duracao << '"';

}

void DVD :: digitar(){

    Produto :: digitar();

    cout << "Digite o numero de faixas: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> duracao;
}

void DVD :: imprimir() const{

    Produto :: imprimir();
    cout << duracao;

}

inline istream& operator>>(istream &I, DVD &C) {C.digitar(); return I;}
inline ostream& operator<<(ostream &S, const DVD &C) {C.salvar(S); return S;}

class DVD: public Produto{

private:
    int duracao;
public:
    inline DVD(const string& N="", unsigned P=0, int D=0): Produto(N,P), duracao(D) {}
    bool ler (istream &L);
    void salvar(ostream &S) const;
    void digitar();
    void imprimir() const;
};

bool DVD :: ler(istream &I){

  //   if(arq.is_open) verifica se o arquivo pode ser aberto
     Produto :: ler(I);
     I.ignore(numeric_limits <streamsize>::max(), '"');
     I >> duracao;
}

void DVD :: salvar(ostream &S)const{

     Produto :: salvar(S);
     S << '"' << duracao << '"';

}

void DVD :: digitar(){

    Produto :: digitar();

    cout << "Digite a duracao do DVD: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> duracao;
}

void DVD :: imprimir() const{

    Produto :: imprimir();
    cout << duracao;

}

inline istream& operator>>(istream &I, DVD &C) {C.digitar(); return I;}
inline ostream& operator<<(ostream &S, const DVD &C) {C.salvar(S); return S;}


class ListaLivro
{
private:
  Livro *x;
  unsigned N;
public:
  // Inclua os construtores, destrutor e operadores necessarios
  void incluir(const Livro &L);
  bool excluir(unsigned id);

  bool ler(istream &I);
  void salvar(ostream &O) const;
  void imprimir() const;
};

// =========================================
// Inclua aqui as classes ListaCD e ListaDVD
// =========================================

class Loja
{
private:
  ListaLivro LL;
  ListaCD LC;
  ListaDVD LD;
public:
  inline Loja(): LL(), LC(), LD() {}

  inline void incluirLivro(const Livro &X) {LL.incluir(X);}
  inline bool excluirLivro(unsigned id) {return LL.excluir(id);}
  inline void incluirDVD(const DVD &X) {LD.incluir(X);}
  inline bool excluirDVD(unsigned id) {return LD.excluir(id);}
  inline void incluirCD(const CD &X) {LC.incluir(X);}
  inline bool excluirCD(unsigned id) {return LC.excluir(id);}

  bool ler(const string& arq);
  bool salvar(const string& arq) const;
  void imprimir() const;
};




#endif // CLASSES_H_INCLUDED
