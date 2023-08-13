#include "geo.h"
#include "system.h"
#include "cpt.h"
#include "circle.h"
#include "rectangle.h"
#include "line.h"
#include "text.h"
#include "figure.h"

void ReadGeo(path paths, CPTree b, score points){
    char corb[100], corp[100], cor[100], txto[100];
    char a;
    int i;
    double x, y, x1, x2, y1, y2, r, w , h;

    FILE* GeoFile = fopen(get_path_GeoFile(paths),"r");
    char command[20], type;

    while (fscanf(GeoFile, "%s", command) != EOF) {
        if (strcmp(command, "c") == 0) {
            type = 'c';
            fscanf(GeoFile, "%d %lf %lf %lf %s %s", &i, &x, &y, &r, corb, corp);
            void* new_circle = build_circle(i, x, y, r, corb, corp);
            void* new_figure = create_figure(type, new_circle);
            insertCPT(b, x, y, new_figure, NULL, NULL, NULL);
            addMaxPoints((75/((3.14*r*r)/5)), points);
        }

        if (strcmp(command, "r") == 0){
            type = 'r';
            fscanf(GeoFile, "%d %lf %lf %lf %lf %s %s", &i, &x, &y, &w, &h, corp, corb);
            void* new_rectangle = build_rectangle(i, x, y, w, h, corp, corb);
            void* new_figure = create_figure(type, new_rectangle);
            insertCPT(b, x, y, new_figure, NULL, NULL, NULL);
            addMaxPoints((90/((w*h)/5)), points);
        }

        if (strcmp(command, "l") == 0){
            type = 'l';
            fscanf(GeoFile, "%d %lf %lf %lf %lf %s", &i, &x1, &y1, &x2, &y2, cor);
            void* new_line = build_line(i, x1, y1, x2, y2, cor);
            void* new_figure = create_figure(type, new_line);
            insertCPT(b, x, y, new_figure, NULL, NULL, NULL);
            addMaxPoints(150, points);
        }
        
        if (strcmp(command, "t") == 0){
            type = 't';
            fscanf(GeoFile, "%d %lf %lf %s %s %c %[^\n]", &i, &x, &y, corb, corp, &a, txto);
            void* new_text = build_text(i, x, y, corb, corp, a, txto);
            void* new_figure = create_figure(type, new_text);
            insertCPT(b, x, y, new_figure, NULL, NULL, NULL);
            addMaxPoints(500, points);
        }
    }
    
    fclose(GeoFile);
}