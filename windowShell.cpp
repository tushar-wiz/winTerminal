#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>

void show(std::string path){
    std::string add = "\\*.";
    path.append(add);
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

std::string changePath(std::string q, std::string path){
    
}

int main(){
    std::string path = "C:\\Users\\tusha";
    std::string query;
    while(true){
        std::cout << path << "> ";
        std::cin >> query;
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