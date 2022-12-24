#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>
#include <assert.h>
#include <stdlib.h>
#include "hash.h"

#define DB_NAME_LENGTH 255
#define IDX_LENGTH DB_NAME_LENGTH + 4
#define DT_LENGTH DB_NAME_LENGTH + 3
#define DATABASE "access"
#define NUMSLOT 104729
#define TRUE 1
#define FALSE 0

static char dt_str[DT_LENGTH];
static char idx_str[IDX_LENGTH];

typedef struct {
  char *key;
  long size;
} db_key;

typedef struct {
  char *data;
  long size;
} db_data;

typedef struct DB {
    int (*db_open)(const char *,struct DB *,FILE *,FILE *);
    int (*db_put)(struct DB *,db_key *,db_data *);
    char *(*db_get)(struct DB *,db_key *);
    FILE *dt;
    FILE *idx;
    char name[DB_NAME_LENGTH];
} DB;

MapPtr EntryCache;
FILE *fdt,*fidx;
DB *dbt;

int file_exist (char *filename)
{
  struct stat   buffer;
  return (stat (filename, &buffer) == 0);
}

char *get_key(struct DB *dbt,db_key *key) {

    FILE *fdp=dbt->dt;
    FILE *fip=dbt->idx;
    long int pos;
    int errnum;

    if (!fip) {
            perror("Accessing index file");
            return NULL;
    }

    if (!fdp) {
            perror("Accessing data file");
            return NULL;
    }

    char *s=getEntry(EntryCache,key->key);
    // Found in cache!
        if (s) {
                return s;
        }

    return NULL;


}


int put_key(DB *dbt,db_key *key,db_data *data) {


    FILE *fdp=dbt->dt;
    FILE *fip=dbt->idx;
    long curr_pos;
    size_t ret=0;


    memset(idx_str,0,IDX_LENGTH);
    strcpy(idx_str,DATABASE);
    char *ix_str=strcat(idx_str,".idx");


    if (file_exist(ix_str)) {

       char *s=getEntry(EntryCache,key->key);
       // Found in cache!
       if (s) {
                printf("%s\n","Key already in db");
                return 0;
        }

    }

    fseek(fdp,0L,SEEK_END);
    fseek(fip,0L,SEEK_END);

    //Write key size to index file

    if (ret=fwrite(&(key->size),sizeof(long),1,fip)<1) {
            perror("Writing long to index file");
            return -1;
    }

    //Write key to index file

    if (ret=fwrite(key->key,sizeof(char),key->size,fip)<key->size) {
            perror("Writing string to index file");
            return -1;
    }

    //Write data offset to index file

    curr_pos=ftell(fdp);
    if (ret=fwrite(&curr_pos,sizeof(long),1,fip)<1) {
            perror("Writing second long to index file");
            return -1;
    }


    //Write data size to data file

    if (ret=fwrite(&(data->size),sizeof(long),1,fdp)<1) {
            perror("Writing long to data file");
            return -1;
    }

    //Write data to data file

    if(ret=fwrite(data->data,sizeof(char),data->size,fdp)<data->size) {
            perror("Writing string to data file");
            return -1;
    }

    fflush(fip);
    fflush(fdp);

    return 0;

}


int load_index(DB *dbt,FILE *idx,FILE *fd) {


    db_key key_buff;
    db_data data_buff;
    long key_size;
    long data_pos;
    long data_size;
    long ret;


while (TRUE) {

     char ch=fgetc(idx);
     if (ch==EOF)
       break;
     else
       ungetc(ch,idx);


      if (ret=fread(&key_size,sizeof(long),1,idx)<1) {
          perror("Reading key size from index file");
          return -1;
      }

        key_buff.key=(char *)malloc(key_size);

      if (ret=fread(key_buff.key,sizeof(char),key_size,idx)<key_size) {
          perror("Reading key from index file");
          free(key_buff.key);
          return -1;
      }



      if (ret=fread(&data_pos,sizeof(long),1,idx)<1) {
          perror("Reading data pos from index file");
          free(key_buff.key);
          return -1;
      }


        fseek(fd,data_pos,SEEK_SET);

      if (ret=fread(&data_size,sizeof(long),1,fd)<1) {
          perror("Reading data size from data file");
          free(key_buff.key);
          return -1;
      }


        data_buff.data=(char *)malloc(data_size);


      if (ret=fread(data_buff.data,sizeof(char),data_size,fd)<data_size) {
          perror("Reading data from datafile");
          free(key_buff.key);
          free(data_buff.data);
          return -1;
      }


         putEntry(EntryCache,key_buff.key,data_buff.data);

         free(key_buff.key);
         free(data_buff.data);

   }


    return 0;

}

