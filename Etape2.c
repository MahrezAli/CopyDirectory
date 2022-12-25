#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>


void copy(char file_source[50], char file_dest[50]){
    int src, dest;
    char c;
    struct stat s_src;
        
    src = open(file_source, O_RDONLY);
    
    if(src == -1){
        printf("Le fichier source n'a pas pu être ouvert\n");
        exit(1);
    }
    fstat(src, &s_src); //Elle stocke les permissions du fichier src dans s_src
    
    dest = open(file_dest, O_WRONLY);
    
    if(dest == -1){
        close(src);
        printf("Le fichier cible n'a pas pu être ouvert\n");
        exit(1);
    }

    while(read(src, &c, sizeof(c)) > 0){
        write(dest, &c, sizeof(c));
    }
    //Après avoir fini de copier le contenu du fichier, la fonction chmod retranscrit les permissions de src dans dest.
    fchmod(dest, s_src.st_mode); 

    close(src);
    close(dest);
}




int main(){
    char file_source[50], file_dest[50];

    printf("Entrez le nom du fichier source avec son extension :\n");
    scanf("%[^\n]%*c", file_source);
    
    printf("Entrez le nom du fichier cible et son extension :\n");
    scanf("%[^\n]%*c", file_dest);
    
    
    copy(file_source, file_dest);

    return 0;
}
























































































































































































































