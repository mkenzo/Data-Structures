#include "flags.h"

typedef struct flags {

    bool qry_inserted;
	bool bed_inserted;

} flags;

void* create_flags(){
    flags* new_flags = calloc(1, sizeof(flags));
    set_bed_inserted(new_flags, false);
    set_qry_inserted(new_flags, false);
	return new_flags;
}

bool get_qry_inserted(void* current_flags){
	flags* aux = current_flags;
	return aux->qry_inserted; 
}

void set_qry_inserted(void* current_flags, bool new_value){
	flags* aux = current_flags;
	aux->qry_inserted = new_value;
}

bool get_bed_inserted(void* current_flags){
	flags* aux = current_flags;
	return aux->bed_inserted; 
}

void set_bed_inserted(void* current_flags, bool new_value){
	flags* aux = current_flags;
	aux->bed_inserted = new_value;
}