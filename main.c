#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <WinUser.h>

char* GetDay(int day);
char* GetMonth(int month);

int main(void)
{
    time_t t = time(NULL);

    struct tm buf;

    FILE* timeCode;
    char str[32];
    int err = localtime_s(&buf, &t);
    if (err != 0)
    {
        printf("error\n");
        exit(13);
    }
    char* day = GetDay(buf.tm_wday);
    char* mon = GetMonth(buf.tm_mon);

    sprintf_s(str, 32, "%s %d %s %d, %dh%dm%ds.txt", day, buf.tm_mday, mon, buf.tm_year + 1900, buf.tm_hour, buf.tm_min, buf.tm_sec);
    printf("S pour noter un temps et N pour arreter.\n");
    fopen_s(&timeCode, str, "w");

    if (timeCode != 0)
    {
        char continuer = 1;
        while (continuer)
        {
            Sleep(50);
            if (GetKeyState(0x53) & 0x8000) // S
            {
                t = time(NULL);
                err = localtime_s(&buf, &t);
                if (err != 0)
                {
                    printf("error\n");
                    exit(15);
                }
                printf("%dh %dmin %ds\n", buf.tm_hour, buf.tm_min, buf.tm_sec);
                fprintf_s(timeCode, "%d:%d:%d\n", buf.tm_hour, buf.tm_min, buf.tm_sec);
            }
            else if (GetKeyState(0x4E) & 0x8000)
            {
                continuer = 0;
            }
        }

        fclose(timeCode);
    }
    else
    {
        printf("erreur d'ouverture du fichier %s\n", str);
        exit(13);
    }
    
    system("pause");
    return 0;
}

char* GetDay(int day)
{
    switch (day)
    {
    case 0:
        return "Dim";
    case 1:
        return "Lun";
    case 2:
        return "Mar";
    case 3:
        return "Mer";
    case 4:
        return "Jeu";
    case 5:
        return "Ven";
    case 6:
        return "Sam";
    default:
        return "ERR";
    }
}

char* GetMonth(int month)
{
    switch (month)
    {
    case 0:
        return "Jan";
    case 1:
        return "Fev";
    case 2:
        return "Mar";
    case 3:
        return "Avr";
    case 4:
        return "Mai";
    case 5:
        return "Jun";
    case 6:
        return "Jui";
    case 7:
        return "Aou";
    case 8:
        return "Sep";
    case 9:
        return "Oct";
    case 10:
        return "Nov";
    case 11:
        return "Dec";
    default:
        return "ERR";
    }
}