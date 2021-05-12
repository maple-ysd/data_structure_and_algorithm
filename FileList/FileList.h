#ifndef FILELIST_H_
#define FILELIST_H_

/*
    ͷ�ļ� <io.h>
    _finddata_t �洢�ļ���Ϣ�Ľṹ����
    long _findfirst( char *filespec, struct _finddata_t *fileinfo )
    filespec�������ļ����ַ�������֧��ͨ���
    �ɹ�����һ��long�;����һ��Ψһ��ţ��� ʧ�ܷ���-1
    ���ҳɹ��� ��������Ϣ����fileinfo�ṹ��

    int _findnext( long handle, struct _finddata_t *fileinfo )
    ���ɹ�����0�����򷵻�-1
    ������ handle ��_findfirst�������ػ����ľ��
    fileinfo���ļ���Ϣ�ṹ���ָ�롣�ҵ��ļ��󣬺��������ļ���Ϣ����˽ṹ����

    int _findclose( long handle )
    �ɹ�����0��ʧ�ܷ���-1
    ������ handle ��_findfirst�������ػ����ľ��
*/

#include <iostream>
#include <string>
#include <io.h>

// �����ļ��������е��ļ�
void FileList(std::string path, int depth = 0)
{
    std::string filename = path + "*";
    // ���ڲ��ҵľ��
    long handle;
    struct _finddata_t fileInfo;
    // ��һ�β���
    handle = _findfirst(filename.c_str(), &fileInfo);
    if (handle == -1)
    {
        std::cout << "there is no such kind of file.\n";
        return;
    }

    do
    {
        if (fileInfo.attrib & _A_SUBDIR)        // ͨ��λ�������ж��ǲ���һ���ļ���
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
