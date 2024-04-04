#include "freefiledestroyer.h"

void intro();
void show_progress(const long long int start,const long long int end);
long long int get_file_size(const int target);
int open_input_file(const char *name);
char *get_memory(const size_t size);
void corrupt_file(const char *target);
void delete_file(const char *target);

int main(int argc, char *argv[])
{
 intro();
 if (argc!=2)
 {
  puts("You must give target file name as command line argument!");
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
 putchar('\n');
 puts("FREE FILE DESTROYER");
 puts("Version 1.2.3");
 puts("Securely file erasing tool by Popov Evgeniy Alekseyevich,2012-2024 year");
 puts("This program distributed under GNU GENERAL PUBLIC LICENSE");
 putchar('\n');
}

void show_progress(const long long int start,const long long int end)
{
 long long int progress;
 progress=(start+1)*100;
 progress/=end;
 putchar('\r');
 printf("Amount of processed bytes: %lld from %lld. Progress:%lld%%",start,end,progress);
}

long long int get_file_size(const int target)
{
 long long int length;
 length=lseek64(target,0,SEEK_END);
 lseek64(target,0,SEEK_SET);
 return length;
}

int open_input_file(const char *name)
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

char *get_memory(const size_t size)
{
 char *memory=NULL;
 memory=(char*)calloc(size,sizeof(char));
 if(memory==NULL)
 {
  puts("Can't allocate memory");
  exit(2);
 }
 return memory;
}

void corrupt_file(const char *target)
{
 int output;
 const size_t block_length=4096;
 char *data=NULL;
 long long int index,size;
 size_t block;
 output=open_input_file(target);
 size=get_file_size(output);
 index=0;
 block=block_length;
 data=get_memory(block);
 while(index<size)
 {
  if(size-index<=(long long int)block_length)
  {
   block=(size_t)size-(size_t)index;
  }
  show_progress(index+(long long int)block,size);
  if(write(output,data,block)==-1)
  {
   putchar('\n');
   puts("Can't totally wipe the target file");
   break;
  }
  index+=(long long int)block;
 }
 free(data);
 putchar('\n');
 close(output);
}

void delete_file(const char *target)
{
 if(remove(target)!=0)
 {
  puts("Can't destroy target file");
  exit(3);
 }

}