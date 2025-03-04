#include "main.h"

void inicializar(t_curso *curso) {
    curso->quantidade_turmas = 0;
    curso->turmas = (t_turma *)malloc(sizeof(t_turma));
}

void exibir_menu(void) {
    printf("1- inserir turma\n");
    printf("2- inserir disciplina\n");
    printf("3- inserir aluno\n");
    printf("4- listar turma\n");
    printf("5- listar disciplinas\n");
    printf("6- listar alunos\n");
    printf("7- remover turma\n");
    printf("8- remover disciplinas\n");
    printf("9- remover alunos\n");
    printf("0- finalizar\n");
}

int obter_opcao_menu(void) {
    int escolha;
    printf("Escolha a opcao desejada: \n");
    scanf("%i", &escolha);
    return escolha;
}

void processar_opcao_menu(int opcao, t_curso *curso) {
    switch (opcao) {
    case 1:
        inserir_turma(curso);
        break;
    case 2:
        {
            t_turma* turma = obter_turma(curso);
            if (turma) {
                inserir_disciplina(turma);
            }
        }
        break;
    case 3: {
    t_turma* turma = obter_turma(curso); 
    if (turma) {
        t_disciplina* disciplina = obter_disciplina(turma);
        if (disciplina) {
            t_aluno novo_aluno;

           
            printf("Digite a matrícula do aluno: ");
            scanf("%d", &novo_aluno.matricula);

            if (existe_aluno(disciplina, novo_aluno.matricula)) {
                printf("Aluno já existe na disciplina.\n");
            } else {
                getchar(); 
                printf("Digite o nome do aluno: ");
                obter_texto(&novo_aluno.nome);

                printf("Digite o telefone do aluno: ");
                scanf("%s", novo_aluno.telefone);

                
                disciplina->quantidade_alunos++;
                disciplina->alunos = realloc(disciplina->alunos, disciplina->quantidade_alunos * sizeof(t_aluno));
                if (!disciplina->alunos) {
                    printf("Erro ao realocar memória para armazenar alunos.\n");
                    exit(1);
                }

                disciplina->alunos[disciplina->quantidade_alunos - 1] = novo_aluno;

                printf("Aluno inserido com sucesso!\n");
            }
        }
    }
}

        break;
    case 4:
        listar_turmas(curso);
        break;
    case 5:
        {
            t_turma* turma = obter_turma(curso);
            if (turma) {
                listar_disciplinas(turma);
            }
        }
        break;
    case 6:
        {
            t_turma* turma = obter_turma(curso);
            if (turma) {
                t_disciplina* disciplina = obter_disciplina(turma);
                if (disciplina) {
                    listar_alunos(disciplina);
                }
            }
        }
        break;
    case 7:
        remover_turma(curso);
        break;
    case 8:
        {
            t_turma* turma = obter_turma(curso);
            if (turma) {
                remover_disciplina(turma);
            }
        }
        break;
    case 9:
        {
            t_turma* turma = obter_turma(curso);
            if (turma) {
                t_disciplina* disciplina = obter_disciplina(turma);
                if (disciplina) {
                    remover_aluno(disciplina);
                }
            }
        }
        break;
    case 0:
        escrever_arquivo(curso);
        liberar_memoria_curso(curso);
        printf("Saindo...\n");
        break;
    default:
        printf("Opcao invalida. Tente novamente.\n");
    }
}

int existe_turma(t_curso *curso, int numero) {
    for (int i = 0; i < curso->quantidade_turmas; i++) {
        if (curso->turmas[i].numero == numero) {
            return 1;
        }
    }
    return 0;
}

int existe_disciplina(t_turma *turma, int codigo) {
    for (int i = 0; i < turma->quantidade_disciplinas; i++) {
        if (turma->disciplinas[i].codigo == codigo) {
            return 1;
        }
    }
    return 0;
}

