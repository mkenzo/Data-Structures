#include "system.h"
#include "path.h"
#include "flags.h"

typedef struct points {
    double total_points;
    double obtained_points;
    double agress;
} points;

typedef struct general_paths
{
    char *BED;
    char *BSD;
    char *GeoFile;
    char *QryFile;
    char *QryName;
    char *GeoName;
    char *final_SVGName;
    char *path_GeoFile;
    char *path_QryFile;
    char *path_SVG;
    char *path_modifiedSVG;
    char *path_TXTQry;

} general_paths;

score create_points() {
    points *aux = calloc(1, sizeof(points));

    aux->total_points = 0;
    aux->obtained_points = 0;
    aux->agress = 0;

    return aux;
}

void addMaxPoints (double p, score point) {
    points *aux = point;
    aux->total_points = aux->total_points + p;
}

void addPoints (double p, score point) {
    points *aux = point;
    aux->obtained_points = aux->obtained_points + p;
}

void addAgress (score point) {
    points *aux = point;
    aux->agress = aux->agress + 1;
}

double get_total_points(score point) {
    points *aux = point;
    return aux->total_points;
}

double get_obtained_points(score point) {
    points *aux = point;
    return aux->obtained_points;
}

double get_agress(score point) {
    points *aux = point;
    return aux->agress;
}

void set_BED(path paths, char *newSet) {
    general_paths *aux = paths;
    aux->BED = newSet;
}

void set_BSD(path paths, char *newSet) {
    general_paths *aux = paths;
    aux->BSD = newSet;
}

void set_GeoFile(path paths, char *newSet) {
    general_paths *aux = paths;
    aux->GeoFile = newSet;
}

void set_QryFile(path paths, char *newSet) {
    general_paths *aux = paths;
    aux->QryFile = newSet;
}

void set_GeoName(path paths, char *newSet) {
    general_paths *aux = paths;
    aux->GeoName = newSet;
}

void set_QryName(path paths, char *newSet) {
    general_paths *aux = paths;
    aux->QryName = newSet;
}

void set_final_SVGName(path paths, char *newSet) {
    general_paths *aux = paths;
    aux->final_SVGName = newSet;
}

void set_path_GeoFile(path paths, char *newSet) {
    general_paths *aux = paths;
    aux->path_GeoFile = newSet;
}

void set_path_QryFile(path paths, char *newSet) {
    general_paths *aux = paths;
    aux->path_QryFile = newSet;
}

void set_path_SVG(path paths, char *newSet) {
    general_paths *aux = paths;
    aux->path_SVG = newSet;
}

void set_path_modifiedSVG(path paths, char *newSet) {
    general_paths *aux = paths;
    aux->path_modifiedSVG = newSet;
}

void set_path_TXTQry(path paths, char *newSet) {
    general_paths *aux = paths;
    aux->path_TXTQry = newSet;
}

void CheckArgs(path paths) {
    char* GeoFile = get_GeoFile(paths);
    char* BSD = get_BSD(paths);
    if(GeoFile == NULL || BSD == NULL){
        printf("\nERROR\nArgumento essencial nao inserido!\n");
        exit(1);
    }
}

