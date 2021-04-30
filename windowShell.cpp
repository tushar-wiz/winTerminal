#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
using std::string;

void helpCommands(){
    std::cout << "exit -> to exit the program\n";
    std::cout << "folder +/- -> to create or delete a folder\n";
    std::cout << "path +/- -> to add or remove from the working path\n";
    std::cout << "show -> lists all the folders and files in the Directory\n";
}

void folder(string path, string query){
    path += '\\';
    path += query.substr(8);
    path += '\\';
    LPCSTR ph = path.c_str();
    if(query[7]=='+'){
        BOOL caseBOOL = CreateDirectoryA(ph,NULL);
        switch(caseBOOL){
            case ERROR_ALREADY_EXISTS:
                std::cout << "Folder already exists\n";
                break;
            case ERROR_PATH_NOT_FOUND:
                std::cout << "Wrong Path entered\n";
                break;
            default:
                std::cout << "Success\n";
                break;
        }
        return;
    }
    else if(query[7]=='-'){
        BOOL caseBOOL = RemoveDirectoryA(ph);
        if(caseBOOL == 0)
            std::cout << "Error\n";
        else
            std::cout << "Success\n";
        return;
    }
    std::cout << "ERROR\n";
    return;
}

void show(string path){
    path += "\\*.*";
    WIN32_FIND_DATAA ffd;
    HANDLE hfind;
    LPCSTR ph = path.c_str();
    hfind = FindFirstFileA(ph, &ffd);
    do{
        std::cout << ffd.cFileName << '\n';
    }while(FindNextFileA(hfind, &ffd));
    FindClose(hfind);

}

bool match(string q,string p){
    int n = p.length();

    for(int i=0;i<n;i++){
        if(p[i] != q[i])
            return false;
    }
    return true;
}

bool folderExists(string path){
    DWORD ftyp = GetFileAttributesA(path.c_str());
    if (ftyp == INVALID_FILE_ATTRIBUTES)
        return false;  //something is wrong with your path!

    if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
        return true;   // this is a directory!

    return false;    // this is not a directory!
}

string changePath(string q, string path){
    string normalPath = path;
    q = q.substr(5);
    if(q[0] == '+'){
        q = q.substr(1);
        for(int i=0;i<q.length();i++){
            if(q[i] == '/'){
                std::cout << "Use front slash \\" << '\n';
                return normalPath;
            }
        }
        path += "\\";
        path += q;
        if(folderExists(path))
            return path;
        else{
            std::cout << "Path Doesnt Exist" << '\n';
            return normalPath;
        }
    }
    else if(q[0] == '-'){
        for(int i=0;i<path.length();i++){
            if(path[i] == '\\'){
                path.erase(i);
            }
        }
        return path;
    }
    else
        return (folderExists(q))?q:normalPath;
    
    return normalPath;
}

int main(){
    string path = "C:";
    if(folderExists("D:\\")!=true){std::cout<<"BOO";};
    string query;
    while(true){
        std::cout << path << "> ";
        getline(std::cin,query);
        std::cout << '\n';
        if(match(query,"exit"))
            break;
        else if(match(query,"show"))
            show(path);
        else if(match(query,"path"))
            path = changePath(query,path);
        else if(match(query,"folder"))
            folder(path,query);
        else if(match(query,"help"))
            helpCommands();
        else
            std::cout << "Enter Valid Command\nUse help to get list of commands\n";
    }
    return 0;
}