int existe_aluno(t_disciplina *disciplina, int matricula) {
    for (int i = 0; i < disciplina->quantidade_alunos; i++) {
        if (disciplina->alunos[i].matricula == matricula) {
            return 1;
        }
    }
    return 0;
}

void obter_texto(char **texto) {
    char caractere;
    int tamanho_texto = 0;

   
    *texto = NULL;

    
    while((caractere = getchar()) != '\n') {
        
        *texto = realloc(*texto, (tamanho_texto + 1) * sizeof(char));
        
        
        if (*texto == NULL) {
            printf("Erro na alocação de memória.\n");
            exit(1);
        }
        
        
        (*texto)[tamanho_texto++] = caractere;
    }

   
    (*texto)[tamanho_texto] = '\0';
}

t_turma *obter_turma(t_curso *curso) {
    int numero;
    printf("Digite o numero da turma: ");
    scanf("%d", &numero);
    for (int i = 0; i < curso->quantidade_turmas; i++) {
        if (curso->turmas[i].numero == numero) {
            return &curso->turmas[i];
        }
    }
    printf("Turma não encontrada!\n");
    return NULL;
}

t_disciplina *obter_disciplina(t_turma *turma) {
    int codigo;
    printf("Digite o codigo da disciplina: ");
    scanf("%d", &codigo);
    for (int i = 0; i < turma->quantidade_disciplinas; i++) {
        if (turma->disciplinas[i].codigo == codigo) {
            return &turma->disciplinas[i];
        }
    }
    printf("Disciplina não encontrada!\n");
    return NULL;
}

t_aluno *obter_aluno(t_disciplina *disciplina) {
    int matricula;
    printf("Digite a matricula do aluno: ");
    scanf("%d", &matricula);
    for (int i = 0; i < disciplina->quantidade_alunos; i++) {
        if (disciplina->alunos[i].matricula == matricula) {
            return &disciplina->alunos[i];
        }
    }
    printf("Aluno não encontrado!\n");
    return NULL;
}

void inserir_turma(t_curso *curso) {
    t_turma nova_turma;
    printf("Digite o numero da turma: ");
    scanf("%d", &nova_turma.numero);

    if (existe_turma(curso, nova_turma.numero)) {
        printf("Turma ja existe.\n");
        return;
    }

    nova_turma.quantidade_disciplinas = 0;
    nova_turma.disciplinas = (t_disciplina *)malloc(sizeof(t_disciplina));

    curso->quantidade_turmas++;
    curso->turmas = (t_turma *)realloc(curso->turmas, curso->quantidade_turmas * sizeof(t_turma));
    curso->turmas[curso->quantidade_turmas - 1] = nova_turma;

    printf("Turma inserida com sucesso!\n");
}

void inserir_disciplina(t_turma *turma) {
    t_disciplina nova_disciplina;
    printf("Digite o codigo da disciplina: ");
    scanf("%d", &nova_disciplina.codigo);
    getchar();

    if (existe_disciplina(turma, nova_disciplina.codigo)) {
        printf("Disciplina já existe.\n");
        return;
    }

    printf("Digite o nome da disciplina: ");
    nova_disciplina.nome = (char*) malloc(sizeof(char));
    obter_texto(&nova_disciplina.nome); 
    nova_disciplina.quantidade_alunos = 0;
    nova_disciplina.alunos = (t_aluno *)malloc(sizeof(t_aluno));

    turma->quantidade_disciplinas++;
    turma->disciplinas = (t_disciplina *)realloc(turma->disciplinas, turma->quantidade_disciplinas * sizeof(t_disciplina));

    turma->disciplinas[turma->quantidade_disciplinas - 1] = nova_disciplina;

    printf("Disciplina inserida com sucesso!\n");
}
void inserir_aluno(t_disciplina *disciplina) {
    t_aluno novo_aluno;
    novo_aluno.nome = (char*)malloc(sizeof(char));

    printf("Informe a matricula do aluno: ");
    scanf("%i", &novo_aluno.matricula);

    if (existe_aluno(disciplina,novo_aluno.matricula)) {
        printf("O aluno já existe!\n");
        return;
    }

    printf("Digite o nome do aluno: \n");
    obter_texto(&novo_aluno.nome);
    printf("Digite o telefone do aluno: \n");
    scanf("%s", novo_aluno.telefone);

    disciplina->quantidade_alunos++;
    disciplina->alunos = (t_aluno *)realloc(disciplina->alunos, disciplina->quantidade_alunos * sizeof(t_aluno));

    disciplina->alunos[disciplina->quantidade_alunos - 1] = novo_aluno;
 
    printf("Aluno inserido com sucesso!\n");
}


