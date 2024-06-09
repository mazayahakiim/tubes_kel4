#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h> 

const int MAX_LENGTH = 100; 

typedef struct node{
  char *judul;
  char *artist;
  struct node *nextNode;
} Node;

void inputString(const char *prompt, char *arr, int arrsize);
void insert_song(Node **head, const char *judul, const char *artist);
void print_playlist(Node *head);
void searchByJudul(Node *head, const char *judul);
void removeLagu(Node **head, const char *judul);
//void deletePlaylist();
//void quit_program();
//sortingLaguByArtis atau by apa terserah

int main(){
  struct node *head = NULL;
  char *judul_lagu, *penyanyi;

  penyanyi = (char *)malloc(MAX_LENGTH * sizeof(char));
  judul_lagu = (char *)malloc(MAX_LENGTH * sizeof(char));

  printf("\n----------------------------------------------------------------------\n");
  printf("                          PLAYLIST KELOMPOK 4\n");
  printf("----------------------------------------------------------------------\n");
  printf("                           Pilih perintah:\n");
  printf("                            I (insert)\n");
  printf("                            P (show playlist)\n");
  printf("                            S (search by judul)\n");
  printf("                            R (remove lagu)\n");
  // printf("                            Q (quit program)");
  /*dan lain-lain*/
  printf("\n----------------------------------------------------------------------\n");


  char response;
  char input[MAX_LENGTH+1];

  do{
    inputString("\nPerintah", input, MAX_LENGTH );
    response = toupper(input[0]);

    if(response == 'I'){
      inputString("Judul Lagu", judul_lagu, MAX_LENGTH);
      inputString("Penyanyi", penyanyi, MAX_LENGTH);
      insert_song(&head, judul_lagu, penyanyi);
      //nanti tambahin lg sisanya yg belum//

    }else if(response=='P'){
      print_playlist(head);
    }else if(response == 'S'){
        inputString("Masukkan judul lagu untuk dicari: ", judul_lagu, MAX_LENGTH);
        searchByJudul(head, judul_lagu);
    }else if(response == 'R'){
        inputString("Masukkan judul lagu yang ingin dihapus", judul_lagu, MAX_LENGTH);
        removeLagu(&head, judul_lagu);
    }else{
      printf("Perintah tidak ditemukan.. Silahkan coba lagi.\n");
    }
  }while (response != 'Q'); /*Q itu fungsi quit dari program*/

  return 0;
}


void inputString(const char *prompt, char *arr, int arrsize){
  int i = 0;
  char c;

  printf("%s --> ", prompt);

  while ( i < arrsize && ( c = getchar())!= '\n'){
      arr[i++] = c;
  }
  arr[i]='\0';
    
}

void insert_song(Node **head, const char *judul, const char *artist){ /*fungsi add lagu ke playlist*/
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->judul = strdup(judul);
  new_node->artist = strdup(artist);
  new_node->nextNode = NULL;

  if(*head == NULL || strcmp((*head)->judul, judul) > 0){
    new_node->nextNode = *head;
    *head = new_node;
  }else{
    Node *current = *head;
    while(current->nextNode != NULL && strcmp(current->nextNode->judul, judul) < 0){
      current = current->nextNode;
    }
    new_node->nextNode = current->nextNode;
    current->nextNode = new_node;
  }
}


void print_playlist(Node *head){  /*fungsi cetak playlist*/
  Node *current = head;

  if(current != NULL){
    printf("\n----------------------------------------------------------------------\n");
    printf("                          PLAYLIST KELOMPOK\n");
    printf("----------------------------------------------------------------------\n");
    printf(" Judul                                            | Penyanyi\n");
    printf("----------------------------------------------------------------------\n");
    while (current != NULL){
      printf(" %-48s | %s\n", current->judul, current->artist);
      current = current -> nextNode;
    }
    printf("----------------------------------------------------------------------");
  }else{
    printf("\nPlaylist kosong.\n");
  }
}

void searchByJudul(Node *head, const char *judul){  /*fungsi cari lagu berdasarkan judul*/
  Node *current = head;
  int found = 0;

  while(current != NULL){
    if(strcmp(current->judul, judul) == 0){
      printf("\nLagu ditemukan:\n");
      printf("Judul: %s\n", current->judul);
      printf("Penyanyi: %s\n", current->artist);
      found = 1;
      break;
    }
    current = current->nextNode;
  }

  if(!found){
    printf("\nLagu dengan judul '%s' tidak ditemukan.\n", judul);
  }
}  

void removeLagu(Node **head, const char *judul) {   /*fungsi hapus lagu*/
  Node *current = *head;
  Node *previous = NULL;

  while (current != NULL && strcmp(current->judul, judul) != 0) {
    previous = current;
    current = current->nextNode;
  }

  if (current == NULL) {
    printf("\nLagu dengan judul '%s' tidak ditemukan.\n", judul);
    return;
  }

  if (previous == NULL) {
    *head = current->nextNode;
  } else {
    previous->nextNode = current->nextNode;
  }

  free(current->judul);
  free(current->artist);
  free(current);
  printf("\nLagu dengan judul '%s' berhasil dihapus.\n", judul);
}


