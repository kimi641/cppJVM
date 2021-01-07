#define ZIP_STD
#include <iostream>
#include "zlib.h"
#include "unzip.h"

using namespace std;

int main(int argc, char* argv[])
{
    HZIP hz = OpenZip("sample.zip",0);
    ZIPENTRY ze;
    int i;
    FindZipItem(hz,"a.txt",true,&i,&ze);
    char* ibuf = new char[ze.unc_size];
    UnzipItem(hz,i,ibuf,ze.unc_size);
    cout<<ibuf<<endl;
    delete[] ibuf;
    CloseZip(hz);
    return 0;
}
