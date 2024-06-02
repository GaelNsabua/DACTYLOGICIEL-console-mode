#include <stdio.h>

FILE *f = NULL;

void create_word_db(){
    f = fopen("word-db.xls", "w");
}

void write_into_word_db(){
    int n;
for (n=0 ; n<3 ; n++)
   {
     fprintf (f, "Name\n");
   }
   fclose (f);

}
