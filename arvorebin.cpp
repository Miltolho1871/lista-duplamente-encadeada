#include <iostream>
using namespace std;

struct noh{
    int valor;
    noh* esq; 
    noh* dir;
    noh* pai;
    noh();
};

noh::noh(){
    esq=NULL;
    dir=NULL;
    pai=NULL;
    cout<<"Insira um valor: ";
    cin>>valor;
}

class Arvore{
private:
    noh* raiz;
public:
    Arvore();
    ~Arvore();
    void destrutorAux(noh* aux);

    void insere();
    void remove(int valor);
    void substitui(noh* remov, noh* subst);

    void percorre();
    void percorreAux(noh* aux);

    void buscaAux(int valor);
    noh* busca(noh* aux, int valor);
    noh* busca(noh* aux, int valor, int& i);

    void max();
    void min();
    noh* maximo(noh* aux);
    noh* minimo(noh* aux);
};

//CONSTRUTOR E DESTRUTOR=======================================

Arvore::Arvore(){
    raiz = NULL;
}

Arvore::~Arvore(){
    destrutorAux(raiz);
}

void Arvore::destrutorAux(noh* aux){
    if(aux!=NULL){
        destrutorAux(aux->esq);
        destrutorAux(aux->dir);
        if(aux==raiz) raiz = NULL;
        else{
            if(aux==aux->pai->dir) aux->pai->dir = NULL;
            else aux->pai->esq = NULL;
        }
        delete[] aux;
    }
}

//INSERÇÃO E REMOÇÃO===========================================

void Arvore::insere(){
    noh* novo_noh = new noh();
    if(raiz == NULL) raiz = novo_noh;
    else{
        noh* aux = raiz;
        while(aux != NULL){
            novo_noh->pai = aux;
            if(novo_noh->valor<aux->valor) aux = aux->esq;
            else aux = aux->dir;
        }
        if(novo_noh->pai->valor>novo_noh->valor) novo_noh->pai->esq = novo_noh;
        else novo_noh->pai->dir = novo_noh;
    }
}

void Arvore::remove(int valor){
    noh* aux_remove = busca(raiz, valor);
    if(aux_remove==NULL) cout << "Remoção inválida" << endl;
    else{
        if(aux_remove->dir==NULL) substitui(aux_remove, aux_remove->esq);
        else if(aux_remove->esq==NULL) substitui(aux_remove, aux_remove->dir);
        else{
            noh* sucessor = minimo(aux_remove->dir);
            if(sucessor->pai!=aux_remove){
                substitui(sucessor, sucessor->dir);
                sucessor->dir = aux_remove->dir;
                sucessor->dir->pai = sucessor;
            }
            substitui(aux_remove, sucessor);
            sucessor->esq = aux_remove->esq;
            sucessor->esq->pai = sucessor;
        }
        delete[] aux_remove;
    }
}

void Arvore::substitui(noh* remov, noh* subst){
    if(remov==raiz) raiz=subst;
    else if(remov==remov->pai->esq) remov->pai->esq = subst;
    else remov->pai->dir = subst;
    if(subst!=NULL) subst->pai=remov->pai;
}

//PERCORRIMENTO================================================

void Arvore::percorre(){
    percorreAux(raiz);
    cout << endl;
}

void Arvore::percorreAux(noh* aux){
    if(aux!=NULL){
        percorreAux(aux->esq);
        cout << aux->valor << " ";
        percorreAux(aux->dir);
    }
}

//BUSCA========================================================

void Arvore::buscaAux(int valor){
    int i = 0;
    noh* aux = busca(raiz, valor, i);
    if(aux==NULL) cout << "Valor inexistente" << endl;
    else cout << "O valor é " << aux->valor << " e está a " << i << " níveis de profundidade" << endl; 
}

noh* Arvore::busca(noh* aux, int valor, int& i){
    if(aux==NULL) return NULL;
    else{
        if(aux->valor==valor) return aux;
        else{
            if(valor<aux->valor){
                if(aux->esq==NULL) return NULL;
                else {
                    i++;
                    return busca(aux->esq, valor, i);
                }
            }else{
                if(aux->dir==NULL) return NULL;
                else {
                    i++;
                    return busca(aux->dir, valor, i);
                }
            }
        }
    }
}

noh* Arvore::busca(noh* aux, int valor){
    if(aux==NULL) return NULL;
    else{
        if(aux->valor==valor) return aux;
        else{
            if(valor<aux->valor){
                if(aux->esq==NULL) return NULL;
                else return busca(aux->esq, valor);
            }else{
                if(aux->dir==NULL) return NULL;
                else return busca(aux->dir, valor);
            }
        }
    }
}

//MÁXIMO E MÍNIMO DA ÁRVORE====================================

void Arvore::max(){
    noh* aux = maximo(raiz);
    if(aux==NULL) cout << "Valor inexistente" << endl;
    else cout << aux->valor << endl;
}


void Arvore::min(){
    noh* aux = minimo(raiz);
    if(aux==NULL) cout << "Valor inexistente" << endl;
    else cout << aux->valor << endl;
}

noh* Arvore::maximo(noh* aux){
    if(aux==NULL) return NULL;
    else{
        if(aux->dir==NULL) return aux;
        else return minimo(aux->dir);
    }
}

noh* Arvore::minimo(noh* aux){
    if(aux==NULL) return NULL;
    else{
        if(aux->esq==NULL) return aux;
        else return minimo(aux->esq);
    }
}

//============================================================

int main(){
    bool fechado=false;
    Arvore arvore;
    int acao;
    while(!fechado){
        cin>>acao; cin.ignore();
        switch(acao){
        case 0:
            arvore.~Arvore();
            fechado=true;
            break;
        case 1:
            int valor_busca; cout<<"Valor de busca: ";cin>>valor_busca;
            arvore.buscaAux(valor_busca);
            break;
        case 2:
            arvore.insere();
            break;
        case 3:
            int valor_remove; cout<<"Valor de remoção: ";cin >> valor_remove;
            arvore.remove(valor_remove);
            break;
        case 4:
            arvore.max();
            break;
        case 5:
            arvore.min();
            break;
        case 6:
            arvore.percorre();
            break;
        case 7:
            arvore.~Arvore();
            break;
        }
    }
}