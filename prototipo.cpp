#include <iostream>
#include "json.hpp"
#include <fstream>
#include <vector>
using namespace std;
using json = nlohmann::json;

bool close = true;
bool closeSale = true;
int mainOption;

struct Produto
{
   string product;
   float price;
};

struct ItemCarrinho
{
    int indiceProduto;
    int quantProduto;
};

struct Extrato
{
    string produto;
    int quantidade;
    float valorPago;

};


vector<Produto> produtos;
vector<ItemCarrinho> carrinho;
vector<Extrato> vendas;


void registrarProduto();
void listaProduto();
void realizarVenda();
void carrinhoCompras();
void visualizarCarrinho();
void finalizarCompra();
void clearScreen();
void to_json(json& j, const Produto& p);
void from_json(const json& j, Produto& p);
void to_json(json& j, const Extrato& e);
void from_json(const json& j, Extrato& e);
void carregarProdutos();
void salvarProdutos();
void carregarExtrato();
void salvarExtrato();
void editarProduto();
void removerProduto();
void verificarExtrato();
int lerInteiro();
float lerFloat();
void pausar();


int main(){
    carregarProdutos();
    carregarExtrato();
    do{
    cout << "Bem vindo ao sistema de super-mercado VERSÃO 3.0\n\n";
    cout << "[SELECIONE UMA OPÇÃO]\n";
    cout << "[1] Registrar produto.\n";
    cout << "[2] Lista de produtos.\n";
    cout << "[3] Realizar venda.\n";
    cout << "[4] Carrinho de Compras.\n";
    cout << "[5] Visualizar Carrinho.\n";
    cout << "[6] Finalizar Compras. \n";
    cout << "[7] Extrato de Compras.\n";
    cout << "[8] Sair.\n";
    mainOption = lerInteiro();

    switch (mainOption)
    {
    case 1:
       registrarProduto();
        break;
    case 2:
        listaProduto();
        break;
    case 3:
        realizarVenda();
        break;
    case 4:
        carrinhoCompras();
        break;
    case 5:
        visualizarCarrinho();
        break;
    case 6:
        finalizarCompra();
        break;
    case 7:
        verificarExtrato();
        break;
    case 8:
        close = false;
        break;
    default:
        cout << "Invalido.\n";
        clearScreen();
        break;
    }




    } while(close);
    cout << "Até mais!\n";
    return 0;
}

void registrarProduto(){
    clearScreen();


    string nome;
    float preco;
    cout << "Digite o nome do produto: ";
    cin.ignore();
    getline(cin, nome);

    for(const auto& p : produtos){
        if(p.product == nome){
            cout << "Produto com esse nome já está registrado.\n\n";
            pausar();
            clearScreen();
            return;
        }
    }

    cout << "Digite o preço do produto seguindo o exemplo (0.00) : ";
    preco = lerFloat();
    
    Produto newProduct = {nome, preco};
    produtos.push_back(newProduct);

    salvarProdutos();

    pausar();
    clearScreen();
}


void listaProduto(){
    clearScreen();
    int opt;
    cout << "[LISTA DE PRODUTOS]\n\n";
    cout << "EM ESTOQUE: " << produtos.size() << "\n\n";

    for(int i = 0; i < produtos.size(); i++){
            cout << " | NUMERAÇÃO: " << i << "\n";
            cout << " | PRODUTO: " << produtos[i].product << "\n";
            cout << " | PREÇO: " << produtos[i].price << "\n\n";
    }

    cout << "[1] Editar produto\n";
    cout << "[2] Remover produto\n";
    cout << "[3] Voltar\n";
    opt = lerInteiro();

    switch(opt){
    case 1:
        editarProduto();
        break;
    case 2:
        removerProduto();
        break;
    case 3:
    clearScreen();
        break;
    default:
        clearScreen();
        break;
    }
}


