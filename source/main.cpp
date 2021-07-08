#include <windows.h>
#include <Shlobj.h>
#include <stdbool.h>
#include <string>
#include <iostream>

using namespace std;

#define APP_VER_STR (string)"v1.0.0"
#define NUM_OF_LANG_LIST 2

bool app_is_seven_zip_available = false;
bool app_is_oscdimg_available = false;
int app_lang_num = 0;
const string app_seven_zip_default_path[2] = { "C:/Program Files (x86)/7-Zip/7z", "C:/Program Files/7-Zip/7z", };
const string app_oscdimg_default_path[2] = { "C:/Program Files (x86)/Windows Kits/10/Assessment and Deployment Kit/Deployment Tools/x86/Oscdimg/Oscdimg",
"C:/Program Files (x86)/Windows Kits/10/Assessment and Deployment Kit/Deployment Tools/amd64/Oscdimg/Oscdimg", };
const string app_seven_zip_command_line[2] = { " x -y -ocache/ ", " sources/appraiserres.dll", };
const string app_oscdimg_command_line = " -m -o -u1 -bootdata:2#p0,e,bcache/boot/etfsboot.com#pEF,e,bcache/efi/Microsoft/boot/efisys.bin cache Windows11_no_tpm_2_0.iso";
string app_seven_zip_path = "N/A";
string app_oscdimg_path = "N/A";
string app_windows10_iso_path = "N/A";
string app_windows11_iso_path = "N/A";

//msg
const string app_select_lang_msg = "Select language/言語選択\nIf you want to use English, please type 'en'.\n日本語を使用したい場合、 'jp' と入力してください。\n";
const string app_lang_list[NUM_OF_LANG_LIST] = { "en", "jp", };

const string app_checking_seven_zip_msg[NUM_OF_LANG_LIST] = { "Checking if 7zip available...", "7zipが利用可能か確認中・・・", };
const string app_checking_oscdimg_msg[NUM_OF_LANG_LIST] = { "Checking if oscdimg available...", "oscdimgが利用可能か確認中・・・", };

const string app_no_seven_zip_msg[NUM_OF_LANG_LIST] = { "7zip was not found!\nDo you want to enter 7zip path manually\?\?\?(in case you've installed 7zip to a different path)[Y/N]",
"7zipが検出されませんでした！\n手動で7zipのパスを入力しますか\?\?\?(7zipを別の場所へインストールした場合)[Y/N]", };
const string app_no_oscdimg_msg[NUM_OF_LANG_LIST] = { "oscdimg was not found!\nDo you want to enter oscdimg path manually\?\?\?(in case you've installed oscdimg to a different path)[Y/N]",
"oscdimgが検出されませんでした！\n手動でoscdimgのパスを入力しますか\?\?\?(oscdimgを別の場所へインストールした場合)[Y/N]", };

const string app_seven_zip_dl_link_msg[NUM_OF_LANG_LIST] = { "You need to install 7zip.\nYou can download 7zip from : https://www.7-zip.org/download.html\n",
"7zipをインストールしなければいけません。\n以下から7zipをダウンロード可能です : https://www.7-zip.org/download.html\n", };
const string app_oscdimg_dl_link_msg[NUM_OF_LANG_LIST] = { "You need to install oscdimg.\nYou can download oscdimg from : https://go.microsoft.com/fwlink/?linkid=2165884\n",
"oscdimgをインストールしなければいけません。\n以下からoscdimgをダウンロード可能です : https://go.microsoft.com/fwlink/?linkid=2165884\n", };

const string app_ask_seven_zip_path_msg[NUM_OF_LANG_LIST] = { "Please select 7z.exe .\n", "7z.exeを選択してください。\n", };
const string app_ask_oscdimg_path_msg[NUM_OF_LANG_LIST] = { "Please select oscdimg.exe .\n", "oscdimg.exeを選択してください。\n", };
const string app_ask_win10_iso_path_msg[NUM_OF_LANG_LIST] = { "Please select windows10.iso .\n", "windows10.isoを選択してください。\n", };
const string app_ask_win11_iso_path_msg[NUM_OF_LANG_LIST] = { "Please select windows11.iso .\n", "windows11.isoを選択してください。\n", };

const string app_seven_zip_path_msg[NUM_OF_LANG_LIST] = { "7zip path : ", "7zipパス : ", };
const string app_oscdimg_path_msg[NUM_OF_LANG_LIST] = { "oscdimg path : ", "oscdimgパス : ", };
const string app_win10_iso_path_msg[NUM_OF_LANG_LIST] = { "windows10.iso path : ", "windows10.isoパス : ", };
const string app_win11_iso_path_msg[NUM_OF_LANG_LIST] = { "windows11.iso path : ", "windows11.isoパス : ", };

