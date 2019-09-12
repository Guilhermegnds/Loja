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
};

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
    if (nome != "" || preco != 0) return true;
    else return false;
}

void Produto :: salvar(ostream &O) const
{
    unsigned Prec, res;
    Prec = preco/100;
    res = preco%100;
    if (res < 10) O << '"' << nome << '"' << ';' << '$' << Prec << '.' << '0' << res << ';';
    else O << '"' << nome << '"' << ';' << '$' << Prec << '.' << res << ';';
}

void Produto :: digitar()
{
    int teste;
    cout << "Digite o nome do Produto: ";
    getline(cin,nome);
    do
    {
        cout << "Digite o Preco do Produto: ";
        cin >> teste;
    }
    while(teste < 0);
    preco = teste;
}



inline istream& operator>>(istream &I, Produto &P)
{
    P.digitar();
    return I;
}
inline ostream& operator<<(ostream &O, const Produto &P)
{
    P.salvar(O);
    return O;
}
///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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

bool Livro :: ler(istream &I)
{
    //   if(arq.is_open) verifica se o arquivo pode ser aberto
    string teste(""), teste2("");
    getline(I, teste, ' ');
    getline(I,teste2, '"');
    I.ignore(numeric_limits <streamsize>::max(), '"');
    cout << teste << teste2 << endl;
    if (teste == "L:" && teste2 == "")
    {
        Produto :: ler(I);
        I.ignore(numeric_limits <streamsize>::max(), '"');
        getline(I, autor, '"');
        teste = "";
        teste2 = "";
        return true;
    }
    else return false;
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


inline istream& operator>>(istream &I, Livro &L)
{
    L.digitar();
    return I;
}
inline ostream& operator<<(ostream &S, const Livro &L)
{
    L.salvar(S);
    return S;
}

/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class ListaLivro: public Livro
{
private:
    Livro *x;
    unsigned N;
public:
    // Inclua os construtores, destrutor e operadores necessarios
    inline ListaLivro (): x(NULL), N(0) {}
    ListaLivro(const ListaLivro &LL);
    ~ListaLivro ();

    void incluir(const Livro &L);
    bool excluir(unsigned id);

    bool ler(istream &I);
    void salvar(ostream &O) const;
    void imprimir() const;
};

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
        //   delete[] prov;
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
        for (unsigned i=0; i<N; i++){
            if (i == 0){
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
        //    delete[] prov;
        prov = NULL;
        N--;
        return true;
    }
    else
        return false;

}

int main()
{
    ofstream arq("saida.txt");
 //   ifstream arq2("saida.txt");
    //if(arq.is_open()){cerr<<"deu errado troxa";}
    ListaLivro P, h;
    Livro L,l;
    L.digitar();
    l.digitar();
    l.imprimir();
    cout << endl;
    L.imprimir();
    cout << endl;
    // P.ler(arq2);
    P.incluir(l);
    P.incluir(L);
    P.incluir(l);
    P.incluir(L);
    P.imprimir();
    cout << endl;
    P.excluir(0);
    P.imprimir();
    P.salvar(arq);
 //   h.ler(arq2);
   // h.imprimir();

    return 0;
}

