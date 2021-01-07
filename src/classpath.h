#include <string>

class Entry
{
//public:
    //Entry(std::string path);
    //~Entry();
private:
    virtual std::string readClass(std::string className);
    virtual std::string String();
};

class WildcardEntry: public Entry
{
public:
    WildcardEntry(std::string path);
    ~WildcardEntry();
private:
    std::string readClass(std::string className);
    std::string String();
};

class ZipEntry: public Entry
{
public:
    ZipEntry(std::string path);
    ~ZipEntry();
private:
    std::string readClass(std::string className);
    std::string String(){return absPath;};
    std::string absPath;
};

class DirEntry: public Entry
{
public:
    DirEntry(std::string path);
    ~DirEntry();
private:
    std::string readClass(std::string className);
    std::string String(){return absDir;};
    std::string absDir;
};

Entry* newEntry(std::string path);
WildcardEntry* newWildcardEntry(std::string path);
ZipEntry* newZipEntry(std::string path);
DirEntry* newDirEntry(std::string path);
