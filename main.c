#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void view(const char *filename);
void edit(const char *filename, const char *field, const char *value);
int main(int argc, char *argv[])
{
    if (argc < 2) 
    {
        printf("Usage:\n");
        printf("  %s -v <filename>\n", argv[0]);
        printf("  %s -e <field> <value> <filename>\n", argv[0]);
        return 1;
    }
    if (strcmp(argv[1], "-v") == 0) 
    {
        if (argc != 3) 
        {
            printf("Usage: %s -v <filename>\n", argv[0]);
            return 1;
        }
        view(argv[2]); 
    } 
    else if (strcmp(argv[1], "-e") == 0) 
    {
        if (argc != 5) 
        {
            printf("Usage: %s -e <field> <value> <filename>\n", argv[0]);
            return 1;
        }
        const char *field    = argv[2];
        const char *newValue = argv[3];
        const char *filename = argv[4];
        edit(filename, field, newValue); 
    } 
    else 
    {
        printf("Unknown command: %s\n", argv[1]);
        printf("Use -v to view or -e to edit.\n");
        return 1;
    }
    return 0;
}