int open_db(const char *str,DB *dbt,FILE *idx,FILE *fd) {


    memset(dt_str,0,DT_LENGTH);
    memset(idx_str,0,IDX_LENGTH);
    strcpy(dt_str,DATABASE);
    strcpy(idx_str,DATABASE);

    char *db_str=strcat(dt_str,".db");
    char *ix_str=strcat(idx_str,".idx");

    fd = fopen(db_str,"rb+");
    if (!fd) {
            perror("Opening data file");
            free(dbt);
            return -1;
    }

    idx = fopen(ix_str,"rb+");
    if (!idx) {
            perror("Opening  index file");
            free(dbt);
            return -1;
    }

   printf("%s\n","Loading index ...");
   load_index(dbt,idx,fd);

}




int create_db(const char *str,DB **dbt) {

    int errnum;
    *dbt = (DB *)malloc(sizeof(DB));

    if (!*dbt) {
            perror("Allocating memory for db");
            return -1;
    }

    memset(dt_str,0,DT_LENGTH);
    memset(idx_str,0,IDX_LENGTH);
    strcpy(dt_str,DATABASE);
    strcpy(idx_str,DATABASE);

    char *db_str=strcat(dt_str,".db");
    char *ix_str=strcat(idx_str,".idx");

    fdt = fopen(db_str,"ab+");
    if (!fdt) {
            perror("Opening data file");
            free(dbt);
            return -1;
    }

    fidx = fopen(ix_str,"ab+");
    if (!fidx) {
            perror("Opening  index file");
            free(dbt);
            return -1;
    }

    (*dbt)->dt = fdt;
    (*dbt)->idx = fidx;
    (*dbt)->db_open=&open_db;
    (*dbt)->db_put=&put_key;
    (*dbt)->db_get=&get_key;

    strcpy((*dbt)->name,str);

    printf("%s\n","Loading index ...");
    load_index(*dbt,(*dbt)->idx,(*dbt)->dt);

    return 0;

}

int destroy_db(DB **dbt) {

     fclose((*dbt)->dt);
     fclose((*dbt)->idx);
     free(*dbt);

     return 0;

}

int main(int argc, char *argv[])
{

      static db_key key;
      static db_data data;
      int ret;

       //Creating cache
       createHt(&EntryCache,NUMSLOT);

       // Creating database
       if (ret = create_db(DATABASE,&dbt) != 0) {
                perror("Creating db");
                exit(EXIT_FAILURE);
        }


        // Write key n.1

        memset(&key, 0, sizeof(key));
        memset(&data, 0, sizeof(data));

        key.key=strdup("key1");
        key.size=sizeof("key1");

        data.data=strdup("data1");
        data.size=sizeof("data1");


        if (dbt->db_put(dbt,&key,&data)<0) {
            perror("Inserting key");
            //exit(EXIT_FAILURE);
        }

       free(key.key);
       free(data.data);

        // Write key n.2

        memset(&key, 0, sizeof(key));
        memset(&data, 0, sizeof(data));

        key.key=strdup("key2");
        key.size=sizeof("key2");

        data.data=strdup("data2");
        data.size=sizeof("data2");


        if (dbt->db_put(dbt,&key,&data)<0) {
            perror("Inserting key");
            //exit(EXIT_FAILURE);
        }

       free(key.key);
       free(data.data);

        // Write key n.3

        memset(&key, 0, sizeof(key));
        memset(&data, 0, sizeof(data));

        key.key=strdup("key3");
        key.size=sizeof("key3");

        data.data=strdup("data3");
        data.size=sizeof("data3");


        if (dbt->db_put(dbt,&key,&data)<0) {
            perror("Inserting key");
           // exit(EXIT_FAILURE);
        }

       free(key.key);
       free(data.data);


       fclose(dbt->dt);
       fclose(dbt->idx);

        if (dbt->db_open(DATABASE,dbt,dbt->idx,dbt->dt)<0) {
            perror("Opening");
        //  exit(EXIT_FAILURE);
        }

      db_key db_k;
      db_k.key=strdup("key2");
      db_k.size=sizeof("key2");

      char *s=dbt->db_get(dbt,&db_k);
      if (s) {
            printf("Data found: %s\n",s);
      } else {
           printf("%s\n","Key not found");
      }

      // Cleaning up
      free(db_k.key);

      db_k.key=strdup("ugo");
      db_k.size=sizeof("ugo");

      s=dbt->db_get(dbt,&db_k);
      if (s) {
            printf("%s\n",s);
      } else {
           printf("%s\n","Key not found");
      }

       free(db_k.key);

       //Writing key n.4 after reopening

        memset(&key, 0, sizeof(key));
        memset(&data, 0, sizeof(data));

        key.key=strdup("key4");
        key.size=sizeof("key4");

        data.data=strdup("data4");
        data.size=sizeof("data4");


        if (dbt->db_put(dbt,&key,&data)<0) {
            perror("Inserting key");
           // exit(EXIT_FAILURE);
        }


       if (ret=destroy_db(&dbt)!=0) {
                perror("Cannot destroy db");
       }


       printf("%s\n","Traversing cache");
       traverseHashChain(EntryCache);
       destroyHt(&EntryCache);

       exit(EXIT_SUCCESS);

}
