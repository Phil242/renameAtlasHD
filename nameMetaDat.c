// Auteur : Philippe Paget
// Lience : MIT


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char  pad1[0x15];
	char  chan[0x21];
	char  pad2;
	char  prov[0x21];
	char  pad3[0xA1];
	char  prog[0x3F];
	unsigned char  recHour; // UTC
	unsigned char  recMin;
	char  pad4[0x02];
	unsigned char  year1;
	unsigned char  year2;
	unsigned char  month;
	unsigned char  day;
	char  pad5[0x08];
	unsigned char  hour; // prog len
	unsigned char  min;
	unsigned char  sec;
	char  pad6[0x2D];
} DAT ;

char tolow(char car)
{
        if ((car <= 'Z') && (car >= 'A'))
                return (car + 0x20);
        else
                return (car);
}

void strlwr(char * buffer)
{
        int i;
        for(i = 0; buffer[i]; i++)
		buffer[i] = tolow(buffer[i]);
}

int lenFile(char * nom)
{
        FILE *fp;
        int file_size=0;
        if ((fp = fopen(nom, "rb" )) == NULL)
        {
                //printf("%s",nom);
                printf("META.DAT");
                exit(1);
        }
        if (fseek(fp, (long)(0), SEEK_END) != 0)
        {
                fclose(fp);
                return(file_size);
        }
        file_size = (ftell(fp));
        fclose(fp);
        return(file_size);
}

int main(int argc, char *argv[])
{
	DAT dat;
	char fileName[10+0x21+1+0x3F+1+5+3*3+20];
	char buff[100];
	FILE * fd;

	if (argc != 2 )
	{
		printf("Utilisation: nameMetaDat META.DAT\n");
		exit(1);
	}

	memset(fileName,0,sizeof(fileName));
	memset(buff,0,sizeof(buff));

	if (lenFile(argv[1])!=376)
	{
		//printf("%s",argv[1]);
		printf("META.DAT");
		exit(1);
	}

	fd = fopen( argv[1], "rb");
	fread(&dat,sizeof(DAT),1,fd);
	fclose(fd);

	if (dat.year2 != 0x07 )
	{
		printf("META.DAT");
		exit(1);
	}

	sprintf(fileName,"%d-%02d-%02d - ",(dat.year2<<8)+dat.year1,dat.month,dat.day);
	strncpy(buff,dat.chan,0x21);
	strlwr(&buff[1]);
	strcat(fileName,buff);
	strcat(fileName," - ");

	if(strcmp(dat.chan,dat.prog))
	{
		strncpy(buff,dat.prog,0x3F);
		strlwr(&buff[1]);
		strcat(fileName,buff);
		strcat(fileName," - ");
	}
	else
	{

	}

	sprintf(buff,"%dH%02d",dat.hour,dat.min);
	strcat(fileName,buff);
	printf("%s",fileName);
	return 0;
}
