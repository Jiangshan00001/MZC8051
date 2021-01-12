/// 2020.7.31 添加记录文件的方式
/// 2020.8.14 add print before createprocess
///
///
#include <assert.h>
#include <windows.h>
#include <shellapi.h>

#include "text_encode.h"
#include "myexecute.h"
#include "mylog.h"
#include "text_encode.h"

using mylog::cerr;
using mylog::cout;



int myexecute_ansi(std::string cmd_ansi, std::string param_ansi, int wait_for_finish, std::string output_file_name)
{
    std::wstring output_file_name_w = AsciiToUnicode(output_file_name);
    std::wstring param_w = AsciiToUnicode(param_ansi);
    std::wstring cmd_w = AsciiToUnicode(cmd_ansi);
    std::wstring cmd_w_with_param= cmd_w + AsciiToUnicode(std::string(" ")) + param_w;
    std::string cmd_a_with_param= cmd_ansi + (std::string(" ")) + param_ansi;




    DWORD dwShareMode=FILE_SHARE_READ|FILE_SHARE_WRITE;
#if 0
    SECURITY_ATTRIBUTES sa={sizeof ( sa ),NULL,TRUE};
    SECURITY_ATTRIBUTES *psa=NULL;
    OSVERSIONINFO osVersion={0};
    osVersion.dwOSVersionInfoSize =sizeof ( osVersion );
    if ( GetVersionEx ( &osVersion ) )
    {
        if ( osVersion.dwPlatformId ==VER_PLATFORM_WIN32_NT )
        {
        }
    }
#endif
    SECURITY_ATTRIBUTES sa={sizeof ( sa ),NULL,TRUE};
    //根据版本设置共享模式和安全属性
    // 创建记录文件
    HANDLE hConsoleRedirect=CreateFileA (
                                output_file_name.c_str(),
                                GENERIC_WRITE,
                                dwShareMode,
                                &sa,
                                OPEN_ALWAYS,
                                FILE_ATTRIBUTE_NORMAL,
                                NULL );
    assert ( hConsoleRedirect!=INVALID_HANDLE_VALUE );

    unsigned dwSize = GetFileSize (hConsoleRedirect, NULL) ;
    SetFilePointer (hConsoleRedirect, 0, NULL, FILE_END);



    STARTUPINFOA s={};
    s.cb = sizeof(s);
    PROCESS_INFORMATION pi={0};
    s.dwFlags =STARTF_USESHOWWINDOW|STARTF_USESTDHANDLES;
        //使用标准柄和显示窗口
    s.hStdOutput =hConsoleRedirect;//将文件作为标准输出句柄
    s.hStdError = hConsoleRedirect;
    s.wShowWindow =SW_HIDE;//隐藏控制台窗口

    cout<<"EXEC:"<<cmd_a_with_param<<"\n";
	DWORD exitCode=0;
    if ( CreateProcessA ( NULL,// no module name(use command line)
                        (char*)cmd_a_with_param.c_str(),//command line
                        NULL,//process handle not inheritable
                        NULL,//thread handle not inheritable
                        TRUE,// set handle inheritance to ?
                        NULL,// no creation flags
                        NULL,// use parent's environment block
                        NULL,// use parent's starting directory
                        &s, //pointer to startup info struct
                        &pi // pointer to process_information struct
                        ) )
    {
        //wait unitl child process exit
        WaitForSingleObject ( pi.hProcess ,INFINITE );
        //等待进程执行完毕
		
		

    GetExitCodeProcess(pi.hProcess, &exitCode);
        CloseHandle ( pi.hProcess );
        CloseHandle ( pi.hThread );
        //关闭进程和主线程句柄
    }
    CloseHandle ( hConsoleRedirect );
	return exitCode;
}







int myexecute_ansi_old(std::string cmd_ansi, std::string param_ansi, int wait_for_finish)
{
    std::wstring cmd_uni=AsciiToUnicode(cmd_ansi);
    std::wstring param_uni = Utf8ToUnicode(param_ansi);

    ShellExecuteW(NULL, AsciiToUnicode("open").c_str(), cmd_uni.c_str(), param_uni.c_str(),NULL, SW_SHOW );

#if 0
    std::string cmd_uni=(cmd_ansi);
    std::string param_uni = (param_ansi);

    cout<<"exec:"<<cmd_ansi<<"\n";
    cout<<"exec_param:"<<param_ansi<<"\n";


    std::string open_cmd = ("open");
    SHELLEXECUTEINFOA sei;
    memset(&sei, 0, sizeof(SHELLEXECUTEINFOA));

    sei.cbSize = sizeof(SHELLEXECUTEINFOA);
    sei.fMask = SEE_MASK_NOCLOSEPROCESS;
    sei.lpVerb =open_cmd.c_str();
    sei.lpFile = cmd_uni.c_str();
    sei.lpParameters = param_uni.c_str();
    sei.nShow = SW_SHOWDEFAULT;
    bool is_exec_success = ShellExecuteExA(&sei);

    if(!is_exec_success)
    {
        cout<<"ERROR:exec"<<"\n";
        cerr<<"ERROR:exec"<<"\n";
    }

    if(wait_for_finish)
    {
        WaitForSingleObject(sei.hProcess, INFINITE);
    }

    CloseHandle(sei.hProcess);
#endif
    return 0;
}


int myexecute(std::string cmd_utf8, std::string param_utf8, int wait_for_finish)
{
    std::wstring cmd_uni=Utf8ToUnicode(cmd_utf8);
    std::wstring param_uni = Utf8ToUnicode(param_utf8);

    cout<<"exec:"<<cmd_utf8<<"\n";
    cout<<"exec_param:"<<param_utf8<<"\n";


    std::wstring open_cmd = Utf8ToUnicode("open");
    SHELLEXECUTEINFOW sei;
    memset(&sei, 0, sizeof(SHELLEXECUTEINFOW));

    sei.cbSize = sizeof(SHELLEXECUTEINFOW);
    sei.fMask = SEE_MASK_NOCLOSEPROCESS;
    sei.lpVerb =open_cmd.c_str();
    sei.lpFile = cmd_uni.c_str();
    sei.lpParameters = param_uni.c_str();
    sei.nShow = SW_SHOWDEFAULT;
    bool is_exec_success = ShellExecuteExW(&sei);

    if(!is_exec_success)
    {
        cout<<"ERROR:exec"<<"\n";
        cerr<<"ERROR:exec"<<"\n";
    }

    if(wait_for_finish)
    {
        WaitForSingleObject(sei.hProcess, INFINITE);
    }

	DWORD exitCode;
	GetExitCodeProcess(sei.hProcess, &exitCode);
    CloseHandle(sei.hProcess);
    return exitCode;
}
