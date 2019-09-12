#ifndef CLASSES_H_INCLUDED
#define CLASSES_H_INCLUDED
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
    inline void imprimir() const
    {
        salvar(cout);
    }
    friend class Livro;
    friend class DVD;
    friend class CD;
};

class Livro: public Produto
{

private:
    string autor;

public:
    inline Livro(Produto &G, const string &M=""): Produto(), autor(M) {}
    inline Livro()
    {
        Produto(nome,preco);
        autor=autor;
    }
    bool ler (istream &L);
    void salvar(ostream &S) const;
    void digitar();
    void imprimir() const;
};


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

class ListaLivro: public Livro
{
private:
    Livro *x;
    unsigned N;
public:
    inline ListaLivro (): x(NULL), N(0) {}
    ListaLivro(const ListaLivro &LL);
    ~ListaLivro ();

    void incluir(const Livro &L);
    bool excluir(unsigned id);

    bool ler(istream &I);
    void salvar(ostream &O) const;
    void imprimir() const;
};

class ListaCD: public CD
{
private:
    CD *x;
    unsigned N;
public:
    inline ListaCD (): x(NULL), N(0) {}
    ListaCD(const ListaCD &LC);
    ~ListaCD ();

    void incluir(const CD &D);
    bool excluir(unsigned id);

    bool ler(istream &I);
    void salvar(ostream &O) const;
    void imprimir() const;
};

class ListaDVD: public DVD
{
private:
    DVD *x;
    unsigned N;
public:
    inline ListaDVD (): x(NULL), N(0) {}
    ListaDVD(const ListaDVD &LD);
    ~ListaDVD ();

    void incluir(const DVD &D);
    bool excluir(unsigned id);

    bool ler(istream &I);
    void salvar(ostream &O) const;
    void imprimir() const;
};

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

inline istream& operator>>(istream &I, Livro &L){L.digitar(); return I;}
inline ostream& operator<<(ostream &S, const Livro &L){L.salvar(S); return S;}
inline istream& operator>>(istream &I, Produto &P){P.digitar(); return I;}
inline ostream& operator<<(ostream &O, const Produto &P){P.salvar(O); return O;}
inline istream& operator>>(istream &I, DVD &D){D.digitar();return I;}
inline ostream& operator<<(ostream &S, const DVD &D){D.salvar(S); return S;}
inline istream& operator>>(istream &I, CD &C){C.digitar(); return I;}
inline ostream& operator<<(ostream &S, const CD &C){C.salvar(S); return S;}

/// ///////////////////////////////////CLASSE PRODUTO/////////////////////////////////// ///

bool Produto :: ler(istream &I)
{
    unsigned valor=0, sob=0;

    I.ignore(numeric_limits <streamsize>::max(), '"');
    getline(I, nome, '"');
    I.ignore(numeric_limits <streamsize>::max(), ';');
    I.ignore(numeric_limits <streamsize>::max(), '$');
    I >> valor;
    I.ignore(numeric_limits <streamsize>::max(), '.');
    I >> sob;
    preco = valor*100 + sob;
    if (nome != "" || preco != 0)
        return true;
    else
        return false;
}

void Produto :: salvar(ostream &O) const
{
    unsigned Prec, res;
    Prec = preco/100;
    res = preco%100;
    if (res < 10)
        O << '"' << nome << '"' << ';' << '$' << Prec << '.' << '0' << res << ';';
    else
        O << '"' << nome << '"' << ';' << '$' << Prec << '.' << res << ';';
}

void Produto :: digitar()
{
    int teste;
    cout << "Digite o nome do Produto: ";
    getline(cin,nome);
    do
    {
        cout << "Digite o Preco, em centavos, do Produto: ";
        cin >> teste;
    }
    while(teste < 0);
    preco = teste;
}


/// ///////////////////////////////////CLASSE PRODUTO/////////////////////////////////// ///
//////////////////////////////////////////////////////////~/////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
/// //////////////////////////////////CLASSE LIVRO///////////////////////////////////// ///

