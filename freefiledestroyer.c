#include "freefiledestroyer.h"
#include "exitcode.h"
#include "settings.h"

void show_intro();
void show_error(const char *message);
void show_progress(const long long int start,const long long int end);
FILE *open_target_file(const char *name);
long long int get_file_position(FILE *target);
long long int get_file_size(FILE *target);
unsigned char *get_memory(const size_t size);
size_t write_data(FILE *target,const void *buffer,const size_t length);
void delete_file(const char *target);
void set_access(const char *target);
void force_write(FILE *target,const size_t block,const size_t limit);
void corrupt_file(const char *name);

int main(int argc, char *argv[])
{
 show_intro();
 if (argc<2)
 {
  puts("You must give a target file name as the command-line argument!");
  exit(COMMAND_LINE_ARGUMENTS_ERROR);
 }
 else
 {
  set_access(argv[1]);
  corrupt_file(argv[1]);
  delete_file(argv[1]);
 }
 return 0;
}

void show_intro()
{
 putchar('\n');
 puts("FREE FILE DESTROYER");
 puts("Version 1.5.5");
 puts("The secure file-erasing tool by Popov Evgeniy Alekseyevich,2012-2026 year");
 puts("This program is distributed under the GNU GENERAL PUBLIC LICENSE");
 putchar('\n');
}

void show_error(const char *message)
{
 fputc('\n',stderr);
 fputs(message,stderr);
 fputc('\n',stderr);
}

void show_progress(const long long int start,const long long int stop)
{
 putchar('\r');
 printf("The current position: %lld.The end data position: %lld. The operation progress:%lld%%",start,stop,(start*100)/stop);
}

FILE *open_target_file(const char *name)
{
 FILE *target=NULL;
 if (name!=NULL)
 {
  target=fopen(name,"r+b");
 }
 if (target==NULL)
 {
  show_error("Can't open the target file");
  exit(OPEN_FILE_ERROR);
 }
 return target;
}

long long int get_file_position(FILE *target)
{
 long long int position=0;
 position=file_tell(target);
 if (position<0)
 {
  show_error("Can't get the current position!");
  exit(GET_FILE_POSITION_ERROR);
 }
 return position;
}

long long int get_file_size(FILE *target)
{
 long long int length=0;
 if (file_seek(target,0,SEEK_END)!=0)
 {
  show_error("Can't get the file size!");
  exit(GET_FILE_SIZE_ERROR);
 }
 length=file_tell(target);
 file_seek(target,0,SEEK_SET);
 return length;
}

unsigned char *get_memory(const size_t size)
{
 unsigned char *memory=NULL;
 memory=(unsigned char*)calloc(size,sizeof(char));
 if (memory==NULL)
 {
  show_error("Can't allocate memory");
  exit(MEMORY_ALLOCATION_ERROR);
 }
 return memory;
}

size_t write_data(FILE *target,const void *buffer,const size_t length)
{
 return fwrite(buffer,sizeof(char),length,target);
}

void delete_file(const char *target)
{
 if (remove(target)!=0)
 {
  show_error("Can't destroy the target file");
  exit(DESTROY_FILE_ERROR);
 }

}

void set_access(const char *target)
{
 if (target==NULL)
 {
  show_error("Can't set the file access rights");
  exit(SET_ACCESS_ERROR);
 }
 if (chmod(target,TARGET_FILE_PERMISSIONS)==-1)
 {
  show_error("Can't set the file access rights");
  exit(SET_ACCESS_ERROR);
 }

}

void force_write(FILE *target,const size_t block,const size_t limit)
{
 static size_t written=0;
 written+=block;
 if (written>=limit)
 {
  fflush(target);
  written=0;
 }

}

void corrupt_file(const char *name)
{
 unsigned char *data=NULL;
 FILE *target=NULL;
 long long int index=0;
 long long int length=0;
 long long int elapsed=0;
 size_t block=DATA_BLOCK_LENGTH;
 target=open_target_file(name);
 length=get_file_size(target);
 data=get_memory(block);
 while (index<length)
 {
  elapsed=length-index;
  if (elapsed<=DATA_BLOCK_LENGTH)
  {
   block=(size_t)elapsed;
  }
  if (write_data(target,data,block)<block)
  {
   putchar('\n');
   puts("Can't totally wipe the target file");
   break;
  }
  else
  {
   force_write(target,block,DATA_LIMIT);
  }
  index=get_file_position(target);
  show_progress(index,length);
 }
 fclose(target);
 free(data);
}