#include "libs.h"
#include "path.h"
#include "flags.h"
#include "system.h"
#include "lista.h"
#include "geo.h"
#include "svg.h"
#include "qry.h"

int main (int argc, char* argv[]) {
    path paths = create_general_paths();
    flag flags = create_flags();
    list list = createLista(-1);
    score score = create_points();
        
    ReadParameters(argc, argv, paths, flags);

    ReadGeo(paths, list, score);
    write_on_SVG(list, paths);

    if (get_qry_inserted(flags))
        format_qry_results(paths, list, score);
    
    killLista(list);
    free(score);
    free(flags);
    free_paths(paths);
}