#include <stdio.h>
#include <windows.h>

int main() {
    WIN32_FIND_DATA fd;
    HANDLE h = FindFirstFile("extras\\*.*", &fd);
    while(1) 
    {
        printf("%s\n", fd.cFileName);
        if (FindNextFile(h, &fd) == 0)
        {
            break;
        }
    }
    return 0;
}