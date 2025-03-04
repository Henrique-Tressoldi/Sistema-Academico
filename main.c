#include "main.h"


int main() {
    t_curso curso;
    int opcao;
    inicializar(&curso);

    do {
        exibir_menu(); 
        opcao = obter_opcao_menu();
        processar_opcao_menu(opcao, &curso);
    } while (opcao != 0);
    

    return 0;
}