bool Livro :: ler(istream &I)
{
    //   if(arq.is_open) verifica se o arquivo pode ser aberto
    string teste(""), teste2("");
    getline(I, teste, ' ');
    getline(I,teste2, '"');
    I.ignore(numeric_limits <streamsize>::max(), '"');
    if (teste == "L:" && teste2 == "")
    {
        Produto :: ler(I);
        I.ignore(numeric_limits <streamsize>::max(), '"');
        getline(I, autor, '"');
        teste = "";
        teste2 = "";
        return true;
    }
    else
        return false;
}

void Livro :: salvar(ostream &S)const
{

    S << "L: ";
    Produto :: salvar(S);
    S << '"' << autor << '"';

}

void Livro :: digitar()
{

    Produto :: digitar();

    cout << "Digite o nome do autor: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, autor, '\n');
}

void Livro :: imprimir() const
{

    cout << "L: ";
    Produto :: imprimir();
    cout << '"' << autor << '"';

}

/// ///////////////////////////////////CLASSE LIVRO/////////////////////////////////// ///
////////////////////////////////////////////////////////~/////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/// //////////////////////////////////CLASSE CD///////////////////////////////////// ///

bool CD :: ler(istream &I)
{

    string teste(""), teste2("");
    getline(I, teste, ' ');
    getline(I,teste2, '"');
    I.ignore(numeric_limits <streamsize>::max(), '"');
    cout << teste << teste2 << endl;
    if (teste == "D:" && teste2 == "")
    {
        Produto :: ler(I);
        I.ignore(numeric_limits <streamsize>::max(), '"');
        I >> nf;
        teste = "";
        teste2 = "";
        return true;
    }
    else
        return false;
}


void CD :: salvar(ostream &S)const
{

    S << "C: ";
    Produto :: salvar(S);
    S << nf;

}

void CD :: digitar()
{

    Produto :: digitar();

    cout << "Digite o numero de faixas: ";
  //  cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> nf;
}

void CD :: imprimir() const
{

    cout << "C: ";
    Produto :: imprimir();
    cout << nf;

}

/// /////////////////////////////////////CLASSE CD///////////////////////////////////// ///
////////////////////////////////////////////////////////~/////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/// //////////////////////////////////CLASSE DVD///////////////////////////////////// ///

bool DVD :: ler(istream &I)
{
    string teste(""), teste2("");
    getline(I, teste, ' ');
    getline(I,teste2, '"');
    I.ignore(numeric_limits <streamsize>::max(), '"');
    cout << teste << teste2 << endl;
    if (teste == "D:" && teste2 == "")
    {
        Produto :: ler(I);
        I.ignore(numeric_limits <streamsize>::max(), '"');
        I >> duracao;
        teste = "";
        teste2 = "";
        return true;
    }
    else
        return false;
}

void DVD :: salvar(ostream &S)const
{

    S << "D: ";
    Produto :: salvar(S);
    S << '"' << duracao << '"';

}

void DVD :: digitar()
{

    Produto :: digitar();

    cout << "Digite a duracao do DVD: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> duracao;
}

void DVD :: imprimir() const
{

    cout << "D: ";
    Produto :: imprimir();
    cout << duracao;

}

/// /////////////////////////////////////CLASSE DVD///////////////////////////////////// ///
////////////////////////////////////////////////////////~///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
/// ///////////////////////////////CLASSE LISTALIVRO////////////////////////////////// ///

ListaLivro :: ListaLivro ( const ListaLivro &LL)
{

    if(LL.N != 0)
    {
        N = LL.N;
        for (unsigned i=0; i<N; i++)
        {
            x[i] = LL.x[i];
        }
    }
}

ListaLivro :: ~ListaLivro()
{

    if (x!=NULL)
        delete[] x;
    N = 0;
    x = NULL;
}