void remover_turma(t_curso *curso) {
    int numero;
    printf("Digite o numero da turma a ser removida: ");
    scanf("%d", &numero);

    for (int i = 0; i < curso->quantidade_turmas; i++) {
        if (curso->turmas[i].numero == numero) {
            free(curso->turmas[i].disciplinas);
            for (int j = i; j < curso->quantidade_turmas - 1; j++) {
                curso->turmas[j] = curso->turmas[j + 1];
            }
            curso->quantidade_turmas--;
            curso->turmas = realloc(curso->turmas, curso->quantidade_turmas * sizeof(t_turma));
            printf("Turma removida com sucesso!\n");
            return;
        }
    }
    printf("Turma nao encontrada.\n");
}

void remover_disciplina(t_turma *turma) {
    int codigo;
    printf("Digite o codigo da disciplina a ser removida: ");
    scanf("%d", &codigo);

    for (int i = 0; i < turma->quantidade_disciplinas; i++) {
        if (turma->disciplinas[i].codigo == codigo) {
            free(turma->disciplinas[i].alunos);
            for (int j = i; j < turma->quantidade_disciplinas - 1; j++) {
                turma->disciplinas[j] = turma->disciplinas[j + 1];
            }
            turma->quantidade_disciplinas--;
            turma->disciplinas = realloc(turma->disciplinas, turma->quantidade_disciplinas * sizeof(t_disciplina));
            printf("Disciplina removida com sucesso!\n");
            return;
        }
    }
    printf("Disciplina nao encontrada.\n");
}

void remover_aluno(t_disciplina *disciplina) {
    int matricula;
    printf("Digite a matricula do aluno a ser removido: ");
    scanf("%d", &matricula);

    int i;
    for (i = 0; i < disciplina->quantidade_alunos; i++) {
        if (disciplina->alunos[i].matricula == matricula) {
            free(disciplina->alunos[i].nome);
            for (int j = i; j < disciplina->quantidade_alunos - 1; j++) {
                disciplina->alunos[j] = disciplina->alunos[j + 1];
            }
            disciplina->quantidade_alunos--;
            t_aluno* alunos_temp = realloc(disciplina->alunos, disciplina->quantidade_alunos * sizeof(t_aluno));
            if (disciplina->quantidade_alunos == 0) {
                free(disciplina->alunos);
                disciplina->alunos = NULL;
            } else if (alunos_temp != NULL) {
                disciplina->alunos = alunos_temp;
            } else {
                printf("Erro ao realocar memória.\n");
                exit(1);
            }
            printf("Aluno removido com sucesso!\n");
            return;
        }
    }
    printf("Aluno nao encontrado.\n");
}




void listar_turmas(t_curso *curso) {
    if (curso->quantidade_turmas == 0) {
        printf("Nao ha turmas cadastradas.\n");
        return;
    }
    for (int i = 0; i < curso->quantidade_turmas; i++) {
        printf("Turma numero: %d\n", curso->turmas[i].numero);
    }
}

void listar_disciplinas(t_turma *turma) {
    if (turma->quantidade_disciplinas == 0) {
        printf("Nao ha disciplinas cadastradas.\n");
        return;
    }
    for (int i = 0; i < turma->quantidade_disciplinas; i++) {
        printf("Disciplina codigo: %d, nome: %s\n", turma->disciplinas[i].codigo, turma->disciplinas[i].nome);
    }
}

