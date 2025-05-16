#include "header.h"

//Algumas funções podem não estar atualizadas, recomendo utilizar a versão do windows.

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
void loading();
int lerInteiro();
float lerFloat();
void pausar();


int main(){
    carregarProdutos();
    carregarExtrato();
    do{
    cout << "\033[1;36m"; // Cor ciano forte
    cout << "╔══════════════════════════════════════╗\n";
    cout << "║       🛒  SUPERMERCADO v3.0          ║\n";
    cout << "╚══════════════════════════════════════╝\n";
    cout << "\033[0m"; // Reset cor
    
    cout << "\033[1;33m"; // Amarelo
    cout << "[SELECIONE UMA OPÇÃO]\n\n";
    cout << "\033[0m";
    
    cout << "\033[1;33m";
    cout << "═════════════════════════════════════════════\n";
    cout << " [1] 📝 Registrar produto\n";
    cout << " [2] 📦 Listar produtos\n";
    cout << " [3] 💰 Realizar venda\n";
    cout << " [4] 🛍️  Adicionar ao carrinho\n";
    cout << " [5] 🧾 Ver carrinho\n";
    cout << " [6] ✅ Finalizar compra\n";
    cout << " [7] 📊 Ver extrato de compras\n";
    cout << " [8] ❌ Sair do sistema\n";
    cout << "═════════════════════════════════════════════\n";
    cout << "\033[0m";
    
    cout << "\033[1;32m👉 Digite a opção desejada: \033[0m";
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
    cout << "\033[1;36m";
    cout << "╔═══════════════════════════════════════════╗\n";
    cout << "║          📝 REGISTRAR NOVO PRODUTO        ║\n";
    cout << "╚═══════════════════════════════════════════╝\n";
    cout << "\033[0m\n";
    cout << "📦 Digite o nome do produto: ";
    cin.ignore();
    getline(cin, nome);

    for(const auto& p : produtos){
        if(p.product == nome){
            cout << "\n\033[1;31m[⚠️ ERRO] Produto com esse nome já está registrado!\033[0m\n\n";
            pausar();
            clearScreen();
            return;
        }
    }

    cout << "💲 Digite o preço do produto (formato 0.00): ";
    preco = lerFloat();
    
    Produto newProduct = {nome, preco};
    produtos.push_back(newProduct);

    salvarProdutos();
    loading();
    cout << "\n\033[1;32m✅ Produto registrado com sucesso!\033[0m\n\n";
    pausar();
    clearScreen();
}


void listaProduto(){
    clearScreen();
    int opt;
    cout << "\033[1;36m";
    cout << "╔═══════════════════════════════════════════╗\n";
    cout << "║           📦 LISTA DE PRODUTOS            ║\n";
    cout << "╚═══════════════════════════════════════════╝\n";
    cout << "\033[0m\n";
    cout << "📋 Produtos em estoque: \033[1;33m" << produtos.size() << "\033[0m\n\n";

    if(produtos.empty()){
        cout << "\033[1;31m[⚠️ Nenhum produto cadastrado]\033[0m\n\n";
    } else{
    for(int i = 0; i < produtos.size(); i++){
        cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
        cout << "🔢 Numeração: \033[1;34m" << i << "\033[0m\n";
        cout << "📦 Produto:   \033[1;37m" << produtos[i].product << "\033[0m\n";
        cout << "💰 Preço:     \033[1;32mR$" << fixed << setprecision(2) << produtos[i].price << "\033[0m\n";
    }
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";
    }
    cout << "\033[1;36m[Opções de Gerenciamento]\033[0m\n";
    cout << " [1] ✏️  Editar produto\n";
    cout << " [2] 🗑️  Remover produto\n";
    cout << " [3] 🔙 Voltar ao menu principal\n\n";
    cout << "\033[1;32m👉 Digite a opção desejada: \033[0m";
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
        cout << "\n\033[1;31m[⚠️ Opção inválida. Retornando ao menu.]\033[0m\n";
        pausar();
        clearScreen();
        break;
    }
}


