#include "freefiledestroyer.h"
#include "exitcode.h"
#include "settings.h"

void show_intro();
void show_message(const char *message);
void show_error(const char *message);
void show_system_error(const char *message,const int code);
void check_name(const char *name,const char *message,const int code);
void show_progress(const long long int start,const long long int end);
int open_target_file(const char *name);
long long int get_file_position(const int target);
long long int get_file_size(const int target);
unsigned char *get_memory(const size_t size);
size_t write_data(const int target,const unsigned char *buffer,const size_t length);
void delete_file(const char *target);
void set_access(const char *target);
void force_write(const int target,const size_t block,const size_t limit);
void corrupt_file(const char *name);
void work(const char *name);

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
  work(argv[1]);
 }
 return 0;
}

void show_intro()
{
 putchar('\n');
 puts("FREE FILE DESTROYER 1.6.7");
 puts("The secure file-erasing tool by Popov Evgeniy Alekseyevich,2012-2026 year");
 puts("This program is distributed under the GNU GENERAL PUBLIC LICENSE");
 putchar('\n');
}

void show_message(const char *message)
{
 putchar('\n');
 puts(message);
}

void show_error(const char *message)
{
 fputc('\n',stderr);
 fputs(message,stderr);
 fputc('\n',stderr);
}

void show_system_error(const char *message,const int code)
{
 show_error(message);
 fputs(strerror(code),stderr);
 fputc('\n',stderr);
}

void check_name(const char *name,const char *message,const int code)
{
 size_t length=0;
 if (name!=NULL)
 {
  length=strlen(name);
 }
 if (length==0)
 {
  show_error(message);
  exit(code);
 }

}


void show_progress(const long long int start,const long long int stop)
{
 putchar('\r');
 printf("The current position: %lld.The end data position: %lld. The operation progress:%lld%%",start,stop,(start*100)/stop);
}

int open_target_file(const char *name)
{
 int target=-1;
 target=open(name,TARGET_FILE_MODE);
 if (target==-1)
 {
  show_system_error("Can't open the target file",errno);
  exit(OPEN_FILE_ERROR);
 }
 return target;
}

long long int get_file_position(const int target)
{
 long long int position=0;
 position=file_seek(target,0,SEEK_CUR);
 if (position==-1)
 {
  show_system_error("Can't get the current position!",errno);
  exit(GET_FILE_POSITION_ERROR);
 }
 return position;
}

long long int get_file_size(const int target)
{
 long long int length=0;
 length=file_seek(target,0,SEEK_END);
 if (length==-1)
 {
  show_system_error("Can't get the file size!",errno);
  exit(GET_FILE_SIZE_ERROR);
 }
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

size_t write_data(const int target,const unsigned char *buffer,const size_t length)
{
 ssize_t written=0;
 size_t total=0;
 for (total=0;total<length;total+=written)
 {
  written=write(target,buffer+total,length-total);
  if (written<=0)
  {
   if (try_again==0)
   {
    total=0;
    break;
   }
   else
   {
    written=0;
    continue;
   }

  }

 }
 return total;
}

void delete_file(const char *target)
{
 if (remove(target)!=0)
 {
  show_system_error("Can't destroy the target file",errno);
  exit(DESTROY_FILE_ERROR);
 }

}

void set_access(const char *target)
{
 if (chmod(target,TARGET_FILE_PERMISSIONS)==-1)
 {
  show_system_error("Can't set the file access rights",errno);
  exit(SET_ACCESS_ERROR);
 }

}

void force_write(const int target,const size_t block,const size_t limit)
{
 static size_t written=0;
 written+=block;
 if (written>=limit)
 {
  file_sync(target);
  written=0;
 }

}

void corrupt_file(const char *name)
{
 unsigned char *data=NULL;
 int target=-1;
 long long int index=0;
 long long int length=0;
 long long int elapsed=0;
 size_t written=0;
 size_t block=DATA_BLOCK_LENGTH;
 target=open_target_file(name);
 length=get_file_size(target);
 data=get_memory(block);
 while (index<length)
 {
  elapsed=length-index;
  if (elapsed<DATA_BLOCK_LENGTH)
  {
   block=(size_t)elapsed;
  }
  written=write_data(target,data,block);
  if (written==0)
  {
   show_message("Can't totally wipe the target file");
   break;
  }
  else
  {
   force_write(target,written,DATA_LIMIT);
   index=get_file_position(target);
   show_progress(index,length);
  }

 }
 free(data);
 show_message("Data synchronization in progress. Please wait");
 file_sync(target);
 close(target);
}

void work(const char *name)
{
 check_name(name,"The target file name is empty",EMPTY_TARGET_NAME_ERROR);
 set_access(name);
 corrupt_file(name);
 delete_file(name);
}