void listar_alunos(t_disciplina *disciplina) {
    if (disciplina->quantidade_alunos == 0) {
        printf("Nao ha alunos cadastrados.\n");
        return;
    }
    for (int i = 0; i < disciplina->quantidade_alunos; i++) {
        printf("Aluno matricula: %d, nome: %s tel: %s \n", disciplina->alunos[i].matricula, disciplina->alunos[i].nome,disciplina->alunos[i].telefone);
    }
}

void liberar_memoria_curso(t_curso *curso) {
    for (int i = 0; i < curso->quantidade_turmas; i++) {
        liberar_memoria_turma(&curso->turmas[i]);
    }
    free(curso->turmas);
}

void liberar_memoria_turma(t_turma *turma) {
    for (int i = 0; i < turma->quantidade_disciplinas; i++) {
        liberar_memoria_disciplina(&turma->disciplinas[i]);
    }
    free(turma->disciplinas);
}

void liberar_memoria_disciplina(t_disciplina *disciplina) {
    for (int i = 0; i < disciplina->quantidade_alunos; i++) {
        liberar_memoria_aluno(&disciplina->alunos[i]);
    }
    free(disciplina->alunos);
}

void liberar_memoria_aluno(t_aluno *aluno) {
    free(aluno->nome);
}

void escrever_arquivo(t_curso *curso) {
   
    FILE *arquivo_turma = fopen("turma.txt", "w");
    FILE *arquivo_disciplina = fopen("disciplina.txt", "w");
    FILE *arquivo_aluno = fopen("aluno.txt", "w");

    
    if (arquivo_turma == NULL) {
        printf("Erro ao abrir o arquivo 'turma.txt'.\n");
        return;
    }
    if (arquivo_disciplina == NULL) {
        printf("Erro ao abrir o arquivo 'disciplina.txt'.\n");
        fclose(arquivo_turma);
        return;
    }
    if (arquivo_aluno == NULL) {
        printf("Erro ao abrir o arquivo 'aluno.txt'.\n");
        fclose(arquivo_turma);
        fclose(arquivo_disciplina); 
        return;
    }

    
    fprintf(arquivo_turma, "Quantidade de turmas: %d\n", curso->quantidade_turmas);
    
    
    for (int i = 0; i < curso->quantidade_turmas; i++) {
        fprintf(arquivo_turma, "Turma %d:\n", curso->turmas[i].numero);
        fprintf(arquivo_disciplina, "Turma %d\n", curso->turmas[i].numero);
        
        for (int j = 0; j < curso->turmas[i].quantidade_disciplinas; j++) {
            fprintf(arquivo_disciplina, "Disciplina %d ", curso->turmas[i].disciplinas[j].codigo);
            fprintf(arquivo_disciplina, "Nome: %s ", curso->turmas[i].disciplinas[j].nome);
            fprintf(arquivo_disciplina, "Quantidade de alunos: %d\n", curso->turmas[i].disciplinas[j].quantidade_alunos);

            fprintf(arquivo_aluno, "Disciplina %d: \n", curso->turmas[i].disciplinas[j].codigo);
            
            for (int k = 0; k < curso->turmas[i].disciplinas[j].quantidade_alunos; k++) {
                fprintf(arquivo_aluno, "matricula %d: ", curso->turmas[i].disciplinas[j].alunos[k].matricula);
                fprintf(arquivo_aluno, "Nome: %s ", curso->turmas[i].disciplinas[j].alunos[k].nome);
                fprintf(arquivo_aluno, "Telefone: %s\n", curso->turmas[i].disciplinas[j].alunos[k].telefone);
            }
        }
    }

    fclose(arquivo_turma);
    fclose(arquivo_disciplina);
    fclose(arquivo_aluno);
}