void realizarVenda(){
    clearScreen();
    int num;
    int quantidadeProduto;
    float valorPago;
    cout << "\033[1;36m";
    cout << "╔═══════════════════════════════════════════╗\n";
    cout << "║            💰 REALIZAR VENDA              ║\n";
    cout << "╚═══════════════════════════════════════════╝\n";
    cout << "\033[0m\n";

    cout << "🔢 Digite a numeração do produto desejado (verifique a lista se necessário): ";
    num = lerInteiro();

    if(num >= 0 && num < produtos.size()){
        cout << "📦 Produto selecionado: \033[1;37m" << produtos[num].product << "\033[0m\n";
        cout << "📦 Preço unitário: \033[1;32mR$" << fixed << setprecision(2) << produtos[num].price << "\033[0m\n";
        cout << "📦 Digite a quantidade desejada: ";
        quantidadeProduto = lerInteiro();
    if(quantidadeProduto > 0){

    clearScreen();
    float valorTotal = produtos[num].price * quantidadeProduto;

    cout << "\033[1;34m🔍 RESUMO DA VENDA:\033[0m\n";
    cout << "🛍️ Produto: " << produtos[num].product << "\n";
    cout << "📦 Quantidade: " << quantidadeProduto << "\n";
    cout << "💰 Valor total: \033[1;32mR$" << valorTotal << "\033[0m\n\n";

    cout << "💵 Digite o valor pago pelo cliente: R$";
    valorPago = lerFloat();
    clearScreen();
    loading();

        if(valorPago >= valorTotal){
            float troco = valorPago - valorTotal;
            cout << "\033[1;32m✅ Pagamento realizado com sucesso!\033[0m\n\n";
            cout << "💰 Valor do produto: R$" << valorTotal << "\n";
            cout << "💵 Valor pago: R$" << valorPago << "\n";
            cout << "💸 Troco: R$" << troco << "\n";

                Extrato novaVenda;
                novaVenda.produto = produtos[num].product;
                novaVenda.quantidade = quantidadeProduto;
                novaVenda.valorPago = produtos[num].price * quantidadeProduto;
                vendas.push_back(novaVenda);
        
            salvarExtrato();
        }else{
            float valorNecessario = valorTotal - valorPago;
            cout << "\033[1;31m❌ Pagamento insuficiente!\033[0m\n\n";
            cout << "💰 Valor necessário: R$" << valorTotal << "\n";
            cout << "💵 Valor pago: R$" << valorPago << "\n";
            cout << "🚫 Faltam: R$" << valorNecessario << "\n";
        } 
    } else{
        cout << "\n\033[1;31m[⚠️ ERRO] Quantidade inválida.\033[0m\n";
    }
}else{
    cout << "\n\033[1;31m[⚠️ ERRO] Produto com essa numeração não encontrado!\033[0m\n";
    cout << "🧾 Verifique a lista de produtos e tente novamente.\n";
}
    pausar();
    clearScreen();
}




void carrinhoCompras() {
    int numProduto;
    int quantidade;

    clearScreen(); 
    cout << "\033[1;36m";
    cout << "╔═══════════════════════════════════════════╗\n";
    cout << "║         🛒 ADICIONAR AO CARRINHO          ║\n";
    cout << "╚═══════════════════════════════════════════╝\n";
    cout << "\033[0m\n";
    cout << "🔢 Digite o número do produto que deseja adicionar: ";
    numProduto = lerInteiro();

    if (numProduto >= 0 && numProduto < produtos.size()) {
        cout << "📦 Produto selecionado: \033[1;37m" << produtos[numProduto].product << "\033[0m\n";
        cout << "💲 Preço unitário: R$" << fixed << setprecision(2) << produtos[numProduto].price << "\n";
        cout << "🔢 Digite a quantidade desejada: ";
        quantidade = lerInteiro();
    
        if(quantidade <= 0){
            cout << "\n\033[1;31m❌ Quantidade inválida! Deve ser maior que zero.\033[0m\n";
        }else{

        

        bool numEncontrado = false;
        
    
        for (auto& item : carrinho) {
            if (item.indiceProduto == numProduto) {
               
                item.quantProduto += quantidade;
                numEncontrado = true;
                break;
            }
        }

        if (numEncontrado) {
            cout << "\n\033[1;34m🔄 Produto já estava no carrinho. Quantidade atualizada com sucesso!\033[0m\n";
        } else {
            carrinho.push_back({numProduto, quantidade});
            cout << "\n\033[1;32m✅ Produto adicionado com sucesso ao carrinho!\033[0m\n";
        }
    }

    } else {
          cout << "\n\033[1;31m[⚠️ ERRO] Produto não encontrado com essa numeração!\033[0m\n";
          cout << "🧾 Verifique a lista de produtos e tente novamente.\n";
    }

   
    pausar();
    clearScreen();
}


