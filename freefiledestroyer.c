/*
Available platform identfer
MS_WINDOWS - 32 bit Microsoft Windows and 64 bit Microsoft Windows
UNIX_32 - 32 bit Unix like system
UNIX_64 - 64 bit Unix like system
*/
#define MS_WINDOWS
#include "freefiledestroyer.h"

void intro();
void show_progress(long long int start, long long int end);
long long int get_file_size(int target);
int open_input_file(char *name);
char *get_memory(long int size);
void corrupt_file(char *target);
void delete_file(char *target);

int main(int argc, char *argv[])
{
 intro();
 if (argc!=2)
 {
  puts("You must get target file name as command line argument!");
 }
 else
 {
  corrupt_file(argv[1]);
  delete_file(argv[1]);
 }
 return 0;
}

void intro()
{
 printf("\n");
 puts("FREE FILE DESTROYER");
 puts("Version 1.1.3");
 puts("Securely file destroy tool by Popov Evgeniy Alekseyevich,2012-2016 year");
 puts("This program distributed under GNU GENERAL PUBLIC LICENSE");
 printf("\n");
}

void show_progress(long long int start, long long int end)
{
 long long int progress;
 progress=start+1;
 progress*=100;
 progress/=end;
 printf("\r");
 printf("Amount of processed bytes: %lld from %lld. Progress:%lld%%",start,end,progress);
}

long long int get_file_size(int target)
{
 long long int length;
 length=file_seek(target,0,SEEK_END);
 file_seek(target,0,SEEK_SET);
 return length;
}

int open_input_file(char *name)
{
 int file;
 file=open(name,TARGET_FILE_MODE,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
 if (file==-1)
 {
  puts("Can't open target file");
  exit(1);
 }
 return file;
}

char *get_memory(long int size)
{
 char *memory=NULL;
 memory=(char*)calloc(size,1);
 if(memory==NULL)
 {
  puts("Can't allocate memory");
  exit(2);
 }
 return memory;
}

void corrupt_file(char *target)
{
 int output;
 const long int block_length=33554432;
 char *data=NULL;
 long long int index,size;
 long int block;
 output=open_input_file(target);
 size=get_file_size(output);
 index=0;
 block=block_length;
 data=get_memory(block);
 while(index<size)
 {
  if(size-index<=block_length)
  {
   block=size-index;
  }
  show_progress(index+block,size);
  if(write(output,data,block)==-1)
  {
   printf("\n");
   puts("Can't totally wipe the target file");
   break;
  }
  index+=block;
 }
 free(data);
 printf("\n");
 close(output);
}

void delete_file(char *target)
{
 if(remove(target)==0)
 {
  puts("Target file successfully destroyed");
 }
 else
 {
  puts("Can't destroy target file");
  exit(3);
 }

}