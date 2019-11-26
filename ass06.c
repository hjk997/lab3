#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

#define MAX_BUF 256

int countFile = 0;

void ls(char *argv)
{
	DIR *dir, *tempDir;
	struct dirent *directory;
	struct stat file_state;

	char current[MAX_BUF];
    char previlege[11];

	memset(current, 0, MAX_BUF);		

    strcpy(previlege, "----------");
    
	if( (dir = opendir(argv)) < 0)
	{
		perror("opendir");
		exit(1);
	}
	
	//항목 읽기 시작
	while( (directory = readdir(dir)) != NULL)
	{
		countFile++;

        sprintf(current, "%s/%s", argv, directory->d_name);
//		printf("%s\n", current);

        //파일 형식 가져오기
        if(lstat(current, &file_state) < 0)
		{
			perror("stat");
			exit(1);
		}

        //파일의 권한 
        // 관리자
        if (file_state.st_mode & S_IRUSR) previlege[1] = 'r';
        if (file_state.st_mode & S_IWUSR) previlege[2] = 'w';
        if (file_state.st_mode & S_IXUSR) previlege[3] = 'x';
        // 소유자
        if (file_state.st_mode & S_IRGRP) previlege[4] = 'r';
        if (file_state.st_mode & S_IWGRP) previlege[5] = 'w';
        if (file_state.st_mode & S_IXGRP) previlege[6] = 'x';
        // 사용자
        if (file_state.st_mode & S_IROTH) previlege[7] = 'r';
        if (file_state.st_mode & S_IWOTH) previlege[8] = 'w';
        if (file_state.st_mode & S_IXOTH) previlege[9] = 'x';

        //권한 출력
		printf("%s ", previlege);

        //하드링크 수
        printf("%3d ", file_state.st_nlink );

        //사용자아이디 그룹아이디
        printf("%s %s ", getpwuid(file_state.st_uid)->pw_name, getgrgid(file_state.st_gid)->gr_name);

        //파일 사이즈
        printf("%7d ", file_state.st_size);

        //시간출력
        char *file_time = ctime(&file_state.st_ctime)+4;
        for (int i = 0; *file_time != '\n'; i++) {
        printf("%c", *file_time);
        file_time++;
        }

        printf(" ");


        //파일 이름 출력
		printf("%s\n", directory->d_name);

    }

    close(argv);

}

void main(int argc, char *argv[]) 
{
    int opt = NULL;
//    printf("%d", argc);
    if(argc == 4)
    {
        if( !strcmp(argv[1],"ls") )
        {
            printf("pass ls\n");
            while((opt = getopt(argc, argv, "la:"))!=EOF)
            {
                switch(opt)
                {
                    case 'a':
                    case 'l':
                        ls(argv[3]);
                    default:
                        break;
                }
            }
        }
    }
    else
    {
        printf("usage: a.out ls -la directoryName\n");
    }

    printf("합계 : %d\n", countFile );
}