void ReadParameters(int argc, char* argv[], path paths, flag flags){

    for(int i = 0; i < argc; i++){
        if(strcmp("-e", argv[i]) == 0){
            char* input_base_directory = calloc(strlen(argv[i+1]) + 1, sizeof(char));
            strcpy(input_base_directory, argv[i+1]);

            if(input_base_directory[strlen(input_base_directory)-1] == '/'){
                normalizePath(argv[i+1], input_base_directory, strlen(argv[i+1]));
            }

            if(argv[i+1] == NULL || input_base_directory[0] == '-'){
                printf("ERROR - Sem parametros em -e\n");
                exit(1);
            }

            set_BED(paths, input_base_directory);
            set_bed_inserted(flags, true);
        }

        else if(strcmp("-f", argv[i]) == 0){
            char* geo_file = calloc(strlen(argv[i+1]) + 1, sizeof(char));
            char* geo_name = calloc(strlen(argv[i+1]) + 1, sizeof(char));
            strcpy(geo_file, argv[i+1]);

            if(argv[i+1] == NULL || geo_file[0] == '-'){
                printf("ERROR - Sem parametros em -f\n");
                exit(1);
            }

            set_GeoFile(paths, geo_file);
            getFileName(geo_file, geo_name, strlen(geo_file));
            for (int i = 0; geo_name[i]; i++) {
                if (geo_name[i] == '.') {
                    geo_name[i] = '\0';
                    break;
                }
            }
            set_GeoName(paths, geo_name);
        }

        else if(strcmp("-o", argv[i]) == 0){
            char* output_base_directory = calloc(strlen(argv[i+1]) + 4, sizeof(char));
            strcpy(output_base_directory, argv[i+1]);

            if(output_base_directory[strlen(output_base_directory)-1] == '/'){
                normalizePath(argv[i+1], output_base_directory, strlen(argv[i+1]));
            }

            if(argv[i+1] == NULL || output_base_directory[0] == '-'){
                printf("ERROR - Sem parametros em -o\n");
                exit(1);
            }
            set_BSD(paths, output_base_directory);
        }

        else if(strcmp("-q", argv[i]) == 0){
            char* qry_file = calloc(strlen(argv[i+1]) + 1, sizeof(char));
            char* qry_name = calloc(strlen(argv[i+1]) + 1, sizeof(char));
            strcpy(qry_file, argv[i+1]);

            if(argv[i+1] == NULL || qry_file[0] == '-'){
                printf("ERROR - Sem parametros em -q\n");
                exit(1);
            }

            set_QryFile(paths, qry_file);
            getFileName(qry_file, qry_name, strlen(qry_file));
            for (int i = 0; qry_name[i]; i++) {
                if (qry_name[i] == '.') {
                    qry_name[i] = '\0';
                    break;
                }
            }
            set_QryName(paths, qry_name);
            set_qry_inserted(flags, true);
        }
    }

    CheckArgs(paths);

    char* path_SVG = calloc(strlen(get_BSD(paths)) + strlen(get_GeoName(paths)) + 10, sizeof(char));
    joinAll(get_BSD(paths), get_GeoName(paths), ".svg", path_SVG, strlen(path_SVG));
    set_path_SVG(paths, path_SVG);

    if (get_bed_inserted(flags)){
        char* path_GeoFile = calloc(strlen(get_BED(paths)) + strlen(get_GeoFile(paths)) + 4, sizeof(char));
        joinFilePath(get_BED(paths), get_GeoFile(paths), path_GeoFile, strlen(path_GeoFile));
        set_path_GeoFile(paths, path_GeoFile);
    }
    else{
        char* BED = calloc(3, sizeof(char));
        strcpy(BED, "./");
        set_BED(paths, BED);

        char* path_GeoFile = calloc(strlen(get_BED(paths)) + strlen(get_GeoFile(paths)) + 2, sizeof(char));
        joinFilePath(get_BED(paths), get_GeoFile(paths), path_GeoFile, strlen(path_GeoFile));
        set_path_GeoFile(paths, path_GeoFile);
    }

    if (get_qry_inserted(flags)){
        char* path_QryFile = calloc(strlen(get_BED(paths)) + strlen(get_QryFile(paths)) + 10, sizeof(char));
        joinFilePath(get_BED(paths), get_QryFile(paths), path_QryFile, strlen(path_QryFile));
        set_path_QryFile(paths, path_QryFile);

        char* path_TXTQry = calloc(strlen(get_BSD(paths)) + strlen(get_GeoName(paths)) + strlen(get_QryName(paths)) + 10, sizeof(char));
        char* path_modifiedSVG = calloc(strlen(get_BSD(paths)) + strlen(get_GeoName(paths)) + strlen(get_QryName(paths)) + 10, sizeof(char));
        sprintf(path_TXTQry, "%s%s-%s.txt", get_BSD(paths), get_GeoName(paths), get_QryName(paths));
        set_path_TXTQry(paths, path_TXTQry);
        sprintf(path_modifiedSVG, "%s%s-%s.svg", get_BSD(paths), get_GeoName(paths), get_QryName(paths));
        set_path_modifiedSVG(paths, path_modifiedSVG);
    }
}

