#include "libs.h"

#ifndef System_h_ADD
#define System_h_ADD

/*
    Este modulo prove funcoes para leitura dos parâmetros informados.
    Basicamente, exitem 2 tipos de funcoes:
        - Leitura de parametros.
        - Retornam o path ou nome do arquivo inserido.
*/

/** Recebe os parâmetros inseridos no argc argv e processa salvando os seus caminhos e nomes */
void ReadParameters(int argc, char* argv[], path paths, flag flags);

/** Retorna uma struct vazia, com uma lista de paths e nomes de arquivos. */
path create_general_paths();

/** Retorna o caminho do diretório base de entrada. */
char *get_BED(path paths);

/** Retorna o caminho do diretório base de saida. */
char *get_BSD(path paths);

/** Retorna o nome do .geo (sem diretório). */
char *get_GeoFile(path paths);

/** Retorna o nome do .qry (sem diretório). */
char *get_QryFile(path paths);

/** Retorna o nome do .geo sem o .geo. */
char *get_GeoName(path paths);

/** Retorna o nome do .qry sem o .qry. */
char *get_QryName(path paths);

/** Retorna o nome do .geo sem o .geo. */
char *get_final_SVGName(path paths);

/** Retorna o caminho do .geo. */
char *get_path_GeoFile(path paths);

/** Retorna o caminho do .qry. */
char *get_path_QryFile(path paths);

/** Retorna o caminho do .svg. */
char *get_path_SVG(path paths);

/** Retorna o caminho do .svg modificado. */
char *get_path_modifiedSVG(path paths);

/** Retorna o caminho do .txt do qry. */
char *get_path_TXTQry(path paths);

/** Da free em todos os paths. */
void free_paths(path paths);

score create_points();
void addMaxPoints (double p, score point);
void addPoints (double p, score point);
void addAgress (score point);
double get_total_points(score point);
double get_obtained_points(score point);
double get_agress(score point);

#endif