#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void view(const char *filename) 
{
    FILE *fp = fopen(filename, "rb");   
    if (!fp) 
    { 
        printf("Error: Cannot open file.\n");
        return; 
    }
    fseek(fp, -128, SEEK_END);
    char tag[3], title[30], artist[30], album[30], year[4], comment[30];
    unsigned char genre;
    fread(tag, 1, 3, fp);
    fread(title, 1, 30, fp);
    fread(artist, 1, 30, fp);
    fread(album, 1, 30, fp);
    fread(year, 1, 4, fp);
    fread(comment, 1, 30, fp);
    fread(&genre, 1, 1, fp);
    fclose(fp);
    if (memcmp(tag, "TAG", 3) != 0) 
    {
        printf("No ID3v1 tag found in file.\n");
        return;
    }
    unsigned char rev[4];
    rev[0] = year[3];
    rev[1] = year[2];
    rev[2] = year[1];
    rev[3] = year[0];
    unsigned int be_year = (rev[0] << 24) | (rev[1] << 16) | (rev[2] << 8) | rev[3];
    printf("----- MP3 TAG INFO -----\n");
    printf("Title   : %.30s\n", title);
    printf("Artist  : %.30s\n", artist);
    printf("Album   : %.30s\n", album);
    printf("Year    : %.4s (Endian -> %u)\n", year, be_year);
    printf("Comment : %.30s\n", comment);
    printf("Genre   : %d\n", genre);
}
void edit(const char *filename, const char *field, const char *value) 
{
    FILE *fp = fopen(filename, "r+b");  
    if (!fp) 
    { 
        printf("Error: Cannot open file.\n");
        return; 
    }
    fseek(fp, -128, SEEK_END);
    char tag[3], title[30], artist[30], album[30], year[4], comment[30];
    unsigned char genre;
    fread(tag, 1, 3, fp);
    fread(title, 1, 30, fp);
    fread(artist, 1, 30, fp);
    fread(album, 1, 30, fp);
    fread(year, 1, 4, fp);
    fread(comment, 1, 30, fp);
    fread(&genre, 1, 1, fp);
    if (memcmp(tag, "TAG", 3) != 0) 
    {
        printf("No ID3v1 tag found.\n");
        fclose(fp);
        return;
    }
    if (strcmp(field, "title") == 0) 
    {
        strncpy(title, value, 30);
    } 
    else if (strcmp(field, "artist") == 0) 
    {
        strncpy(artist, value, 30);
    } 
    else if (strcmp(field, "album") == 0) 
    {
        strncpy(album, value, 30);
    } 
    else if (strcmp(field, "year") == 0) 
    {
        strncpy(year, value, 4);
    } 
    else if (strcmp(field, "comment") == 0) 
    {
        strncpy(comment, value, 30);
    } 
    else if (strcmp(field, "genre") == 0) 
    {
        genre = (unsigned char)atoi(value);
    } 
    else 
    {
        printf("Field not supported.\n");
        fclose(fp);
        return;
    }
    fseek(fp, -128, SEEK_END);
    fwrite(tag, 1, 3, fp);
    fwrite(title, 1, 30, fp);
    fwrite(artist, 1, 30, fp);
    fwrite(album, 1, 30, fp);
    fwrite(year, 1, 4, fp);
    fwrite(comment, 1, 30, fp);
    fwrite(&genre, 1, 1, fp);
    fclose(fp);
    printf("Field '%s' updated.\n", field);
}