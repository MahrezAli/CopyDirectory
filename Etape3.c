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
        exit(1);
    }
    fstat(src, &s_src);
    
    dest = open(file_dest, O_WRONLY);

    if(dest == -1){
        close(src);
        printf("Le fichier cible n'a pas pu être ouvert\n");
        exit(1);
    }

    while(read(src, &c, sizeof(c)) > 0){
        write(dest, &c, sizeof(c));
    }
    fchmod(dest, s_src.st_mode); 

    close(src);
    close(dest);
}





int main(){
    char directory_source[50], directory_dest[50];
    DIR *dir_src, *dir_dest;
    struct dirent *files;
    char Dsrc[50];
    char Ddest[50];
    
    printf("Entrez le nom du répértoire à copier :\n");
    scanf("%[^\n]%*c", directory_source);
    
    dir_src = opendir(directory_source);

    if(dir_src == NULL){
        printf("Le dossier source n'a pas pu être ouvert\n");
        exit(1);
    }
    strcpy(Dsrc, directory_source);
    printf("Entrez le nom du répértoire cible :\n");
    scanf("%[^\n]%*c", directory_dest);

    dir_dest = opendir(directory_dest);

    if(dir_dest == NULL){
        closedir(dir_src);
        printf("Le dossier cible n'a pas pu être ouvert\n");
        exit(1);
    }
    strcpy(Ddest, directory_dest);
    while((files = readdir(dir_src)) != NULL){
        //copier les fichiers:
        //1- creer un fichier vide dans le dossier dest
        //2- copier mon files dans le fichier crée
        char tmp[50];
        strcpy(tmp, files->d_name);
        if (strcmp(files->d_name, ".") != 0 && strcmp(files->d_name, "..") != 0){
            //J'ai remarqué qu'à chaque fois qu'un nouveau fichier est parcouru, il est rajouté dans le PATH (exemple : dossier/nom1.txt/nom2.txt)
            //Alors à chaque itération je renomme mon PATH initial pour qu'il puisse accéder au bon fichier.
            strcpy(directory_source, Dsrc);
            strcpy(directory_dest, Ddest);
            //Crée un nouveau fichier dans le dossier cible avec le meme nom que fichier qui sera copié
            creat(strcat(strcat(directory_dest, "/"),tmp), O_CREAT | O_WRONLY);
            //Donne au fichier crée tous les droit pour qu'il puisse être recopié (Dans tous les cas copy() copie aussi les droits)
            chmod(directory_dest, 0777); 
            copy(strcat(strcat(directory_source, "/"),tmp),  directory_dest);
        }
    }

    closedir(dir_src);
    closedir(dir_dest);

    return 0;
}
























































































































































































































