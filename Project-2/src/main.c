#include "libs.h"
#include "path.h"
#include "flags.h"
#include "system.h"
#include "cpt.h"
#include "geo.h"
#include "svg.h"
#include "qry.h"

int main (int argc, char* argv[]) {
    path paths = create_general_paths();
    flag flags = create_flags();
    score score = create_points();
    CPTree tree = createCPT(0.000001);
        
    ReadParameters(argc, argv, paths, flags);

    ReadGeo(paths, tree, score);
    write_on_SVG(tree, paths);

    if (get_qry_inserted(flags))
        format_qry_results(paths, tree, score);
    
    free(score);
    free(flags);
    free_paths(paths);
    destroyCPT(tree);
}