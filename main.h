#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct aluno {
    int matricula;
    char* nome;
    char telefone[12];
};
typedef struct aluno t_aluno;

struct disciplina {
    int codigo;
    char* nome;
    t_aluno* alunos;
    int quantidade_alunos;
};
typedef struct disciplina t_disciplina;

struct turma {
    int numero;
    t_disciplina* disciplinas;
    int quantidade_disciplinas;
};
typedef struct turma t_turma;

struct curso {
    t_turma* turmas;
    int quantidade_turmas;
};
typedef struct curso t_curso;

void inicializar(t_curso* curso);
void exibir_menu(void);
int obter_opcao_menu(void);
void processar_opcao_menu(int opcao, t_curso* curso);

void inserir_turma(t_curso* curso);
void inserir_disciplina(t_turma* turma);  
void inserir_aluno(t_disciplina* disciplina);
void remover_turma(t_curso* curso); 
void remover_disciplina(t_turma* turma);  
void remover_aluno(t_disciplina* disciplina);  
void listar_turmas(t_curso* curso);
void listar_disciplinas(t_turma* turma);
void listar_alunos(t_disciplina* disciplina);
t_turma* obter_turma(t_curso* curso);
t_disciplina* obter_disciplina(t_turma* turma);
t_aluno* obter_aluno(t_disciplina* disciplina);
void liberar_memoria_curso(t_curso* curso);
void liberar_memoria_turma(t_turma* turma);
void liberar_memoria_disciplina(t_disciplina* disciplina);
void liberar_memoria_aluno(t_aluno* aluno);
int existe_turma(t_curso* curso, int numero);
int existe_disciplina(t_turma* turma, int codigo);
int existe_aluno(t_disciplina* disciplina, int matricula);

void obter_texto(char** texto);
void escrever_arquivo(t_curso *curso);

void ler_arquivo_turma(const char *nome_arquivo, t_curso *curso);
void ler_arquivo_disciplina(const char *nome_arquivo, t_curso *curso);
void ler_arquivo_aluno(const char *nome_arquivo, t_curso *curso);