void realizarVenda(){
    clearScreen();
    int num;
    int quantidadeProduto;
    float valorPago;
    cout << "[REALIZAR VENDA DE PRODUTO]\n";
    cout << "Digite a numeração do produto a ser comprado (Caso não saiba, verifica a lista de produtos) : ";
    num = lerInteiro();

    if(num >= 0 && num < produtos.size()){
        cout << "Digite a quantidade do produto: ";
        quantidadeProduto = lerInteiro();
    if(quantidadeProduto > 0){

    clearScreen();
    float valorTotal = produtos[num].price * quantidadeProduto;

    cout << "[SUCESSO]\n\n";
    cout << "| PRODUTO ENCONTRADO: " << produtos[num].product << " | QUANTIDADE: " << quantidadeProduto << "\n";
    cout << "| PREÇO TOTAL: R$" << valorTotal << " REAIS | \n\n";
    cout << "Digite o valor pago pelo cliente: R$";
    valorPago = lerFloat();
    clearScreen();


        if(valorPago > valorTotal){
            float troco = valorPago - valorTotal;
            cout << "Produto pago com sucesso!\n\n";
            cout << "Valor do produto: R$" << valorTotal << " Reais \n";
            cout << "Valor pago pelo cliente: R$" << valorPago << " Reais \n";
            cout << "Troco do cliente: R$" << troco << "\n";

                Extrato novaVenda;
                novaVenda.produto = produtos[num].product;
                novaVenda.quantidade = quantidadeProduto;
                novaVenda.valorPago = produtos[num].price * quantidadeProduto;
                vendas.push_back(novaVenda);
        
            salvarExtrato();
        }else{
            float valorNecessario = valorTotal - valorPago;
            cout << "Não foi possivel realizar o pagamento!\n\n";
            cout << "Valor do produto: R$" << valorTotal << " Reais \n";
            cout << "Valor pago pelo cliente: R$" << valorPago << " Reais \n\n";
            cout << "Ainda precisa de: R$" << valorNecessario << " Reais para completar o pagamento\n";
        } 
    } else{
        cout << "[ERRO]\n\n";
        cout << "Quantidade de produto inválida.\n";
    }
}else{
    cout << "[ERRO]\n\n";
    cout << "NÃO FOI ENCONTRADO NENHUM PRODUTO VÁLIDO COM ESSA NUMERAÇÃO!\n";
    cout << "(Verifique a lista de produtos pra uma consulta mais avançada)\n\n";
}
    pausar();
    clearScreen();
}




void carrinhoCompras() {
    int numProduto;
    int quantidade;

    clearScreen(); 
    cout << "Digite o número do produto a ser adicionado no carrinho: ";
    numProduto = lerInteiro();

    if (numProduto >= 0 && numProduto < produtos.size()) {
        cout << "Produto selecionado: " << produtos[numProduto].product << "\n\n";
        
        cout << "Digite a quantidade a ser comprada: ";
        quantidade = lerInteiro();

        bool numEncontrado = false;
        
    
        for (auto& item : carrinho) {
            if (item.indiceProduto == numProduto) {
               
                item.quantProduto += quantidade;
                numEncontrado = true;
                break;
            }
        }

        if (!numEncontrado) {
            carrinho.push_back({numProduto, quantidade});
            cout << "Produto(s) adicionado(s) com sucesso ao carrinho!\n\n";
        } else {
            cout << "Produto atualizado no carrinho!\n\n";
        }

    } else {
        cout << "[ERRO]\n\n";
        cout << "NÃO FOI ENCONTRADO NENHUM PRODUTO VÁLIDO COM ESSA NUMERAÇÃO!\n";
        cout << "(Verifique a lista de produtos para uma consulta mais avançada)\n\n";
    }

   
    pausar();
    clearScreen();
}


void visualizarCarrinho(){
clearScreen();
cout << "[Carrinho de Compras]\n\n";
float totalCarrinho = 0.0;

for(auto& item : carrinho){
    float precoProduto = produtos[item.indiceProduto].price;
    string nomeItem = produtos[item.indiceProduto].product;
    float totalItem = precoProduto * item.quantProduto;

    cout << "Produto: " << nomeItem << " | Quantidade: " << item.quantProduto << "\n";
    cout << "Preço: R$" << precoProduto << "\n";
    cout << "Total: R$" << totalItem << "\n\n";

    totalCarrinho += totalItem;
}

cout << "\n Total do carrinho: R$" << totalCarrinho << "\n\n";

pausar();
clearScreen();
}



void finalizarCompra(){
clearScreen();
float totalCarrinho = 0.0;

for(auto& item : carrinho){
    totalCarrinho += produtos[item.indiceProduto].price * item.quantProduto;
}

if(totalCarrinho > 0){

cout << "[FINALIZAR COMPRA]\n\n";
cout << "Valor total da compra: R$" << totalCarrinho << "\n\n";

float valorPago;
cout << "Valor pago pelo cliente: R$";
valorPago = lerFloat();

if(valorPago < totalCarrinho){
    cout << "Valor insuficiente para concluir a compra.\n\n";
    float valorFaltante = totalCarrinho - valorPago;
    cout << "Ainda falta: " << valorFaltante << " para concluir a compra.\n";
} else{
    float troco = valorPago - totalCarrinho;
    cout << "Compra concluida com sucesso!\n\n";
    cout << "Troco do cliente: R$" << troco << "\n";

    for(auto& item : carrinho){
        Extrato novaVenda;
        novaVenda.produto = produtos[item.indiceProduto].product;
        novaVenda.quantidade = item.quantProduto;
        novaVenda.valorPago = produtos[item.indiceProduto].price * item.quantProduto;
        vendas.push_back(novaVenda);
    }


    salvarExtrato();
    carrinho.clear();
    pausar();
    clearScreen();
}

} else{
    pausar();
    clearScreen();
    }
}


