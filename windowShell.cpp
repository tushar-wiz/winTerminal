#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>

void show(std::string path){
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

bool match(std::string q,std::string p){
    int n = p.length();

    for(int i=0;i<n;i++){
        if(p[i] != q[i])
            return false;
    }
    return true;
}

bool fileExists(std::string path){
    WIN32_FIND_DATAA ffd;
    LPCSTR ph = path.c_str();
    if(FindFirstFileA(ph,&ffd) == INVALID_HANDLE_VALUE){
        return false;
    }
    return true;
}

std::string changePath(std::string q, std::string path){
    std::string normalPath = path;
    q = q.substr(5);
    if(q[0] == '+'){
        q = q.substr(1);
        path += "\\";
        path += q;
        if(fileExists(path)){
            return path;
        }
        else{
            std::cout << "Path Doesnt Exist" << '\n';
            return normalPath;
        }
    }
    else if(q[0] == '-'){
        q = q.substr(1);
        int slashCount = 1;
        for(int i=0;i<q.length();i++) (q[i]=='\\')?slashCount++:NULL;

    }

}

int main(){
    std::string path = "C:";
    std::string query;
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
    }
    return 0;
}