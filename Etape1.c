#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void copy(char file_source[50], char file_dest[50]){
    int src, dest;
    char c;
    src = open(file_source, O_RDONLY);
    if(src == -1){ //On vérifie que le fichier source a bien pu s'ouvrir.
        printf("Le fichier source n'a pas pu être ouvert\n");
        exit(1);
    }
    
    dest = open(file_dest, O_WRONLY);
    
    if(dest == -1){ //On vérifie que le fichier cible a bien pu s'ouvrir.
        close(src);
        printf("Le fichier cible n'a pas pu être ouvert\n");
        exit(1);
    }
    //La boucle parcours tout le fichier source puis le recopie par caractère dans le fichier cible
    while(read(src, &c, sizeof(c)) > 0){ 
        write(dest, &c, sizeof(c));
    }

    close(src);
    close(dest);
}




int main(){
    char file_source[50], file_dest[50];

    //Entrez juste les noms des fichiers source et cible :
    printf("Entrez le nom du fichier source avec son extension :\n");
    scanf("%[^\n]%*c", file_source);
    
    printf("Entrez le nom du fichier cible et son extension :\n");
    scanf("%[^\n]%*c", file_dest);
    
    //Appel de la fonction copy en rajoutant l'extension .txt
    copy(file_source, file_dest);

    return 0;
}
























































































































































































































