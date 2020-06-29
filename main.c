#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	/*
	 *	usage : ./program  SourceFilename  EncryptedFilename  Key
	 *	decrypt usage : ./program  EncryptedFilename  OriginalFile  Key
	 *	Key's max length : 255
	 */
	char enc[255] = "abcd"; //default key
	char destFile[255] = "tmp.encrypt"; //default Encrypted filename
	if(argc > 2 && strlen(argv[2]) > 0)
	{
		strcpy(destFile, argv[2]);
	}
	if(argc > 3)
	{
		strcpy(enc, argv[3]);
	}

	unsigned int pwlen = strlen(enc);

	if(pwlen == 0)
	{
		printf("without pw\n");
		return -1;
	}

	FILE * fSource, *fDest, *fEnp;
	
	if(access(argv[1], F_OK) == 0)
	{
		fSource = fopen(argv[1], "rb");
		fDest = fopen(destFile, "wb");
	
		char b,k;
		int index = 0;
		while( !feof(fSource) )
		{
		  fread(&b, 1, 1, fSource);
		  if(!feof(fSource))
		  {
			k = enc[index % pwlen];
			b = b ^ k;
			fwrite(&b, 1, 1, fDest);
			index++;
		  }
		}

		fclose(fSource);
		fclose(fDest);
		
		fEnp = fopen("encryptKey.txt", "wb");
		fwrite(enc, pwlen, 1, fEnp);
		fclose(fEnp);
	}
	else
	{
		printf("without file\n");
	}
	return 0;
}