void editarProduto(){
clearScreen();
int indice;
cout << "[EDITAR PRODUTO]\n\n";
cout << "Digite a numeração do produto que deseja editar: ";
indice = lerInteiro();

if(indice >= 0 && indice < produtos.size()){
    string nomeNovo;
    float precoNovo;
    cout << "\nProduto encontrado: " << produtos[indice].product << "\n";
    cout << "Digite o novo produto: ";
    cin.ignore();
    getline(cin, nomeNovo);
    cout << "Digite o novo preço: ";
    precoNovo = lerFloat();

    produtos[indice].product = nomeNovo;
    produtos[indice].price = precoNovo;

   salvarProdutos();

    cout << "Produto atualizado com sucesso!\n";
} else{
    cout << "[ERRO]\n\n";
    cout << "NÃO FOI ENCONTRADO NENHUM PRODUTO VÁLIDO COM ESSA NUMERAÇÃO!\n";
}
    pausar();
    clearScreen();
}




void removerProduto(){
    clearScreen();
    cout << "[REMOVER PRODUTO]\n\n";
    int indice;
    cout << "Digite a numeração do produto que deseja remover: ";
    indice = lerInteiro();
    
    if(indice >= 0 && indice < produtos.size()){
        char confirm;
        cout << "Tem certeza que deseja remover: " << produtos[indice].product << "? [S/N] ";
        cin >> confirm;

        if(confirm == 's' || confirm == 'S'){
        cout << "Produto: " << produtos[indice].product << " Foi removido com sucesso!\n\n";

        produtos.erase(produtos.begin() + indice);


    
        salvarProdutos();
        }else{
            cout << "Remoção cancelada com sucesso.\n\n";
        }

    }
    pausar(); 
    clearScreen();
}


void verificarExtrato(){
    clearScreen();
    if(vendas.size() > 0){
    cout << "[EXTRATO DE COMPRAS]\n\n";
    cout << "Total de vendas: " << vendas.size() << "\n\n";

    for(int i = 0; i < vendas.size(); i++){
            cout << " | PRODUTO: " << vendas[i].produto << "\n";
            cout << " | QUANTIDADE: " << vendas[i].quantidade << "\n"; 
            cout << " | VALOR PAGO: " << vendas[i].valorPago << "\n\n";
    } 
    } else{
        cout << "[Não existe nenhum extrato registrado]\n";
        cout << "Realize uma venda para consultar o extrato.\n\n";
    }
    pausar();
    clearScreen();
}


void to_json(json& j, const Produto& p){
    j = json{{"nome", p.product}, {"preco", p.price}};
}

void from_json(const json& j, Produto& p){
    j.at("nome").get_to(p.product);
    j.at("preco").get_to(p.price);
}

void to_json(json& j, const Extrato& e) {
    j = json{{"produto", e.produto}, {"quantidade", e.quantidade}, {"valorPago", e.valorPago}};
}

void from_json(const json& j, Extrato& e) {
    j.at("produto").get_to(e.produto);
    j.at("quantidade").get_to(e.quantidade);
    j.at("valorPago").get_to(e.valorPago);
}

void carregarProdutos(){
    ifstream in("produtos.json");
    if(in){
        json j;
        in >> j;
        in.close();
        produtos = j.get<vector<Produto>>();
    }
}

void carregarExtrato() {
    ifstream in("vendas.json");
    if (in) {
        json j;
        in >> j;
        in.close();
        vendas = j.get<vector<Extrato>>();
    }
}


void salvarExtrato() {
    json j = vendas;
    ofstream out("vendas.json");
    out << j.dump(4);
    out.close();
}



void clearScreen() {
    string escape = "\033[2J\033[1;1H";
    cout << escape;
}



int lerInteiro(){
int valor;
while(!(cin >> valor)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada inválida, porfavor digite um número inteiro: ";
    }
    return valor;
}



float lerFloat(){
float valor;
while(!(cin >> valor)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada inválida, porfavor digite um número decimal (ex: 0.00): ";
    }
    return valor;
}

void salvarProdutos() {
    json j = produtos;
    ofstream out("produtos.json");
    out << j.dump(4);
    out.close();
}


void pausar(){
    cout << "Pressione qualquer tecla pra continuar...";
    cin.get();
}