const string app_extracting_appraiserres_dll_from_win10_iso_msg[NUM_OF_LANG_LIST] = { "Extracting appraiserres.dll from windows10.iso...", "windows10.isoからappraiserres.dllを解凍中・・・", };
const string app_extracting_win11_iso_msg[NUM_OF_LANG_LIST] = { "Extracting windows11.iso... ", "windows11.isoを解凍中・・・", };
const string app_creating_patched_win11_iso_msg[NUM_OF_LANG_LIST] = { "Creating patched Windows11.iso... ", "改造済みwindows11.isoを作成中・・・", };
const string app_deleting_cache_msg[NUM_OF_LANG_LIST] = { "Deleting cache folder...", "cacheフォルダを削除中・・・", };

const string app_yes_msg[NUM_OF_LANG_LIST] = { "Yes\n", "はい\n", };
const string app_no_msg[NUM_OF_LANG_LIST] = { "No\n", "いいえ\n", };
const string app_done_msg[NUM_OF_LANG_LIST] = { "Done!\n", "完了！\n", };

const string app_exit_msg[NUM_OF_LANG_LIST] = { "Press any key to exit.\n\n", "何かキーを押すと終了します。\n\n", };

bool Is_app_available(const string app_full_path)
{
	STARTUPINFO startup_info;
	PROCESS_INFORMATION process_info;
	bool result = false;
	memset(&startup_info, 0x0, sizeof(startup_info));
	memset(&process_info, 0x0, sizeof(process_info));

	result = CreateProcess(NULL, (char*)app_full_path.c_str(), NULL, NULL, false, CREATE_NO_WINDOW, NULL, NULL, &startup_info, &process_info);
	WaitForSingleObject(process_info.hProcess, INFINITE);
	CloseHandle(process_info.hProcess);
	CloseHandle(process_info.hThread);

	return result;
}

void Run_app(const string app_full_path, const DWORD mode)
{
	STARTUPINFO startup_info;
	PROCESS_INFORMATION process_info;
	memset(&startup_info, 0x0, sizeof(startup_info));
	memset(&process_info, 0x0, sizeof(process_info));

	CreateProcess(NULL, (char*)app_full_path.c_str(), NULL, NULL, false, mode, NULL, NULL, &startup_info, &process_info);
	WaitForSingleObject(process_info.hProcess, INFINITE);
	CloseHandle(process_info.hProcess);
	CloseHandle(process_info.hThread);
}

bool Check_yes_or_no(const string message)
{
	while(true)
	{
		string input = "";
		cout << message;
		cin >> input;

		if(input == "Y" || input == "y")
			return true;
		else if(input == "N" || input == "n")
			return false;
	}
}

int Select_language(const string message, const string lang_list[], const int num_of_lang_list)
{
	while(true)
	{
		string input = "";
		cout << message;
		cin >> input;
		
		for(int i = 0; i < num_of_lang_list; i++)
		{
			if(lang_list[i] == input)
				return i;
		}
	}
}

string Select_file(void)
{
	BROWSEINFOA dialog;
	LPITEMIDLIST path_id;
	LPTSTR file_name = (LPTSTR)malloc(0x10000);
	string selected_path = "";

	dialog.hwndOwner = NULL;
	dialog.pidlRoot = NULL;
	dialog.ulFlags = BIF_USENEWUI | BIF_NONEWFOLDERBUTTON | BIF_BROWSEINCLUDEFILES;
	dialog.lpszTitle = "Pick a file";
	dialog.lpfn = NULL;
	dialog.lParam = 0;
	dialog.iImage = 0;

	path_id = SHBrowseForFolderA(&dialog);
	SHGetPathFromIDList(path_id, file_name); 
	selected_path = file_name;

	free(file_name);
	file_name = NULL;
	return selected_path;
}

void Delete_folder(const string dir)
{
	SHFILEOPSTRUCT shfile_data = { NULL, FO_DELETE, (char*)(dir + "\0").c_str(), "", FOF_NOCONFIRMATION, false, 0, "", };
	SHFileOperation(&shfile_data);
}