void visualizarCarrinho(){
clearScreen();

cout << "\033[1;36m";
cout << "╔═════════════════════════════════════════╗\n";
cout << "║          🧾  CARRINHO DE COMPRAS        ║\n";
cout << "╚═════════════════════════════════════════╝\n";
cout << "\033[0m\n";

float totalCarrinho = 0.0;

if(carrinho.empty()){
    cout << "\033[1;33m⚠️  Seu carrinho está vazio!\033[0m\n";
} else{
for(auto& item : carrinho){
    float precoProduto = produtos[item.indiceProduto].price;
    string nomeItem = produtos[item.indiceProduto].product;
    float totalItem = precoProduto * item.quantProduto;

    cout << "🛒 Produto: \033[1;37m" << nomeItem << "\033[0m\n";
    cout << "🔢 Quantidade: \033[1;36m" << item.quantProduto << "\033[0m\n";
    cout << "💰 Preço unitário: R$" << fixed << setprecision(2) << precoProduto << "\n";
    cout << "📦 Total do item: \033[1;32mR$" << totalItem << "\033[0m\n";
    cout << "────────────────────────────────────────────\n";

    totalCarrinho += totalItem;
}   
    cout << "\n🧮 \033[1;32mTOTAL DO CARRINHO: R$" << fixed << setprecision(2) << totalCarrinho << "\033[0m\n";
}
cout << endl;
pausar();
clearScreen();
}



void finalizarCompra(){
clearScreen();
float totalCarrinho = 0.0;

for(auto& item : carrinho){
    totalCarrinho += produtos[item.indiceProduto].price * item.quantProduto;
}


cout << "\033[1;36m";
cout << "╔════════════════════════════════════════════╗\n";
cout << "║           ✅ FINALIZAR COMPRA              ║\n";
cout << "╚════════════════════════════════════════════╝\n";
cout << "\033[0m\n";

if(totalCarrinho > 0){
cout << "🧮 Total da compra: \033[1;32mR$" << fixed << setprecision(2) << totalCarrinho << "\033[0m\n";
float valorPago;
cout << "💵 Valor pago pelo cliente: R$";
valorPago = lerFloat();
loading();
if(valorPago < totalCarrinho){
    cout << "\n\033[1;31m❌ Valor insuficiente!\033[0m\n";
    float valorFaltante = totalCarrinho - valorPago;
    cout << "🔻 Ainda falta: \033[1;33mR$" << valorFaltante << "\033[0m para completar a compra.\n";
} else{
    float troco = valorPago - totalCarrinho;
    cout << "\n\033[1;32m✅ Compra realizada com sucesso!\033[0m\n";
    cout << "💵 Troco para o cliente: \033[1;36mR$" << fixed << setprecision(2) << troco << "\033[0m\n\n";


    for(auto& item : carrinho){
        Extrato novaVenda;
        novaVenda.produto = produtos[item.indiceProduto].product;
        novaVenda.quantidade = item.quantProduto;
        novaVenda.valorPago = produtos[item.indiceProduto].price * item.quantProduto;
        vendas.push_back(novaVenda);
    }


    salvarExtrato();
    carrinho.clear();
}

} else{
    cout << "\033[1;33m⚠️  Carrinho vazio! Adicione produtos antes de finalizar a compra.\033[0m\n";
}

cout << endl;
pausar();
clearScreen();
}


