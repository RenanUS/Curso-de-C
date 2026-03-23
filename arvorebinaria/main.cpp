#include <iostream>
using namespace std;

struct Node {
    int valor;
    int altura;
    Node* esquerda;
    Node* direita;

    Node(int v) {
        valor = v;
        altura = 1;
        esquerda = direita = nullptr;
    }
};

// Função para obter altura
int altura(Node* n) {
    return (n == nullptr) ? 0 : n->altura;
}

// Fator de balanceamento
int getBalance(Node* n) {
    return (n == nullptr) ? 0 : altura(n->esquerda) - altura(n->direita);
}

// Rotação à direita
Node* rotacaoDireita(Node* y) {
    Node* x = y->esquerda;
    Node* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}

// Rotação à esquerda
Node* rotacaoEsquerda(Node* x) {
    Node* y = x->direita;
    Node* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    return y;
}

// Inserção AVL
Node* inserir(Node* node, int valor) {

    // Inserção normal (BST)
    if (node == nullptr)
        return new Node(valor);

    if (valor < node->valor)
        node->esquerda = inserir(node->esquerda, valor);
    else if (valor > node->valor)
        node->direita = inserir(node->direita, valor);
    else
        return node; // sem duplicatas

    // Atualiza altura
    node->altura = 1 + max(altura(node->esquerda), altura(node->direita));

    int balance = getBalance(node);

    // LL
    if (balance > 1 && valor < node->esquerda->valor)
        return rotacaoDireita(node);

    // RR
    if (balance < -1 && valor > node->direita->valor)
        return rotacaoEsquerda(node);

    // LR
    if (balance > 1 && valor > node->esquerda->valor) {
        node->esquerda = rotacaoEsquerda(node->esquerda);
        return rotacaoDireita(node);
    }

    // RL
    if (balance < -1 && valor < node->direita->valor) {
        node->direita = rotacaoDireita(node->direita);
        return rotacaoEsquerda(node);
    }

    return node;
}

// Pré-ordem
void preOrdem(Node* root) {
    if (root != nullptr) {
        cout << root->valor << " ";
        preOrdem(root->esquerda);
        preOrdem(root->direita);
    }
}

int main() {
    Node* root = nullptr;

    int valores[] = {3, 5, 4};

    for (int v : valores) {
        root = inserir(root, v);
    }

    cout << "Pre-ordem da AVL:\n";
    preOrdem(root);

    return 0;
}