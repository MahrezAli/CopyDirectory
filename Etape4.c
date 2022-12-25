#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>


void copy(char file_source[50], char file_dest[50]){
    int src, dest;
    char c;
    struct stat s_src;
        
    src = open(file_source, O_RDONLY);
    if(src == -1){
        printf("Le fichier source n'a pas pu être ouvert\n");
        printf("Il a pour nom : %s\n", file_source);
        exit(1);
    }
    fstat(src, &s_src);
    
    dest = open(file_dest, O_WRONLY);

    if(dest == -1){
        close(src);
        printf("Le fichier cible n'a pas pu être ouvert\n");
        printf("Il a pour nom : %s\n", file_dest);
        exit(1);
    }

    while(read(src, &c, sizeof(c)) > 0){
        write(dest, &c, sizeof(c));
    }
    fchmod(dest, s_src.st_mode); 

    close(src);
    close(dest);
}


void copyDir(char directory_source[50], char directory_dest[50]){
    DIR *dir_src, *dir_dest;
    struct dirent *files;
    char Dsrc[50];
    char Ddest[50];
        
    dir_src = opendir(directory_source);

    if(dir_src == NULL){
        printf("Le dossier source n'a pas pu être ouvert\n");
        exit(1);
    }
    strcpy(Dsrc, directory_source);

    dir_dest = opendir(directory_dest);

    if(dir_dest == NULL){
        closedir(dir_src);
        printf("Le dossier cible n'a pas pu être ouvert\n");
        exit(1);
    }
    strcpy(Ddest, directory_dest);

    while((files = readdir(dir_src)) != NULL){
        char tmp[50];
        strcpy(tmp, files->d_name);
        if (strcmp(files->d_name, ".") != 0 && strcmp(files->d_name, "..") != 0){
            strcpy(directory_source, Dsrc);
            strcpy(directory_dest, Ddest);
            //Il est possible de savoir s'il s'agit d'un dossier ou d'un fichier grâce à stat mais comme il n'est pas obligé de l'utilisé j'ai trouvé plus facile de voir si le type de files est directement un dossier.
            if(files->d_type == DT_DIR){ // Si c'est un fichier
                struct stat s_src;
                stat(directory_source, &s_src); // Copie les droits du dossier source
                mkdir(strcat(strcat(directory_dest, "/"),tmp), 0755 ); // Crée un nouveau dossier avec le nom du dossier source
                copyDir(strcat(strcat(directory_source, "/"),tmp), directory_dest); // Copie récursivement tous les élémént du dossier source dans ce dossier crée
                chmod(strcat(strcat(directory_dest, "/"),tmp), s_src.st_mode); // Lui donne les même droits que le dossier source.
            }
            else{ //Si c'est un fichier : Fait comme dans l'Etape 3
                creat(strcat(strcat(directory_dest, "/"),tmp), O_CREAT | O_WRONLY);
                chmod(directory_dest, 0777); 
                copy(strcat(strcat(directory_source, "/"),tmp),  directory_dest);
            }
        }
    }

    closedir(dir_src);
    closedir(dir_dest);
}



int main(){
    char directory_source[50], directory_dest[50];

    printf("Entrez le nom du répértoire à copier :\n");
    scanf("%[^\n]%*c", directory_source);
    
    printf("Entrez le nom du répértoire cible :\n");
    scanf("%[^\n]%*c", directory_dest);

    copyDir(directory_source, directory_dest);

    return 0;
}
























































































































































































