void ListaLivro :: incluir(const Livro &L)
{
    if(N==0)
    {
        x=new Livro[N+1];
        x[N]=L;
        N++;
    }
    else if(N!=0)
    {
        Livro *prov = new Livro[N+1];
        for (unsigned i=0; i<N; i++)
            prov[i] = x[i];
        prov[N] = L;
        N++;
        if (x != NULL)
            delete[] x;
        x = NULL;
        x = prov;
        prov = NULL;
    }
}


bool ListaLivro :: ler(istream &I)
{
    string pc("");
    getline(I, pc, ' ');
    I >> N;
    I >> ws;
    if (pc == "LISTALIVRO" && N != 0)
    {
        x = new Livro[N];
        for (unsigned i=0; i<N; i++)
        {
            if (i == 0)
            {
                Livro l;
                l.ler(I);
                x[i] = l;
                I.ignore(numeric_limits<streamsize>::max(),'/n');
                cout << x[i];
            }
        }
        return true;
    }
    else
        return false;
}

void ListaLivro :: salvar(ostream &O) const
{
    O << "LISTALIVRO " << N << endl;
    for (unsigned i=0; i<N; i++)
    {
        O<<x[i];
        O << endl;
    }
}

void ListaLivro :: imprimir()const
{
    cout << ">> LIVROS: " << endl;
    for(unsigned i=0; i<N; i++)
    {
        cout << i << ") ";
        cout << x[i];
        cout << endl;
    }
}

bool ListaLivro :: excluir(unsigned id)
{

    if(id <= N-1)
    {
        Livro *prov = new Livro[N-1];
        for(unsigned i=0; i<id; i++)
            prov[i] = x[i];
        if(id!=N-1)
        {
            for(unsigned j=id; j<N-1; j++)
                prov[j]=x[j+1];
        }
        delete[] x;
        x = NULL;
        x = prov;
        prov = NULL;
        N--;
        return true;
    }
    else
        return false;

}

/// ///////////////////////////////CLASSE LISTALIVRO////////////////////////////////// ///
//////////////////////////////////////////////////////~///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
/// ///////////////////////////////CLASSE LISTACD/////////////////////////////////// ///

ListaCD :: ListaCD ( const ListaCD &LC)
{

    if(LC.N != 0)
    {
        N = LC.N;
        for (unsigned i=0; i<N; i++)
        {
            x[i] = LC.x[i];
        }
    }
}

ListaCD :: ~ListaCD()

{
    if (x!=NULL)
        delete[] x;
    N = 0;
    x = NULL;
}

void ListaCD :: incluir(const CD &C)
{
    if(N==0)
    {
        x=new CD[N+1];
        x[N]=C;
        N++;
    }
    else if(N!=0)
    {
        CD *prov = new CD[N+1];
        for (unsigned i=0; i<N; i++)
            prov[i] = x[i];
        prov[N] = C;
        N++;
        if (x != NULL)
            delete[] x;
        x = NULL;
        x = prov;
        //   delete[] prov;
        prov = NULL;
    }
}


bool ListaCD :: ler(istream &I)
{
    string pc("");
    getline(I, pc, ' ');
    I >> N;
    I >> ws;
    if (pc == "LISTACD" && N != 0)
    {
        x = new CD[N];
        for (unsigned i=0; i<N; i++)
        {
            if (i == 0)
            {
                CD C;
                C.ler(I);
                x[i] = C;
                I.ignore(numeric_limits<streamsize>::max(),'/n');
                cout << x[i];
            }
        }
        return true;
    }
    else
        return false;
}

void ListaCD :: salvar(ostream &O) const
{
    O << "LISTACD " << N << endl;
    for (unsigned i=0; i<N; i++)
    {
        O<<x[i];
        O << endl;
    }
}

void ListaCD :: imprimir()const
{
    cout << ">> CDS: " << endl;
    for(unsigned i=0; i<N; i++)
    {
        cout << i << ") ";
        cout << x[i];
        cout << endl;
    }
}

