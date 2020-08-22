#include<stdio.h>

#include<libpq-fe.h>

#include<stdlib.h>

#include<dirent.h>

#include<string.h>

#include <time.h>




int main() {
    
    PGconn *conn = PQconnectdb("user=finalp password=12345678 dbname=fpdb hostaddr = 127.0.0.1 port = 5432");

    //commnad to execute in terminal to create databasae Table
    PGresult *res = PQexec(conn, "CREATE TABLE IF NOT EXISTS fp_stores_data\
    (time TIMESTAMP NOT NULL, \
    market_id INTEGER , \
    product_id INTEGER , \
    provice VARCHAR(20) NOT NULL,\
    city VARCHAR(20) NOT NULL,\
    price INT, \
    quantity INT, \
    has_sold INT,\
    UNIQUE (market_id),\
    UNIQUE (product_id),\
    CONSTRAINT pk_market_product\
    PRIMARY KEY(market_id,product_id));");

//if any error occurred print it
 if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "%s\n", PQerrorMessage(conn));
    }
    
    //set directory that report file are in there
    DIR* directory = opendir("..");
    struct dirent *d ;
//open the directory
    while((d = readdir(directory)) != NULL){
	//if this was report file then go in bracket
        if(strstr(d->d_name,"report-1") != NULL){
       
                //create path
                char baseDir[300] = "../";
                strcat(baseDir,d->d_name);
                
                //open file with created path(baseDir) in  read mode
                FILE *fileName = fopen(baseDir,"r");

                //go through file and get it's lines
                while(!feof(fileName)){
                char str[500];
                //fill str array with lines of text file
                fgets(str,500,fileName);
                
                
                
                //to split a string
                //Extract the first token
                char * token = strtok(str, ",");
                //loop through the string to extract all other tokens
                
                    char info[8][20];
                    int i = 0;
                    while( token != NULL ) {
                        
                        char tmp[20];
                        sprintf(tmp,u8"%s",token);
                        //asign it to array
                        strcpy(info[i],tmp);
                        printf(u8"%s\n", tmp ); //printing each token
                        token = strtok(NULL , ",");
                        i++;
                        
                    }
                    //creating commad to INSERT informations
                    char command[500];
                    sprintf(command,"INSERT INTO fp_stores_data (time,provice,city,market_id,product_id,price,quantity,has_sold) VALUES (%s,%s,%s,%s,%s,%s,%s,%s);" ,
                                                info[0],info[1],
                                                info[2],info[3],
                                                info[4],info[5],
                                                info[6],info[7]);




                    //executing command
                    res = PQexec(conn,command);

                }
              }
            }


    return 0;
}