path create_general_paths() {
    general_paths *aux = calloc(1, sizeof(general_paths));
    return aux;
}

char *get_BED(path paths) {
    general_paths *aux = paths;
    return aux->BED;
}

char *get_BSD(path paths) {
    general_paths *aux = paths;
    return aux->BSD;
}

char *get_GeoFile(path paths) {
    general_paths *aux = paths;
    return aux->GeoFile;
}

char *get_QryFile(path paths) {
    general_paths *aux = paths;
    return aux->QryFile;
}

char *get_GeoName(path paths) {
    general_paths *aux = paths;
    return aux->GeoName;
}

char *get_QryName(path paths) {
    general_paths *aux = paths;
    return aux->QryName;
}

char *get_final_SVGName(path paths) {
    general_paths *aux = paths;
    return aux->final_SVGName;
}

char *get_path_GeoFile(path paths) {
    general_paths *aux = paths;
    return aux->path_GeoFile;
}

char *get_path_QryFile(path paths) {
    general_paths *aux = paths;
    return aux->path_QryFile;
}

char *get_path_SVG(path paths) {
    general_paths *aux = paths;
    return aux->path_SVG;
}

char *get_path_modifiedSVG(path paths) {
    general_paths *aux = paths;
    return aux->path_modifiedSVG;
}

char *get_path_TXTQry(path paths) {
    general_paths *aux = paths;
    return aux->path_TXTQry;
}

void free_paths(path paths) {
    general_paths *aux = paths;
    if (aux->BED) 
        free(aux->BED);
    if (aux->BSD)
        free(aux->BSD);
    if (aux->GeoFile)
        free(aux->GeoFile);
    if (aux->QryFile)
        free(aux->QryFile);
    if (aux->final_SVGName)
        free(aux->final_SVGName);
    if (aux->GeoName)
        free(aux->GeoName);
    if (aux->QryName)
        free(aux->QryName);
    if (aux->path_GeoFile)
        free(aux->path_GeoFile);
    if (aux->path_QryFile)
        free(aux->path_QryFile);
    if (aux->path_modifiedSVG)
        free(aux->path_modifiedSVG);
    if (aux->path_SVG)
        free(aux->path_SVG);
    if (aux->path_TXTQry)
        free(aux->path_TXTQry);
    free(paths);
}

void show_paths(path paths) {
    general_paths *aux = paths;
    if (aux->BED)
    {
        puts("BED :");
        puts(aux->BED);
        puts("====================");
    }
    if (aux->BSD)
    {
        puts("BSD : ");
        puts(aux->BSD);
        puts("====================");
    }
    if (aux->GeoFile)
    {
        puts("Geo Inicial : ");
        puts(aux->GeoFile);
        puts("====================");
    }
    if (aux->QryFile)
    {
        puts("Qry Consultas : ");
        puts(aux->QryFile);
        puts("====================");
    }
    if (aux->final_SVGName)
    {
        puts("Nome Arquivp SVG Final : ");
        puts(aux->final_SVGName);
        puts("====================");
    }
    if (aux->GeoName)
    {
        puts("Nome GEO : ");
        puts(aux->GeoName);
        puts("====================");
    }
    if (aux->QryName)
    {
        puts("Nome QRY : ");
        puts(aux->QryName);
        puts("====================");
    }
    if (aux->path_GeoFile)
    {
        puts("Path Arquivo Geo Inicial : ");
        puts(aux->path_GeoFile);
        puts("====================");
    }

    if (aux->path_QryFile)
    {
        puts("Path Arquivo Qry Atual : ");
        puts(aux->path_QryFile);
        puts("====================");
    }
    if (aux->path_modifiedSVG)
    {
        puts("PathDoSvgComOQryExecutado : ");
        puts(aux->path_modifiedSVG);
        puts("====================");
    }
    if (aux->path_SVG)
    {
        puts("Path Do Svg Do Geo Sem Mudanca : ");
        puts(aux->path_SVG);
        puts("====================");
    }
    if (aux->path_TXTQry)
    {
        puts("Path Do TXT Com O Qry Executado : ");
        puts(aux->path_TXTQry);
        puts("====================");
    }
}