void Init()
{
	CONSOLE_FONT_INFOEX font_info;
    font_info.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    font_info.dwFontSize.X = 16;
    font_info.dwFontSize.Y = 16;
	font_info.FontWeight = FW_NORMAL;
    font_info.FontFamily = TMPF_TRUETYPE;
	wcscpy(font_info.FaceName, L"SimSun-ExtB");

	cout << "Windows11 no tpm iso maker " + APP_VER_STR + "\n";
	cout << (SetConsoleOutputCP(CP_UTF8) ? "" : "SetConsoleOutputCP() failed.\n");
	cout << (SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &font_info) ? "" : "SetCurrentConsoleFontEx() failed.\n");
}

int main()
{
	Init();

	app_lang_num = Select_language(app_select_lang_msg, app_lang_list, NUM_OF_LANG_LIST);

	cout << app_checking_seven_zip_msg[app_lang_num];
	if(Is_app_available(app_seven_zip_default_path[0]))
	{
		app_seven_zip_path = app_seven_zip_default_path[0];
		app_is_seven_zip_available = true;
	}
	else if(Is_app_available(app_seven_zip_default_path[1]))
	{
		app_seven_zip_path = app_seven_zip_default_path[1];
		app_is_seven_zip_available = true;
	}
	cout << (app_is_seven_zip_available ? app_yes_msg[app_lang_num] : app_no_msg[app_lang_num]);

	cout << app_checking_oscdimg_msg[app_lang_num];
	if(Is_app_available(app_oscdimg_default_path[0]))
	{
		app_oscdimg_path = app_oscdimg_default_path[0];
		app_is_oscdimg_available = true;
	}
	else if(Is_app_available(app_oscdimg_default_path[1]))
	{
		app_oscdimg_path = app_oscdimg_default_path[1];
		app_is_oscdimg_available = true;
	}
	cout << (app_is_oscdimg_available ? app_yes_msg[app_lang_num] : app_no_msg[app_lang_num]);

	while(!app_is_seven_zip_available)
	{
		if(Check_yes_or_no(app_no_seven_zip_msg[app_lang_num]))
		{
			cout << app_ask_seven_zip_path_msg[app_lang_num];
			app_seven_zip_path = Select_file();
			if(Is_app_available(app_seven_zip_path))
			{
				app_is_seven_zip_available = true;
				break;
			}
			else
				app_seven_zip_path = "";
		}
		else
		{
			cout << app_seven_zip_dl_link_msg;
			break;
		}
	}

	while(!app_is_oscdimg_available)
	{
		if(Check_yes_or_no(app_no_oscdimg_msg[app_lang_num]))
		{
			cout << app_ask_oscdimg_path_msg[app_lang_num];
			app_oscdimg_path = Select_file();
			if(Is_app_available(app_oscdimg_path))
			{
				app_is_oscdimg_available = true;
				break;
			}
			else
				app_oscdimg_path = "";
		}
		else
		{
			cout << app_oscdimg_dl_link_msg[app_lang_num];
			break;
		}
	}

	cout << app_seven_zip_path_msg[app_lang_num] + app_seven_zip_path << endl;
	cout << app_oscdimg_path_msg[app_lang_num] + app_oscdimg_path << endl;

	if(app_is_seven_zip_available && app_is_oscdimg_available)
	{
		cout << app_ask_win10_iso_path_msg[app_lang_num];
		app_windows10_iso_path = Select_file();
		cout << app_ask_win11_iso_path_msg[app_lang_num];
		app_windows11_iso_path = Select_file();

		cout << app_win10_iso_path_msg[app_lang_num] << app_windows10_iso_path << endl;
		cout << app_win11_iso_path_msg[app_lang_num] << app_windows11_iso_path << endl << endl;

		cout << app_extracting_win11_iso_msg[app_lang_num];
		Run_app(app_seven_zip_path + app_seven_zip_command_line[0] + app_windows11_iso_path, CREATE_NEW_CONSOLE);
		cout << app_done_msg[app_lang_num];

		cout << app_extracting_appraiserres_dll_from_win10_iso_msg[app_lang_num];
		Run_app(app_seven_zip_path + app_seven_zip_command_line[0] + app_windows10_iso_path + app_seven_zip_command_line[1], CREATE_NEW_CONSOLE);
		cout << app_done_msg[app_lang_num];

		cout << app_creating_patched_win11_iso_msg[app_lang_num];
		Run_app(app_oscdimg_path + app_oscdimg_command_line, CREATE_NEW_CONSOLE);
		cout << app_done_msg[app_lang_num];

		cout << app_deleting_cache_msg[app_lang_num];
		Delete_folder("cache/");
		cout << app_done_msg[app_lang_num];
	}

	cout << app_exit_msg[app_lang_num];
	Run_app("cmd /K pause > nul && exit", 0);

	return 0;
}