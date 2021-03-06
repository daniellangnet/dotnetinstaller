#include "StdAfx.h"
#include "ShellUtilUnitTests.h"

using namespace DVLib::UnitTests;

CPPUNIT_TEST_SUITE_REGISTRATION(ShellUtilUnitTests);

void ShellUtilUnitTests::testGetEnvironmentVariable()
{
	wchar_t computername_s[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD computername_size = ARRAYSIZE(computername_s);
	CPPUNIT_ASSERT(::GetComputerNameW(computername_s, & computername_size));
	std::wstring computername = DVLib::GetEnvironmentVariable(L"COMPUTERNAME");
	std::wcout << std::endl << L"Computer name: " << computername;
	CPPUNIT_ASSERT(computername.length() > 0);
	CPPUNIT_ASSERT(computername.length() == wcslen(computername.c_str()));
	CPPUNIT_ASSERT(computername == computername_s);
}

void ShellUtilUnitTests::testExpandEnvironmentVariables()
{
	CPPUNIT_ASSERT(DVLib::ExpandEnvironmentVariables(L"") == L"");
	CPPUNIT_ASSERT(DVLib::ExpandEnvironmentVariables(L"%%") == L"%%");
	CPPUNIT_ASSERT(DVLib::ExpandEnvironmentVariables(L"%%%") == L"%%%");
	CPPUNIT_ASSERT(DVLib::ExpandEnvironmentVariables(L"%" + DVLib::GenerateGUIDStringW() + L"%") == L"");
	CPPUNIT_ASSERT(DVLib::ExpandEnvironmentVariables(L"%COMPUTERNAME%") == DVLib::GetEnvironmentVariableW(L"COMPUTERNAME"));
	CPPUNIT_ASSERT(DVLib::ExpandEnvironmentVariables(L"%COMPUTERNAME%%COMPUTERNAME%") == DVLib::GetEnvironmentVariableW(L"COMPUTERNAME") + DVLib::GetEnvironmentVariableW(L"COMPUTERNAME"));
	CPPUNIT_ASSERT(DVLib::ExpandEnvironmentVariables(L"%COMPUTERNAME") == L"%COMPUTERNAME");
	CPPUNIT_ASSERT(DVLib::ExpandEnvironmentVariables(L"COMPUTERNAME%") == L"COMPUTERNAME%");
	CPPUNIT_ASSERT(DVLib::ExpandEnvironmentVariables(L"{%COMPUTERNAME%}") == L"{" + DVLib::GetEnvironmentVariableW(L"COMPUTERNAME") + L"}");
}

void ShellUtilUnitTests::testDetachCmd()
{
	// test timer runs for 2 seconds
	std::wstring testTimerExe = DVLib::DirectoryCombine(
#ifdef DEBUG
		DVLib::GetModuleDirectoryW(), L"..\\..\\TestTimer\\bin\\Debug\\TestTimer.exe"
#else
		DVLib::GetModuleDirectoryW(), L"..\\..\\TestTimer\\bin\\Release\\TestTimer.exe"
#endif
		);
	CPPUNIT_ASSERT(DVLib::FileExists(testTimerExe));
	// detach without pi
	DWORD c1 = ::GetTickCount();
	DVLib::DetachCmd(testTimerExe);
	CPPUNIT_ASSERT((::GetTickCount() - c1) < 2 * 1000);
	// run with process information
	PROCESS_INFORMATION pi = { 0 };
	DWORD c2 = ::GetTickCount();
	DVLib::DetachCmd(testTimerExe, & pi);
	auto_handle pi_thread(pi.hThread);
	auto_handle pi_process(pi.hProcess);
	CPPUNIT_ASSERT(pi.dwProcessId > 0);
	CPPUNIT_ASSERT((::GetTickCount() - c2) < 2 * 1000);
}

void ShellUtilUnitTests::testRunCmd()
{
	// run without pi
	DVLib::RunCmd(L"cmd.exe /C exit /b 0");
	// with process information
	PROCESS_INFORMATION pi = { 0 };
	DVLib::RunCmd(L"cmd.exe /C exit /b 0", & pi);
	auto_handle pi_thread(pi.hThread);
	auto_handle pi_process(pi.hProcess);
	CPPUNIT_ASSERT(pi.dwProcessId > 0);
	CPPUNIT_ASSERT(WAIT_OBJECT_0 == ::WaitForSingleObject(pi.hProcess, INFINITE));
}

void ShellUtilUnitTests::testExecCmd()
{
	CPPUNIT_ASSERT(0 == DVLib::ExecCmd(L"cmd.exe /C"));
	CPPUNIT_ASSERT(123 == DVLib::ExecCmd(L"cmd.exe /C exit /b 123"));
}

void ShellUtilUnitTests::testShellCmd()
{
	DVLib::ShellCmd(L"cmd.exe /C");
	DVLib::ShellCmd(L"\"" + DVLib::GetEnvironmentVariable(L"SystemRoot") + L"\\system32\\cmd.exe\" /C");
	DVLib::ShellCmd(L"\"cmd.exe\" /C dir");
}