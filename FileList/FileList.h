#ifndef FILELIST_H_
#define FILELIST_H_

/*
    头文件 <io.h>
    _finddata_t 存储文件信息的结构类型
    long _findfirst( char *filespec, struct _finddata_t *fileinfo )
    filespec：标明文件的字符串，可支持通配符
    成功返回一个long型句柄（一个唯一编号）， 失败返回-1
    查找成功， 函数将信息读入fileinfo结构体

    int _findnext( long handle, struct _finddata_t *fileinfo )
    若成功返回0，否则返回-1
    参数： handle ：_findfirst函数返回回来的句柄
    fileinfo：文件信息结构体的指针。找到文件后，函数将该文件信息放入此结构体中

    int _findclose( long handle )
    成功返回0，失败返回-1
    参数： handle ：_findfirst函数返回回来的句柄
*/

#include <iostream>
#include <string>
#include <io.h>

// 遍历文件夹下所有的文件
void FileList(std::string path, int depth = 0)
{
    std::string filename = path + "*";
    // 用于查找的句柄
    long handle;
    struct _finddata_t fileInfo;
    // 第一次查找
    handle = _findfirst(filename.c_str(), &fileInfo);
    if (handle == -1)
    {
        std::cout << "there is no such kind of file.\n";
        return;
    }

    do
    {
        if (fileInfo.attrib & _A_SUBDIR)        // 通过位与运算判断是不是一个文件夹
        {
            if (strcmp(fileInfo.name, ".") != 0 && strcmp(fileInfo.name, "..") != 0)
            {
                for (int i = 0; i < depth; ++i)
                    std::cout << "\t";
                std::cout << fileInfo.name << std::endl;
                FileList(path + fileInfo.name + "\\*", depth + 1);
            }
        }
        else
        {
            for (int i = 0; i < depth; ++i)
                std::cout << "\t";
            std::cout << fileInfo.name << std::endl;
        }
    } while (!_findnext(handle, &fileInfo));

    _findclose(handle);
}
#endif // FILELIST_H_
