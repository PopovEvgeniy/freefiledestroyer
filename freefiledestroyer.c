#include "freefiledestroyer.h"

void intro();
void show_progress(const long long int start,const long long int end);
long long int get_file_size(const int target);
int open_target_file(const char *name);
char *get_memory(const size_t size);
void corrupt_file(const char *target);
void delete_file(const char *target);
void set_access(const char *target);

int main(int argc, char *argv[])
{
 intro();
 if (argc!=2)
 {
  puts("You must give a target file name as the command-line argument!");
 }
 else
 {
  set_access(argv[1]);
  corrupt_file(argv[1]);
  delete_file(argv[1]);
 }
 return 0;
}

void intro()
{
 putchar('\n');
 puts("FREE FILE DESTROYER");
 puts("Version 1.3.4");
 puts("Securely file erasing tool by Popov Evgeniy Alekseyevich,2012-2025 year");
 puts("This program is distributed under GNU GENERAL PUBLIC LICENSE");
 putchar('\n');
}

void show_progress(const long long int start,const long long int end)
{
 long long int progress;
 progress=(start+1)*100;
 progress/=end;
 putchar('\r');
 printf("Amount of the processed bytes: %lld from %lld. Progress:%lld%%",start,end,progress);
}

long long int get_file_size(const int target)
{
 long long int length;
 length=file_seek(target,0,SEEK_END);
 file_seek(target,0,SEEK_SET);
 return length;
}

int open_target_file(const char *name)
{
 int file;
 file=open(name,TARGET_FILE_MODE);
 if (file==-1)
 {
  puts("Can't open the target file");
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
 char *data=NULL;
 long long int index,size;
 size_t block;
 output=open_target_file(target);
 size=get_file_size(output);
 index=0;
 block=4096;
 data=get_memory(block);
 while (index<size)
 {
  if ((size-index)<=(long long int)block)
  {
   block=(size_t)(size-index);
  }
  if (write(output,data,block)==-1)
  {
   putchar('\n');
   puts("Can't totally wipe the target file");
   break;
  }
  index=file_seek(output,0,SEEK_CUR);
  show_progress(index,size);
 }
 free(data);
 putchar('\n');
 close(output);
}

void delete_file(const char *target)
{
 if (remove(target)!=0)
 {
  puts("Can't destroy the target file");
  exit(3);
 }

}

void set_access(const char *target)
{
 if (chmod(target,TARGET_FILE_PERMISSIONS)==-1)
 {
  puts("Can't set the file access rights");
  exit(4);
 }

}