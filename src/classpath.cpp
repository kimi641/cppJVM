#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include "zlib.h"
#include "unzip.h"

#include "classpath.h"

WildcardEntry::WildcardEntry(std::string path){}

std::string WildcardEntry::readClass(std::string className)
{
    return className;
}

ZipEntry::ZipEntry(std::string path):absPath(path){}

std::string ZipEntry::readClass(std::string className)
{
    std::string fileName = absPath;
    HZIP hz = OpenZip(absPath.c_str(),0);
    ZIPENTRY ze;
    int i;
    FindZipItem(hz,className.c_str(),true,&i,&ze);
    char* ibuf = new char[ze.unc_size];
    UnzipItem(hz,i,ibuf,ze.unc_size);
    std::string bufferString(ibuf,ze.unc_size-1);
    delete[] ibuf;
    CloseZip(hz);
    return bufferString;
}

DirEntry::DirEntry(std::string path):absDir(path){}

std::string DirEntry::readClass(std::string className)
{
    std::string fileName = absDir + className;
    std::ifstream ifs (fileName, std::ifstream::binary);
    std::filebuf* pbuf = ifs.rdbuf();
    std::size_t size = pbuf->pubseekoff(0,ifs.end,ifs.in);
    pbuf->pubseekpos(0,ifs.in);
    char* buffer = new char[size];
    pbuf->sgetn(buffer,size);
    std::string bufferString(buffer,0);
    ifs.close();
    delete[] buffer;
    return bufferString;
}

WildcardEntry* newWildcardEntry(std::string path)
{
    WildcardEntry* wd = new WildcardEntry(path);
    return wd;
}

ZipEntry* newZipEntry(std::string path)
{
    ZipEntry* ze = new ZipEntry(path);
    return ze;
}

DirEntry* newDirEntry(std::string path)
{
    std::fstream _file;
    _file.open(path,std::ios::in);
    if(!_file)
    {
        std::cerr<<"Dir can not be accessed!"<<std::endl;
        std::exit(0);
    }
    DirEntry* de = new DirEntry(path);
    return de;
}

Entry* newEntry(std::string &path)
{
    if (path.find_last_of("*") == path.length() - 1)
    {
        return newWildcardEntry(path);
    }else if(path.find_last_of(".jar") == path.length() - 3 ||
             path.find_last_of(".JAR") == path.length() - 3 ||
             path.find_last_of(".zip") == path.length() - 3 ||
             path.find_last_of(".ZIP") == path.length() - 3)
    {
        return newZipEntry(path);
    }else
    {
        return newDirEntry(path);
    }
}

