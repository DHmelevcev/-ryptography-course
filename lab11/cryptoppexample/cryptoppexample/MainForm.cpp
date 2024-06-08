#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;

void cryptoppexample::run_process_on_file(std::string execname, std::string filename)
{
    // additional information
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    // set the size of the structures
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // start the program up
    CreateProcessA
    (
        (LPSTR)execname.c_str(),                    // the path
        (LPSTR)(execname + ' ' + filename).c_str(), // Command line
        NULL,                                       // Process handle not inheritable
        NULL,                                       // Thread handle not inheritable
        FALSE,                                      // Set handle inheritance to FALSE
        CREATE_NO_WINDOW,                           // No separate console
        NULL,                                       // Use parent's environment block
        NULL,                                       // Use parent's starting directory 
        &si,                                        // Pointer to STARTUPINFO structure
        &pi                                         // Pointer to PROCESS_INFORMATION structure
    );

    // Close process and thread handles. 
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

[STAThreadAttribute]
int main(array<String^>^ args)
{
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	cryptoppexample::MainForm form;
	Application::Run(% form);
	return 0;
}
