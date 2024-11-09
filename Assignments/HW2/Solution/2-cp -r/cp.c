#include <stdio.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
struct s_d 
{
	char* source;
	char* dest;
};

void *cpf(void *arg)
{
	printf("hi\n");
	char *s = ( ( struct s_d* ) arg )->source , *d = ( ( struct s_d* ) arg )->dest;
	printf("%s	%s\n\n",s,d);
	FILE *sf = fopen(s,"r"), *df = fopen(d,"w");
	char myString[100];
	while( fgets( myString , 100, sf ) )
		fprintf( df ,"%s", myString );

	fclose(sf); fclose(df);
	
	return NULL;
}

void *cpd(void *arg)
{
	char *s = ( ( struct s_d* ) arg )->source , *d = ( ( struct s_d* ) arg )->dest;

	DIR *tmp = opendir(s);
	struct dirent *td;
	int i = 0;for (;(td = readdir(tmp)) != NULL;i++);
	pthread_t t_ids[i];
	closedir(tmp);

	DIR* source = opendir( s );
	mkdir( d , 0777 );
	DIR* dest = opendir( d );

	struct dirent *entry;
	for (int j = 0;(entry = readdir(source)) != NULL;)
	{
		struct s_d* arg = (struct s_d*)malloc(sizeof(struct s_d));

		char* stmp = (char*)malloc((strlen(s)+strlen(entry->d_name)+1)*sizeof(char));
		strcpy(stmp,s); strcat(stmp,"/"); strcat(stmp,entry->d_name);
		arg->source = stmp;
		
		char* dtmp = (char*)malloc((strlen(s)+strlen(entry->d_name)+1)*sizeof(char));
		strcpy(dtmp,d); strcat(dtmp,"/"); strcat(dtmp,entry->d_name);
		arg->dest = dtmp;

		if (entry->d_type == DT_DIR)
		{
			if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0)
				continue;
			printf("dir: %s\n", entry->d_name);
			pthread_create(t_ids+j , NULL , cpd , arg);
		}
		else
		{
			printf("file: %s\n", entry->d_name);
			pthread_create(t_ids+j , NULL , cpf , arg);
		}
		j++;
	}
	
	for( int j = 0 ; j < i - 2 ; j++)
		pthread_join(t_ids[j],NULL);
	
	closedir(source);
	closedir(dest);
	
	return NULL;
}

int main(int argc, char **argv)
{
	char *s = argv[1] , *d = argv[2];
	DIR *tmp = opendir(s);
	struct dirent *td;
	int i = 0; for( ; (td = readdir(tmp)) != NULL ; i++ );
	pthread_t t_ids[i];
	closedir(tmp);


	DIR *source = opendir(s);
	DIR *dest   = opendir(d);
	if (source == NULL && dest == NULL)
		printf("Error : can't open source or destination!\n");

	struct dirent *entry;
	for (int j = 0;(entry = readdir(source)) != NULL;)
	{
		struct s_d* arg = (struct s_d*)malloc(sizeof(struct s_d));

		char* stmp = (char *)malloc((strlen(s)+strlen(entry->d_name)+1)*sizeof(char));
		strcpy(stmp,s); strcat(stmp,"/"); strcat(stmp,entry->d_name);
		arg->source = stmp;
		
		char* dtmp = (char*)malloc((strlen(s)+strlen(entry->d_name)+1)*sizeof(char));
		strcpy(dtmp,d); strcat(dtmp,"/"); strcat(dtmp,entry->d_name);
		arg->dest = dtmp;

		if (entry->d_type == DT_DIR)
		{
			if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0)
				continue;
			printf("0dir: %s\n", entry->d_name);
			pthread_create(t_ids+j , NULL , cpd , arg);
		}
		else
		{
			printf("0file: %s\n", entry->d_name);
			pthread_create(t_ids+j , NULL , cpf , arg);
		}
		j++;
	}

	for( int j = 0 ; j < i-2 ; j++)
		pthread_join(t_ids[j],NULL);

	closedir(source);
	closedir(dest);

	return 0;
}