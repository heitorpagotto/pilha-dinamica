#include <malloc.h>
#include <iostream>

//#region STRUCTS
typedef struct {
    int placa;
    char modelo[20];
    char cor[20];
} REGISTRO;

typedef struct aux {
    REGISTRO reg;
    struct aux *prox;
} ELEMENTO;

typedef ELEMENTO *PONT;

typedef struct {
    PONT topo;
} PILHA;
//#endregion STRUCTS

//#region LibFunctions
void clearscr()
{
#ifdef __unix__
    system("clear");
#elif defined(_WIN32) || defined(WIN32)
    system("cls");
#endif
}

void pausa()
{
    printf("\nTecle enter para continuar ");
    getchar();
    getchar();
}
//#endregion LibFunctions

int programRunning = 1;

using namespace std;


void inicializarPilha(PILHA *p) {
    p->topo = nullptr;
}

int tamanhoPilha(PILHA *p) {
    PONT ender = p->topo;
    int tam = 0;
    while (ender != nullptr)
    {
        tam++;
        ender = ender->prox;
    }
    return tam;
}

bool pilhaVazia(PILHA *p) {
    if (p->topo == nullptr)
        return true;
    return false;
}

void listarPilha(PILHA *p) {
    PONT ender = p->topo;
    cout << "Estacionamento [" << endl;
    while (ender != nullptr)
    {
        cout <<"{ Placa: " <<ender->reg.placa << ", Modelo: " << ender->reg.modelo << ", Cor: " << ender->reg.cor << "}" << endl;
        ender = ender->prox;
    }
    cout << "]" << endl;
}

bool pushPilha(PILHA *p, REGISTRO reg) {
    PONT novo = (PONT)malloc(sizeof(ELEMENTO));
    novo->reg = reg;
    novo->prox = p->topo;
    p->topo = novo;
    return true;
}

bool popPilha(PILHA *p, REGISTRO *reg) {
    if (p->topo == nullptr)
        return false;

    *reg = p->topo->reg;
    PONT apagar = p->topo;
    p->topo = p->topo->prox;
    free(apagar);
    return true;
}

void reinicializarPilha(PILHA *p) {
    PONT apagar;
    PONT posicao = p->topo;
    while(posicao != nullptr) {
        apagar = posicao;
        posicao = posicao->prox;
        free(apagar);
    }
    p->topo = nullptr;
}

void insertInPile(PILHA *p, REGISTRO reg) {
    cout << "Informe uma placa: ";
    cin >> reg.placa;
    cin.ignore(256, '\n');
    cout << "Informe uma cor: ";
    cin.getline(reg.cor, sizeof(reg.cor));
    cout << "Informe um modelo: ";
    cin.getline(reg.modelo, sizeof(reg.modelo));

    pushPilha(p, reg);
    cout << endl << "Inserido com sucesso!" << endl;
}

void removeFromPile(PILHA *p, REGISTRO *reg) {
    if (popPilha(p, reg)) {
        cout << "Elemento removido com sucesso. Placa: " << reg->placa << endl;
    } else {
        cout << "Nao foi possivel excluir elemento da pilha." << endl;
    }
}

int printMenu(PILHA *p, REGISTRO r) {
    cout << endl;
    cout << "Pilha dinamica - Estacionamento" << endl;
    cout << "1- Listar Pilha" << endl;
    cout << "2- Inserir na Pilha" << endl;
    cout << "3- Remover da Pilha" << endl;
    cout << "4- Tamanho da Pilha" << endl;
    cout << "5- Reinicializar Pilha" << endl;
    cout << "6- Pilha esta vazia?" << endl;
    cout << "7- Sair" << endl;
    cout << endl;
    cout << "Insira a opcao desejada: ";
    int opt;
    cin >> opt;

    switch (opt) {
        case 1:
            clearscr();
            listarPilha(p);
            pausa();
            clearscr();
            break;
        case 2:
            clearscr();
            insertInPile(p, r);
            clearscr();
            break;
        case 3:
            clearscr();
            removeFromPile(p, &r);
            pausa();
            clearscr();
            break;
        case 4:
            clearscr();
            cout << "O tamanho atual da pilha e de: " << tamanhoPilha(p) << endl;
            pausa();
            clearscr();
            break;
        case 5:
            clearscr();
            reinicializarPilha(p);
            cout << "Pilha reinicializada com sucesso!" << endl;
            pausa();
            clearscr();
            break;
        case 6:
            clearscr();
            pilhaVazia(p) ? cout << "A pilha esta vazia" <<endl : cout << "A pilha nao esta vazia" << endl;
            pausa();
            clearscr();
            break;
        case 7:
            clearscr();
            cout << "Encerrando aplicacao..." << endl;
            return 0;
        default:
            clearscr();
            cout << "Opcao invalida" << endl;
            pausa();
            clearscr();
    }

    return 1;
}



int main() {
    PILHA p;
    REGISTRO r;
    inicializarPilha(&p);
    while (programRunning == 1) {
        programRunning = printMenu(&p, r);
    }

    return 0;
}
