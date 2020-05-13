#ifndef CONNECTOR_H
#define CONNECTOR_H

#if defined(_WIN32)
    #include <windows.h>
    #include <stdio.h>
    #include <iostream>
    #include <string>

    STARTUPINFO sti = {0};
    SECURITY_ATTRIBUTES sats = {0};
    PROCESS_INFORMATION pi = {0};
    HANDLE pipin_w, pipin_r, pipout_w, pipout_r;
    BYTE buffer[2048];
    DWORD writ,available,Read,excode;

    void ConnectToEngine(char* path)
    {
        pipin_w = pipin_r = pipout_w = pipout_r = NULL;
        sats.nLength = sizeof(sats);
        sats.bInheritHandle = true;
        sats.lpSecurityDescriptor = NULL;

        CreatePipe(&pipout_r, &pipout_w, &sats, 0);
        CreatePipe(&pipin_r, &pipin_w, &sats, 0);

        sti.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
        sti.wShowWindow = SW_HIDE;
        sti.hStdInput = pipin_r;
        sti.hStdOutput = pipout_w;
        sti.hStdError = pipout_w;

        CreateProcess(NULL, path, NULL, NULL, true,0, NULL, NULL, &sti, &pi);
    }


    std::string getNextMove(const std::string position)
    {
        std::string str;
        position = "position startpos moves "+position+"\ngo\n";
        WriteFile(pipin_w, position.c_str(), position.length(),&writ, NULL);
        Sleep(500);

        PeekNamedPipe(pipout_r, buffer,sizeof(buffer), &Read, &available, NULL);
        do
        {
            ZeroMemory(buffer, sizeof(buffer));
            if(!ReadFile(pipout_r, buffer, sizeof(buffer), &Read, NULL) || !Read) break;
            buffer[Read] = 0;
            str+=(char*)buffer;
        }
        while(Read >= sizeof(buffer));

        int n = str.find("bestmove");
        std::cout<<str<<'\n';
        if (n!=-1) return str.substr(n+9,4);

        return "error";
    }

    void CloseConnection()
    {
        WriteFile(pipin_w, "quit\n", 5,&writ, NULL);
        if(pipin_w != NULL) CloseHandle(pipin_w);
        if(pipin_r != NULL) CloseHandle(pipin_r);
        if(pipout_w != NULL) CloseHandle(pipout_w);
        if(pipout_r != NULL) CloseHandle(pipout_r);
        if(pi.hProcess != NULL) CloseHandle(pi.hProcess);
        if(pi.hThread != NULL) CloseHandle(pi.hThread);
    }
#else

    #include "utils.h"
    #include <fstream>
    #include <cstdlib>
    #include <assert.h>

    std::string getNextMove(const std::string position) {
        std::ofstream fout("../donotopen/buffer.txt");
        fout << position;
        fout.close();

        if(!system("python3 donotopen/stockfish_engine.py"))
            throw EXIT_FAILURE;

        std::ifstream fin("../donotopen/buffer.txt");
        std::string s;
        fin >> s;
        fin.close();

        return s;
    }

#endif
#endif //CONNECTOR_H