void editarProduto(){
clearScreen();
int indice;
cout << "\033[1;36m";
cout << "╔════════════════════════════════════════════╗\n";
cout << "║              🛠️ EDITAR PRODUTO             ║\n";
cout << "╚════════════════════════════════════════════╝\n";
cout << "\033[0m\n";
cout << "🔢 Digite a numeração do produto que deseja editar: ";
indice = lerInteiro();
if(indice >= 0 && indice < produtos.size()){
    string nomeNovo;
    float precoNovo;
    cout << "\n🧾 Produto atual: \033[1;37m" << produtos[indice].product << "\033[0m\n";
    cout << "✏️  Digite o novo nome: ";
    cin.ignore();
    getline(cin, nomeNovo);
    cout << "💰 Digite o novo preço (formato 0.00): ";
    precoNovo = lerFloat();

    produtos[indice].product = nomeNovo;
    produtos[indice].price = precoNovo;

   salvarProdutos();
   loading();
    cout << "\n\033[1;32m✅ Produto atualizado com sucesso!\033[0m\n";
} else{
    cout << "\n\033[1;31m❌ Produto com numeração inválida!\033[0m\n";
    cout << "🔍 Verifique a lista de produtos e tente novamente.\n";
}
    pausar();
    clearScreen();
}




void removerProduto(){
    clearScreen();
    cout << "\033[1;36m";
    cout << "╔════════════════════════════════════════════╗\n";
    cout << "║             🗑️ REMOVER PRODUTO             ║\n";
    cout << "╚════════════════════════════════════════════╝\n";
    cout << "\033[0m\n";

    int indice;
    cout << "🔢 Digite a numeração do produto que deseja remover: ";
    indice = lerInteiro();
    
    if(indice >= 0 && indice < produtos.size()){
        char confirm;
        cout << "\n🧾 Produto encontrado: \033[1;37m" << produtos[indice].product << "\033[0m\n";
        cout << "❓ Tem certeza que deseja remover este produto? [S/N]: ";
        cin >> confirm;

        if(confirm == 's' || confirm == 'S'){
            loading();
            cout << "\n\033[1;32m✅ Produto removido com sucesso!\033[0m\n";
            cout << "🗂️ Nome: \033[1;36m" << produtos[indice].product << "\033[0m\n\n";

        produtos.erase(produtos.begin() + indice);


    
        salvarProdutos();
        }else{
            cout << "\n\033[1;33m⚠️ Remoção cancelada pelo usuário.\033[0m\n";
        }

    } else{
        cout << "\n\033[1;31m❌ Produto com numeração inválida!\033[0m\n";
        cout << "🔍 Verifique a lista e tente novamente.\n";
    }

    cout << endl;
    pausar(); 
    clearScreen();
}


void verificarExtrato(){
    clearScreen();
    float totalArrecadado = 0.0;
    if(vendas.size() > 0){
        cout << "\033[1;36m";
        cout << "╔════════════════════════════════════════════╗\n";
        cout << "║          📊 EXTRATO DE COMPRAS             ║\n";
        cout << "╚════════════════════════════════════════════╝\n";
        cout << "\033[0m\n";
        cout << "\033[1;33m";
        cout << "Total de vendas realizadas: " << vendas.size() << "\n\n";
        cout << "\033[0m";

    for(int i = 0; i < vendas.size(); i++){
        cout << "📦 Produto: \033[1;37m" << vendas[i].produto << "\033[0m\n";
        cout << "🔢 Quantidade: \033[1;32m" << vendas[i].quantidade << "\033[0m\n";
        cout << "💰 Valor pago: R$" << vendas[i].valorPago << "\n\n";

        totalArrecadado += vendas[i].valorPago;
    } 
    cout << "══════════════════════════════════════════════\n";
    cout << "💵 \033[1;32mTOTAL ARRECADADO: R$" << fixed << setprecision(2) << totalArrecadado << "\033[0m\n";

    } else{
        cout << "\033[1;31m";
        cout << "❌ Não existe nenhum extrato registrado ainda!\n";
        cout << "Realize uma venda para gerar o extrato.\n\n";
        cout << "\033[0m";
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
    cin.ignore();
    cin.get();
}

void loading() {
    const char spinner[] = {'|', '/', '-', '\\'};
    cout << "\nCarregando ";
    for (int i = 0; i < 20; ++i) {
        cout << spinner[i % 4] << '\b';
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(150));
    }
    cout << "| Carregamento concluído!\n";
}
