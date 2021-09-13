# include <iostream>

using namespace std;
int const INIT_LIST_INDEX = 1;

//Structs principais
struct data{
    string nome;
    int matricula;
};
struct headerInfo{
    int serie;
    string nome;
};

struct node{
    data info;
    node* next;
    node* previous;
};
struct headerList{
    node* first;
    node* last;
    headerList* next;
    headerList* previous;
    int tamanho;
    headerInfo properties;
};

//Procedimentos

headerList* init(){
    return NULL;
}

void insertListFirst(headerList*& list, headerInfo value){

    if(list == NULL){
        list = new headerList;
        list->first = NULL;
        list->last = NULL;
        list->next = NULL;
        list->previous = NULL;
        list->tamanho = 0;
        list->properties = value;
    }else{
        headerList* aux = new headerList;
        aux->first = NULL;
        aux->last = NULL;
        aux->next = list;
        aux->previous = NULL;
        aux->properties = value;
        aux->tamanho = 0;
        list = aux;
    }
}

void insertListLast(headerList*& list, headerInfo value){

    if(list == NULL){
        insertListFirst(list, value);
    }else{
        headerList* aux = list;

        while(aux->next != NULL){
            aux = aux->next;
        }
        aux->next = new headerList;
        aux->next->first = NULL;
        aux->next->last = NULL;
        aux->next->next = NULL;
        aux->next->previous = aux;
        aux->next->tamanho = 0;
        aux->next->properties = value;
    }
}

int listCount(headerList* list){
    headerList* aux = list;
    int i{};

    while(aux != NULL){
        i++;
        aux = aux->next;
    }

    return i;
}

void insertListOrdemAlfabetica(headerList*& l, headerInfo value){
    if(l != NULL){
        headerList* aux = l;

        while(aux != NULL && (to_string(value.serie) + value.nome).compare(to_string(aux->properties.serie) + aux->properties.nome) > 0){
            aux = aux->next;
        }

        if(aux == NULL){
            insertListLast(l, value);
        }else{
            if(aux->previous == NULL){
                insertListFirst(l, value);
            }else{
                headerList* newL = new headerList;
                newL->first = NULL;
                newL->last = NULL;
                newL->properties = value;
                newL->tamanho = 0;

                newL->next = aux;
                newL->previous = aux->previous;
                aux->previous->next = newL;
                aux->previous = newL;
            }
        }

    }else{
        insertListFirst(l, value);
    }
}

int listLenght(headerList* l){
    if(l != NULL) return l->tamanho;
    return 0;
}

//Mude a chave de pesquisa da lista se necessário no método getList
headerList* getList(headerList* list, string name, int serie){
    headerList* aux = list;

    while(aux != NULL){
        if(aux->properties.nome.compare(name) == 0 && aux->properties.serie == serie) break;
        aux = aux->next;
    }
    return aux;
}

bool insertFirst(headerList* l, data value){

    if(l == NULL) return false;

    if(l->first == NULL){
        l->first = new node;

        l->first->info = value;
        l->first->next = NULL;
        l->first->previous = NULL;

        l->last = l->first;
        l->tamanho = INIT_LIST_INDEX;
    }else{
        node* aux = new node;

        l->first->previous = aux;
        aux->next = l->first;
        aux->previous = NULL;
        aux->info = value;
        l->first = aux;
        l->tamanho++;
    }
    return true;
}

bool insertLast(headerList* l, data value){

    if(l == NULL) return false;

    if(l->first == NULL){
        l->first = new node;

        l->first->info = value;
        l->first->next = NULL;
        l->first->previous = NULL;

        l->last = l->first;
        l->tamanho = INIT_LIST_INDEX;
    }else{
        node* aux = new node;

        l->last->next = aux;
        aux->previous = l->last;
        aux->next = NULL;
        aux->info = value;
        l->last = aux;
        l->tamanho++;
    }
    return true;
}

bool insertOrdemAlfabetica(headerList* l, data value){

    if(l != NULL){
        node* aux = l->first;

        if(aux == NULL){
            insertFirst(l, value);
        }else{
            while(aux != NULL && value.nome.compare(aux->info.nome) > 0){
                aux = aux->next;
            }
            if(aux == NULL){
                insertLast(l, value);
            }else{

                if(aux->previous == NULL){
                    insertFirst(l, value);
                }else{

                    node* newNode = new node;
                    newNode->info = value;

                    newNode->next = aux;
                    aux->previous->next = newNode;
                    l->first = newNode;
                    newNode->previous = aux->previous;
                    aux->previous = newNode;
                }
            }

        }
        return true;
    }
    return false;
}