bool ListaCD :: excluir(unsigned id)
{

    if(id <= N-1)
    {
        CD *prov = new CD[N-1];
        for(unsigned i=0; i<id; i++)
            prov[i] = x[i];
        if(id!=N-1)
        {
            for(unsigned j=id; j<N-1; j++)
                prov[j]=x[j+1];
        }
        delete[] x;
        x = NULL;
        x = prov;
        prov = NULL;
        N--;
        return true;
    }
    else
        return false;

}

/// ///////////////////////////////CLASSE LISTACD////////////////////////////////// ///
//////////////////////////////////////////////////////~///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
/// ///////////////////////////////CLASSE LISTADVD/////////////////////////////////// ///

ListaDVD :: ListaDVD ( const ListaDVD &LD)
{

    if(LD.N != 0)
    {
        N = LD.N;
        for (unsigned i=0; i<N; i++)
        {
            x[i] = LD.x[i];
        }
    }
}

ListaDVD :: ~ListaDVD()
{

    if (x!=NULL)
        delete[] x;
    N = 0;
    x = NULL;
}

void ListaDVD :: incluir(const DVD &D)
{
    if(N==0)
    {
        x=new DVD[N+1];
        x[N]=D;
        N++;
    }
    else if(N!=0)
    {
        DVD *prov = new DVD[N+1];
        for (unsigned i=0; i<N; i++)
            prov[i] = x[i];
        prov[N] = D;
        N++;
        if (x != NULL)
            delete[] x;
        x = NULL;
        x = prov;
        prov = NULL;
    }
}


bool ListaDVD :: ler(istream &I)
{
    string pc("");
    getline(I, pc, ' ');
    I >> N;
    I >> ws;
    if (pc == "LISTADVD" && N != 0)
    {
        x = new DVD[N];
        for (unsigned i=0; i<N; i++)
        {
            if (i == 0)
            {
                DVD D;
                D.ler(I);
                x[i] = D;
                I.ignore(numeric_limits<streamsize>::max(),'/n');
                cout << x[i];
            }
        }
        return true;
    }
    else
        return false;
}

void ListaDVD :: salvar(ostream &O) const
{
    O << "LISTADVD " << N << endl;
    for (unsigned i=0; i<N; i++)
    {
        O<<x[i];
        O << endl;
    }
}

void ListaDVD :: imprimir()const
{
    cout << ">> DVDS: " << endl;
    for(unsigned i=0; i<N; i++)
    {
        cout << i << ") ";
        cout << x[i];
        cout << endl;
    }
}

bool ListaDVD :: excluir(unsigned id)
{

    if(id <= N-1)
    {
        DVD *prov = new DVD[N-1];
        for(unsigned i=0; i<id; i++)
            prov[i] = x[i];
        if(id!=N-1)
        {
            for(unsigned j=id; j<N-1; j++)
                prov[j]=x[j+1];
        }
        delete[] x;
        x = NULL;
        x = prov;
        prov = NULL;
        N--;
        return true;
    }
    else
        return false;

}

/// ///////////////////////////////CLASSE LISTALIVRO////////////////////////////////// ///
//////////////////////////////////////////////////////~///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
/// /////////////////////////////////CLASSE LOJA///////////////////////////////////// ///

void Loja::imprimir() const
{
    LL.imprimir();
    LC.imprimir();
    LD.imprimir();
}

bool Loja::ler(const string& arq){
    ifstream entrada(arq.c_str());
    if(!entrada.is_open())
    {
        cerr << "Nao eh um arquivo existente" << endl;
        return false;
    }
    bool L, D, C;
    L = LL.ler(entrada);
    C = LC.ler(entrada);
    D = LD.ler(entrada);
    if( L == true && C == true && D == true)
        return true;
    else
    {
        cerr << "Nao foi possivel abrir o arquivo\n";
        return false;
    }
}

    bool Loja::salvar(const string& arq) const{
        ofstream saida(arq.c_str());
        if(!saida.is_open())
        {
            cerr << "Nao eh um arquivo existente" << endl;
            return false;
        }

        LL.salvar(saida);
        LC.salvar(saida);
        LD.salvar(saida);

        return true;
    }




#endif // CLASSES_H_INCLUDED
