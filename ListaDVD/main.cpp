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
    friend class DVD;
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
 //   cin.ignore(numeric_limits <streamsize>::max(), '\n');
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
class DVD: public Produto
{

private:
    int duracao;

public:
    inline DVD(Produto &G, const string &M=""): Produto(), duracao(0) {}
    inline DVD(){Produto(nome,preco); duracao=duracao;}
    bool ler (istream &L);
    void salvar(ostream &S) const;
    void digitar();
    void imprimir() const;
};

bool DVD :: ler(istream &I){
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
    else return false;
}


void DVD :: salvar(ostream &S)const
{

    S << "D: ";
    Produto :: salvar(S);
    S << duracao;

}

void DVD :: digitar(){

    Produto :: digitar();
    cout << "Digite a duracao do DVD: ";
    cin >> duracao;
}

void DVD :: imprimir() const{

    cout << "D: ";
    Produto :: imprimir();
    cout << duracao;

}


inline istream& operator>>(istream &I, DVD &C) {C.digitar(); return I;}
inline ostream& operator<<(ostream &S, const DVD &C) {C.salvar(S); return S;}

/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class ListaDVD: public DVD
{
private:
    DVD *x;
    unsigned N;
public:
    // Inclua os construtores, destrutor e operadores necessarios
    inline ListaDVD (): x(NULL), N(0) {}
    ListaDVD(const ListaDVD &LD);
    ~ListaDVD ();

    void incluir(const DVD &D);
    bool excluir(unsigned id);

    bool ler(istream &I);
    void salvar(ostream &O) const;
    void imprimir() const;
};

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
        if (x != NULL) delete[] x;
        x = NULL;
        x = prov;
        //   delete[] prov;
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
        for (unsigned i=0; i<N; i++){
            if (i == 0){
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
    ListaDVD P, h;
    DVD L,l;
    L.digitar();
    l.digitar();
    l.imprimir();
    cout << endl;
    L.imprimir();
    cout << endl;

    P.incluir(l);
    P.incluir(L);
    P.incluir(l);
    P.incluir(L);
    P.imprimir();
    cout << endl;
    P.excluir(0);
    P.imprimir();
    P.salvar(arq);
   // h.ler(arq2);
    //h.imprimir();

    return 0;
}