bool insertInPosition(headerList* list, data value, int position){

    if(list != NULL){
        if(position >= INIT_LIST_INDEX && position <= list->tamanho){

            if(position == INIT_LIST_INDEX){
                insertFirst(list, value);
                list->tamanho++;
            }else if(position == list->tamanho){
                insertLast(list, value);
                list->tamanho++;
            }else{
                node* auxL = list->first;
                node* aux = new node;
                int index = INIT_LIST_INDEX;
                aux->info = value;

                while(auxL != NULL && index < position){
                    auxL = auxL->next;
                    index++;
                }

                aux->previous = auxL->previous;
                aux->next = auxL->next;
                auxL->previous->next = aux;
                auxL->previous = aux;
                list->tamanho++;
            }
            return true;
        }
        return false;
    }
    return false;
}

headerList* listMinLenght(headerList* l, int serie){
    headerList* min = NULL;

    while(l != NULL){

        if(min == NULL && l->properties.serie == serie){
            min = l;
        }else{
            if(l->properties.serie == serie && (l->tamanho < min->tamanho)) min = l;
        }
        l = l->next;
    }

    return min;
}

//Altere abaixo as chaves do método getElement() e removeElement() caso a struct data seja alterada
node* getElement(headerList* list, string nome){
    node* aux = list->first;

    while(aux != NULL){
        if(aux->info.nome.compare(nome) == 0) break;
        aux = aux->next;
    }
    return aux;
}

bool removeElement(headerList* list, string nome){
    node* elm = getElement(list, nome);

    if(elm != NULL){
        if(elm->previous == NULL && elm->next == NULL){
            list->first = NULL;
            list->last = NULL;
            delete elm;
        }else if(elm->previous == NULL){
            list->first = elm->next;
            elm->next->previous = NULL;
            delete elm;
        }else if(elm->next == NULL){
            list->last = elm->previous;
            elm->previous->next = NULL;
            delete elm;
        }else{
            elm->previous->next = elm->next;
            elm->next->previous = elm->previous;
            delete elm;
        }
        return true;
    }
    return false;
}

/*Assim como os métodos get, altere tambem os métodos prints caso seja
adicionado mais dados na struct data ou headerInfo*/
void printList(headerList* list, bool header){

    if(list != NULL){
        node* aux = list->first;
        int i = 1;

        if(aux != NULL){
            if(header){
                cout << endl << list->properties.serie << "º Série | Turma: " << list->properties.nome << endl;
            }
            while(aux != NULL){
                cout << endl;
                cout << i << ". " << aux->info.nome << "(Mat. " << aux->info.matricula << ")";
                aux = aux->next;
                i++;

            }

        }else{
            if(header){
                cout << endl << list->properties.serie << "º Série | Turma: " << list->properties.nome << endl;
            }
            cout << endl << "Sem Alunos.";
        }
        cout << endl;
    }
}

void printListsInfo(headerList* list, bool printAlunos, bool separadores){

    while(list != NULL){
        cout << endl;
        if(separadores) cout << endl << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
        cout << list->properties.serie << "º Série | Turma: " << list->properties.nome;
        cout << endl << "Quantidade de Alunos: " << list->tamanho << endl;
        if(printAlunos) printList(list, false);
        if(separadores) cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-";
        list = list->next;
    }
    cout << endl;
}

void clearListsMemory(headerList*& l){
    while(l != NULL){
        node* aux = l->first;
        while(aux != NULL){
            if(aux->next != NULL){
                aux = aux->next;
                delete aux->previous;
            }else{
                delete aux;
                aux = NULL;
            }
        }
        l = l->next;
    }
}

// Functions Auxiliares ---------------------------------------------------------------
void pressKey2Cont(){
    cout << endl << "Pressione qualquer tecla para continuar..." << endl;
    cin.ignore();
    cin.get();
}
void limpar_tela(){
    system("cls||clear");
}

