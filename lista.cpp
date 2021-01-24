#include <iostream>

using namespace std;

struct noh{
    int x;
    noh *proximo, *anterior;
    inline noh();
};

noh::noh(){
    cin >> x; cin.ignore();
    proximo = NULL;
    anterior = NULL;
}

class Lista{
private:
    noh *primeiro, *ultimo;
public:
    inline Lista();
    inline ~Lista();
    inline void insere_vazio();
    inline void insere_fim();
    inline void insere_inicio();
    inline void insere_lugar();
    inline void percorre_lista();
    inline void remove_primeiro();
    inline void remove_posicao();
    inline void remove_ultimo();
};

Lista::Lista(){
    primeiro = NULL, ultimo = NULL;
}

Lista::~Lista(){
    while(primeiro!=NULL){
        remove_primeiro();
    }
}

void Lista::insere_vazio(){
    noh* novo_noh = new noh();
    primeiro = novo_noh;
    ultimo = novo_noh;
}

void Lista::insere_inicio(){
    if(primeiro==NULL){
        insere_vazio();
    }else{
        noh* novo_noh = new noh();
        novo_noh->proximo = primeiro;
        primeiro->anterior = novo_noh;
        primeiro = novo_noh;
    }
}

void Lista::insere_fim(){
    if(primeiro==NULL){
        insere_vazio();
    }else{
        noh* novo_noh = new noh();
        novo_noh->anterior = ultimo;
        ultimo->proximo = novo_noh;
        ultimo = novo_noh;
    }
}

void Lista::insere_lugar(){
    cout << "Qual posição? ";
    int pos, i = 0; cin >> pos; cin.ignore();
    noh* aux = primeiro;
    while(i<=pos){
        if(aux == NULL){
            cout << "Error" << endl;
            break;
        }if(i==pos and aux!=primeiro){
            noh* novo_noh = new noh();
            novo_noh->proximo = aux;
            novo_noh->anterior = aux->anterior;
            aux->anterior->proximo = novo_noh;
            aux->anterior = novo_noh;
        }else if(i==pos and aux==primeiro){
            insere_inicio();
        }
        aux = aux->proximo;
        i++;
    }
}

void Lista::percorre_lista(){
    noh* aux = primeiro;
    while(aux!=NULL){
        cout << aux->x << " ";
        aux = aux->proximo;
    }
    cout << endl;
}

void Lista::remove_primeiro(){
    noh* aux = primeiro;
    if(aux!=NULL and primeiro!=ultimo){
        primeiro = primeiro->proximo;
        delete[]primeiro->anterior;
        primeiro->anterior = NULL;
        cout << "primeiro apagado ";
    }else if(primeiro==ultimo){
        delete[]primeiro;
        primeiro = NULL;
        ultimo = NULL;
        cout << "primeiro apagado ";
    }
    cout << endl;
}

void Lista::remove_ultimo(){
    noh* aux = ultimo;
    if(aux!=NULL and ultimo!=primeiro){
        ultimo = ultimo->anterior;
        delete[]ultimo->proximo;
        ultimo->proximo = NULL;
        cout << "ultimo apagado ";
    }else if(ultimo==primeiro){
        delete[]primeiro;
        primeiro = NULL;
        ultimo = NULL;
        cout << "ultimo apagado ";
    }
    cout << endl;
}

void Lista::remove_posicao(){
    cout << "Qual posição? ";
    int pos, i = 0; cin >> pos; cin.ignore();
    noh* aux = primeiro;
    while(i<=pos){
        if(aux == NULL){
            cout << "Error" << endl;
            break;
        }if(i==pos and aux!=primeiro and aux!=ultimo){
            aux->proximo->anterior = aux->anterior;
            aux->anterior->proximo = aux->proximo;
            delete[]aux;
        }else if(i==pos and aux==primeiro){
            remove_primeiro();
        }else if(i==pos and aux == ultimo){
            remove_ultimo();
        }
        aux = aux->proximo;
        i++;
    }
}

int main(){
    bool fechado = false;
    Lista minhaLista;
    while(!fechado){
        cout << "1 - inserir no inicio  2 - inserir no fim  3 - inserir em posição  4 - percorrer lista" << endl;
        cout << "5 - remove o primeiro  6 - remove último  7 - remove posição  8 - fechar" << endl;
        int acao; cin >> acao; cin.ignore(); 
        switch(acao){
        case 1:
            minhaLista.insere_inicio();
            break;
        case 2:
            minhaLista.insere_fim();
            break;
        case 3:
            minhaLista.insere_lugar();
            break;
        case 4:
            minhaLista.percorre_lista();
            break;
        case 5:
            minhaLista.remove_primeiro();
            break;
        case 6:
            minhaLista.remove_ultimo();
            break;
        case 7:
            minhaLista.remove_posicao();
            break;    
        case 8: 
            minhaLista.~Lista();
            fechado = true;
            break;
        }
    }
    
}