//Functions do Main --------------------------------------------------------------------
int menuHeader(){
    int opt{};
    limpar_tela();
    cout << "MENU PRINCIPAL:" << endl << endl;
    cout << "[1] Criar nova turma;" << endl;
    cout << "[2] Listar turmas;" << endl;
    cout << "[3] Inserir aluno em turma determinada;" << endl;
    cout << "[4] Inserir aluno na turma mais vaga;" << endl;
    cout << "[5] Listar alunos de turma determinada;" << endl;
    cout << "[6] Relatório completo;" << endl;
    cout << "[0] Sair." << endl;
    cout << endl << "Digite a Opção desejada: ";
    cin >> opt;
    limpar_tela();
    return opt;
}
headerInfo preenche_dados_sala(){
    headerInfo aux{};
    cout << "Série: ";
    cin >> aux.serie;
    cout << "Turma: ";
    cin.ignore();
    getline(cin, aux.nome);
    return aux;
}
data preenche_dados_aluno(){
    data aux{};
    cout << "Mátricula: ";
    cin >> aux.matricula;
    cout << "Nome: ";
    cin.ignore();
    getline(cin, aux.nome);
    return aux;
}
void opt1(headerList*& l){
    limpar_tela();
    cout << "-=-=-=-= CRIAR NOVA TURMA -=-=-=-=" << endl << endl;
    cout << "Preencha os dados abaixo para criar uma nova turma:" << endl << endl;
    insertListOrdemAlfabetica(l, preenche_dados_sala());
    
    limpar_tela();
    cout << "-=-=-=-= CRIAR NOVA TURMA -=-=-=-=" << endl << endl;
    cout << "A turma foi cadastrada!" << endl;
    pressKey2Cont();
}
void opt2(headerList*& l){
    limpar_tela();
    cout << "-=-=-=-= LISTAR TURMAS -=-=-=-=" << endl << endl;
    printListsInfo(l, false, false);
    pressKey2Cont();
}
void opt3(headerList*& l){
    limpar_tela();
    cout << "-=-=-=-= INSERIR ALUNO -=-=-=-=" << endl << endl;
    cout << "Preencha os dados abaixo para cadastrar o aluno:" << endl << endl;
    data aluno = preenche_dados_aluno();

    limpar_tela();
    cout << "-=-=-=-= INSERIR ALUNO -=-=-=-=" << endl << endl;
    cout << "Preencha os dados abaixo para buscar uma turma:" << endl << endl;
    headerInfo sala = preenche_dados_sala();
    headerList* busca = getList(l, sala.nome,sala.serie);

    limpar_tela();
    cout << "-=-=-=-= INSERIR ALUNO -=-=-=-=" << endl << endl;
    if(busca != NULL){
        if(insertOrdemAlfabetica(busca, aluno)){
            cout << "O aluno foi inserido na turma informada!" << endl;
        }else{
            cout << "Ocorreu um erro!" << endl;
        }
        cout << endl;
        pressKey2Cont();
    }else{
        cout << "Turma não encontrada!" << endl;
        pressKey2Cont();
    }    
}
void opt4(headerList*& l){
    limpar_tela();
    cout << "-=-=-=-= INSERIR ALUNO -=-=-=-=" << endl << endl;
    cout << "Preencha os dados abaixo para cadastrar o aluno:" << endl << endl;
    data aluno = preenche_dados_aluno();
    int serie{};
    cout << "Serie: ";
    cin >> serie;  
    headerList* busca = listMinLenght(l, serie);

    limpar_tela();
    cout << "-=-=-=-= INSERIR ALUNO -=-=-=-=" << endl << endl;
    if(busca != NULL){
        if(insertOrdemAlfabetica(busca, aluno)){
            cout << "O aluno foi inserido na turma " << busca->properties.serie << "(" << busca->properties.nome << ")!" << endl;
        }else{
            cout << "Ocorreu um erro!" << endl;
        }
        cout << endl;
        pressKey2Cont();
    }else{
        cout << "Não existe nenhuma turma compativel" << endl;
        pressKey2Cont();
    }    
}
void opt5(headerList*& l){
    limpar_tela();
    cout << "-=-=-=-= LISTAR ALUNOS -=-=-=-=" << endl << endl;
    cout << "Preencha os dados abaixo para buscar uma turma:" << endl << endl;
    headerInfo aux = preenche_dados_sala();
    headerList* busca = getList(l, aux.nome, aux.serie);

    limpar_tela();
    cout << "-=-=-=-= LISTAR ALUNOS -=-=-=-=" << endl << endl;
    if(busca != NULL){
        printList(busca, true);
        cout << endl;
        pressKey2Cont();
    }else{
        cout << "Turma não encontrada!" << endl;
        pressKey2Cont();
    }

}
void opt6(headerList*& l){
    limpar_tela();
    cout << "-=-=-=-= RELATÓRIO COMPLETO -=-=-=-=" << endl << endl;
    printListsInfo(l, true, false);
    pressKey2Cont();
}


int main (){
    headerList* l = init();
    bool continuar = true;
    
    while(continuar){
        switch(menuHeader()){
            case 0:
                continuar = false;
                break;
            case 1:
                opt1(l);
                break;
            case 2:
                opt2(l);
                break;
            case 3:
                opt3(l);
                break;
            case 4:
                opt4(l);
                break;
            case 5:
                opt5(l);
                break;
            case 6:
                opt6(l);
                break;
            default:
                break;
        }
    }

    clearListsMemory(l);
    cout << endl << "Programa feito por Harllem Nascimento" << endl << "-- Fim do programa." << endl;
    return 0;
}
