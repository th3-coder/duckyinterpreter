#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <limits>
#include <vector>
//#include <algorithm>

using std::cout; using std::fstream; using std::string; using std::cin; using std::ios;
using std::endl; using std::vector;

//declare functions
void CheckKeys(string file, bool &bisString, int &isString, int &isComment, int &attackMode);
void FormatString(string file, unsigned char key, bool shift, bool ctrl);
void ChangeMode(string file, unsigned char key, bool &bisString, int &isString, int &isComment, bool ctrl, bool shift, bool alt);
void InitialDelay(string file);
void SpecialKeys(string file, unsigned char key, int &counter);
bool ChangeAttackMode(string file, unsigned char &key, int &attackMode);
bool PasteText(string file, unsigned char key, bool ctrl);
void CleanPayload(string file);
void DeleteKey(string file);
bool AddDelay(string file, unsigned char key);
bool DeleteLine(string file);

//global variables

int main() {
    fstream fout;
    //declare variables
    bool bisString = false;
    int isString = 0;
    int isComment = 0;
    int attackMode = 0;

    string fileNumber;
    //cout << "Warning !!!: Working on adding backspaces be careful when deleting empty space (non characters)" << endl << endl;
    cout << "Enter file number: ";
    cin >> fileNumber;
    string file = "payload" + fileNumber + ".dd";
    //delete old file
    string deleteOld = "del " + file;
    
    cout << "Deleting old file . . ." << endl << endl;
    system(deleteOld.c_str());

    cout << "--------------------------------- KEY FUNCTIONS ------------------------------------" << endl;
    cout << "Auto Begin String: Any character A-Z" << endl << "End String:" << endl  
         << "\t--Return    --CTRL+RETURN    --SHIFT+RETURN    --CTRL+SHIFT+RETURN" << endl << endl 
         << "Manual String (use to paste contents): F2" << endl
         << "\tStart String (F2) -> Paste Contents (CTRL+V) -> Stop String (F2)" << endl 
         << "\tOR" << endl << "\tStart autostring and back space until empty string then paste" << endl << endl
         << "Start/Stop Comment: F4" << endl << endl
         << "Manual Delay: NUMLOCK + ARROW" << endl
         << "\t\tLEFT:  300ms" << endl << "\t\tUP:    600ms" << endl << "\t\tRIGHT: 1,500ms" << endl << "\t\tDOWN:  3,000ms" << endl << endl
         << "Change Attack Mode (HID/STORAGE): F9"  << endl << endl
         << "Delete Previous Line: NUMLOCK+BACKSPACE" << endl;
    cout << "-------------------------------------------------------------------------------------" << endl << endl;
    //call main function
    cout << "Keylogger started, will be saved to " << file << endl << endl;
    cout << ". . . X_X Press ALT+ESCAPE to exit X_X . . ." << endl
         << "        *CANNOT EXIT IN STRING MODE*" << endl << endl;
    cout << "\t- - - Start of File - - -" << endl;
    Sleep(100);
    CheckKeys(file, bisString, isString, isComment, attackMode);

    cout << endl << endl;
    cout << "\t    ^o^ Cleaning up file ^o^" << endl << endl;
    //call function to remove last line in payload.txt
    cout << "\t- - - FORMATTED DUCKY CODE - - -" << endl << endl << endl;
    CleanPayload(file);
    cout << endl << endl << "\t - - - END OF DUCKY CODE - - -";
    //program finished
    cout << endl << "\nLogger finished, saved in " << file << " in Rubber DUCKY format ^_~" << endl << endl;
    cout << "Press X to continue" << endl;
    while(true)
    {
        if(GetAsyncKeyState(0x58) & 0x8000)
        {
            return 0;
        }
    }
}
// main loop which checks if any key is pressed 
void CheckKeys(string file, bool &bisString, int &isString, int &isComment, int &attackMode) {
    //open file
    fstream fout;
    fout.open(file.c_str(), ios::app);
    if(!fout) {
        cout << "Error opening file" << endl;
        return;
    }

    //declare variables
    bool isPressed = false;
    bool keyState[256] = {false};
    bool bAttackMode = true;
    unsigned char key;
    int counter = 0;
    string keydelay = "DELAY 300";

    //initial delay of 3 seconds
    InitialDelay(file);

    while(true)
    {
        Sleep(50); //sleep for 100ms to prevent high CPU usage
        for(key = 8; key <= 255; key++)
        {
            isPressed = (GetAsyncKeyState(key) & 0x8000);

            if(isPressed && !keyState[key])
            {
                keyState[key] = true;
                
                //cout << endl << isString << endl;
                bool ctrl = GetAsyncKeyState(VK_CONTROL) & 0x8000;
                bool shift = GetAsyncKeyState(VK_SHIFT) & 0x8000;
                bool alt = GetAsyncKeyState(VK_MENU) & 0x8000;
                
                //find key ASCII value
                //cout << int(key);
                
                fout.close();
                //cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                if(AddDelay(file, key))
                {
                    break;
                }
                
                //fout.close();
                ChangeMode(file, key, bisString, isString, isComment, ctrl, shift, alt);
                
                //bAttackMode = ChangeAttackMode(file, key, attackMode);

                if(!ChangeAttackMode(file, key, attackMode))
                {
                    break;
                }

                fout.open(file.c_str(), ios::app);
                if(!fout) {
                    cout << "Error opening file" << endl;
                    return;
                }

                if(!bisString)
                {
                    //main keys (when these 4 keys are released it will create a new line)
                    if(ctrl && key == 0x11)
                    {
                        fout << "CTRL ";
                        cout << "CTRL ";
                        counter = 0; //reset ctrl
                    }
                    if(shift && key == 0x10)
                    {
                        fout << "SHIFT ";
                        cout << "SHIFT ";
                        counter = 0;
                    }
                    if(alt && key == 0x12)
                    {
                        fout << "ALT ";
                        cout << "ALT ";
                        counter = 0;
                    }
                    if(key == VK_LWIN)
                    {
                        fout << "GUI ";
                        cout << "GUI ";
                        counter = 0;
                    }
                    //if statements to check all special keys
                    //close file
                    fout.close();
                    
                    SpecialKeys(file, key, counter);
                    
                    fout.open(file.c_str(), ios::app);
                    if(!fout) {
                        cout << "Error opening file" << endl;
                        return;
                    }

                    if(key >= 0x30 && key <= 0x39)
                    {
                        fout << key << " ";
                        cout << key << " ";
                    }
                    else if (key >= 0x41 && key <= 0x5A)
                    {
                            fout << char(key) << " ";
                            cout << char(key) << " ";       
                    }
                }
                else //call format string function
                {
                    fout.close();
                    FormatString(file, key, shift, ctrl);
                    fout.open(file.c_str());
                    if(!fout){
                        cout << "Error opening file";
                        return;
                    }
                }
                //exit program if ALT+ESC is pressed
                if(key == 0x1B && GetAsyncKeyState(VK_MENU) & 0x8000){
                    fout.close();
                    return;
                }
            }
            
            if(!isPressed && keyState[key]){
                keyState[key] = false;
                if(key > 159 && key < 224 || key == VK_LWIN || key == VK_RETURN || key == VK_SPACE || key == VK_TAB || key == VK_ESCAPE || key == VK_UP || key == VK_DOWN || key == VK_LEFT || key == VK_RIGHT){
                    // cout << " - - - released";
                    if(counter == 0 && !bisString){
                    cout << endl;
                    fout << endl;
                    cout << keydelay << endl;
                    fout << keydelay << endl;
                    counter++;
                    }
                }
            } 
        }
    }
    return;
}
// begins/ends when ALT + 1 is pressed
void FormatString(string file, unsigned char key, bool shift, bool ctrl){
    //declare variables
    string stringdelay = "DELAY 900";

    //open file
    fstream fout;

    if(PasteText(file, key, ctrl))
    {
        return;
    }
    //open file
    fout.open(file.c_str(), ios::app);
    if(!fout){
        cout << "Error opening file";
        return;
    }
    if(!shift)
    {
        switch(key) 
        {
            //windows control keys
            case VK_BACK: fout.close(); DeleteKey(file); fout.open(file.c_str()); cout << "\b"; break;
            case VK_TAB: fout << "\t"; cout << "\t"; break;
            case VK_RETURN: fout << endl << stringdelay << endl << "ENTER" << endl
                                 << stringdelay << endl << "STRING ";
                            cout << endl << stringdelay << endl << "ENTER" << endl
                                 << stringdelay << endl << "STRING "; break;
            //special characters
            case 0xBC: fout << ","; cout << ","; break;
            case VK_OEM_PERIOD: fout << "."; cout << "."; break;
            case VK_OEM_1: fout << ";"; cout << ";"; break;
            case VK_OEM_2: fout << "/"; cout << ";"; break;                        
            case VK_OEM_3: fout << "`"; cout << "`"; break; //top left corner of keyboard
            case VK_OEM_4: fout << "["; cout << "["; break;
            case VK_OEM_6: fout << "]"; cout << "]"; break;
            case VK_OEM_5: fout << "\\"; cout << "\\"; break;
            case VK_OEM_7: fout << "'"; cout << "'"; break;
            case VK_SPACE: fout << " "; cout << " "; break;
            
            //F 1-12 keys and numpad keys`
            case VK_NUMPAD0: fout << "0"; cout << "0"; break;
            case VK_NUMPAD1: fout << "1"; cout << "1"; break;
            case VK_NUMPAD2: fout << "2"; cout << "2"; break;
            case VK_NUMPAD3: fout << "3"; cout << "3"; break;
            case VK_NUMPAD4: fout << "4"; cout << "4"; break;
            case VK_NUMPAD5: fout << "5"; cout << "5"; break;
            case VK_NUMPAD6: fout << "6"; cout << "6"; break;
            case VK_NUMPAD7: fout << "7"; cout << "7"; break;
            case VK_NUMPAD8: fout << "8"; cout << "8"; break;
            case VK_NUMPAD9: fout << "9"; cout << "9"; break;
            case VK_MULTIPLY: fout << "*"; cout << "*"; break;
            case VK_ADD: fout << "+"; cout << "+"; break;
            case VK_SUBTRACT: fout << "-"; cout << "-"; break;
            case VK_DECIMAL: fout << "."; cout << "."; break;
            case VK_DIVIDE: fout << "/"; cout << "/"; break;
            case 0xBB: fout << "="; cout << "="; break;
            case 0xBD: fout << "-"; cout << "-"; break;     
        }
    }
    else
    {
        switch(key) 
        {
            //windows control keys
            case VK_BACK: fout.close(); DeleteKey(file); fout.open(file.c_str()); cout << "\b"; break;
            case VK_TAB: fout << "\t"; cout << "\t"; break;
            case VK_RETURN: fout << "\n" << stringdelay << endl << "STRING ";
                            cout << "\n" << stringdelay << endl << "STRING "; break;
            //special characters
            case 0xBC: fout << "<"; cout << "<"; break;
            case VK_OEM_PERIOD: fout << ">"; cout << ">"; break;
            case VK_OEM_1: fout << ":"; cout << ":"; break;
            case VK_OEM_2: fout << "?"; cout << "?"; break;                        
            case VK_OEM_3: fout << "~"; cout << "~"; break; //top left corner of keyboard
            case VK_OEM_4: fout << "{"; cout << "{"; break;
            case VK_OEM_6: fout << "}"; cout << "}"; break;
            case VK_OEM_5: fout << "|"; cout << "|"; break;
            case VK_OEM_7: fout << "\""; cout << "\""; break;
            case VK_SPACE: fout << " "; cout << " "; break;
            
            //F 1-12 keys and numpad keys`
            case VK_NUMPAD0: fout << ")"; cout << ")"; break;
            case VK_NUMPAD1: fout << "!"; cout << "!"; break;
            case VK_NUMPAD2: fout << "@"; cout << "@"; break;
            case VK_NUMPAD3: fout << "#"; cout << "#"; break;
            case VK_NUMPAD4: fout << "$"; cout << "$"; break;
            case VK_NUMPAD5: fout << "%"; cout << "%"; break;
            case VK_NUMPAD6: fout << "^"; cout << "^"; break;
            case VK_NUMPAD7: fout << "&"; cout << "&"; break;
            case VK_NUMPAD8: fout << "*"; cout << "*"; break;
            case VK_NUMPAD9: fout << "("; cout << "("; break;
            case VK_MULTIPLY: fout << "*"; cout << "*"; break;
            case VK_ADD: fout << "+"; cout << "+"; break;
            case VK_SUBTRACT: fout << "-"; cout << "-"; break;
            case VK_DECIMAL: fout << "."; cout << "."; break;
            case VK_DIVIDE: fout << "/"; cout << "/"; break;
            case 0xBB: fout << "+"; cout << "+"; break;
            case 0xBD: fout << "_"; cout << "_"; break;     
        }
    }
    if(key >= 0x30 && key <= 0x39)
    {
        if(!shift)
        {
        cout << key;
        fout << key;
        }
        else
        {
            switch(key)
            {
                case 0x30: fout << ")"; cout << ")"; break;
                case 0x31: fout << "!"; cout << "!"; break;
                case 0x32: fout << "@"; cout << "@"; break;
                case 0x33: fout << "#"; cout << "#"; break;
                case 0x34: fout << "$"; cout << "$"; break;
                case 0x35: fout << "%"; cout << "%"; break;
                case 0x36: fout << "^"; cout << "^"; break;
                case 0x37: fout << "&"; cout << "&"; break;
                case 0x38: fout << "*"; cout << "*"; break;
                case 0x39: fout << "("; cout << "("; break;
            } 
        }
    }
    else if (key >= 0x41 && key <= 0x5A)
    {
        if(shift){
            cout << char(key);
            fout << char(key);
        }
        else{
            cout << char(key+32);
            fout << char(key+32);
        }       
    }
    fout.close();
    return;
}
// change between HID, STRING, and comments
void ChangeMode(string file, unsigned char key, bool &bisString, int &isString, int &isComment, bool ctrl, bool shift, bool alt){
    fstream fout;
    fout.open(file.c_str(), ios::app); //ios::app used to append to file
    if(!fout) {
        cout << endl << "Error opening file" << endl;
        return;
    }

    string stringdelay = "DELAY 1200";

    // start string using shortcut key
    if(key == 0x71) //if F2 is pressed a string command starts/ends
    {
        if(isString == 1){
            //starts a string command in ducky language
            bisString = true;
            cout << stringdelay << endl << "STRING ";
            fout << stringdelay << endl << "STRING ";
            isString = 2;
        }
        else {
            //ends a string command in ducky language
            bisString = false;
            isString = 1;
            cout << endl;
            cout << "DELAY 600" << endl;
            fout << endl;
            fout << "DELAY 600" << endl;
        }
    }
   
   //auto string begin/end
    if((key >= 0x41 && key <= 0x5A && !bisString && !ctrl && !shift && !alt && !(GetAsyncKeyState(VK_LWIN) & 0x8000)))
    {
        //starts a string command in ducky language
        if(isString == 0)
        {
            fout << endl << "$_JITTER_ENABLED = TRUE\n\n";
            cout << endl << "$_JITTER_ENABLED = TRUE\n\n";
            //this is a DUCKY function which sets small delay between typing each char
            // in stringln statement
        }
        if(isString == 1 || isString == 0 || isString == 2){
            bisString = true;
            cout << stringdelay << endl << "STRING ";
            fout << stringdelay << endl << "STRING ";
        }
        isString++;
    }
    else if((ctrl || shift || alt) && bisString){
        bool enter = (GetAsyncKeyState(VK_RETURN) & 0x8000);
        int i = 0;
        if(ctrl){
            if(enter){
                cout << endl << stringdelay << endl;
                fout << endl << stringdelay << endl;
                cout << "CTRL ";
                fout << "CTRL ";
                bisString = false;
                i++;
                isString = 1;
            }
            }

        if(shift){
            if(enter){
                if(i == 0)
                {
                    cout << endl << stringdelay << endl;
                    fout << endl << stringdelay << endl;
                }
                cout << "SHIFT ";
                fout << "SHIFT ";
                i++;
                bisString = false;
                isString = 1;
            }
        }
        if(alt){
            if(enter){
                if(i == 0)
                {
                    cout << endl << stringdelay << endl;
                    fout << endl << stringdelay << endl;
                }
                cout << "ALT ";
                fout << "ALT ";
                i++;
                bisString = false;
                isString = 1;
            }
        }
        if(key == VK_RETURN){
            if(i == 0){
                cout << endl << stringdelay << endl;
                fout << endl << stringdelay << endl;
            }
            bisString = false;
            isString = 1;
        }
    }
    else if(key == VK_RETURN && bisString){
        bisString = false;
        cout << endl << stringdelay << endl;
        fout << endl << stringdelay << endl;
        isString = 1;
        }

    if(key == 0x73){ //if F4 is pressed a comment starts/ends
        if(isComment % 2 == 0){
            //starts a comment in ducky language
            bisString = true;
            cout << "REM ";
            fout << "REM ";
        }
        else {
            //ends a comment in ducky language
            bisString = false;
            cout << endl;
            fout << endl;
        }
        isComment++;
    }
    fout.close();
    return;
}
// adds initial delay of 3 seconds
void InitialDelay(string file){
    fstream fout;
    fout.open(file.c_str(), ios::app);
    if(!fout){
        cout << "Error opening file";
        return;
    }

    fout << "DELAY 3000" << endl;
    cout << "DELAY 3000" << endl;
    fout.close();
    return; 
}
// checks all special characters (comma, semicolon, slashes)
void SpecialKeys(string file, unsigned char key, int &counter){
    fstream fout;
    //open file
    fout.open(file.c_str(), ios::app);
    if(!fout){
        cout << endl << "Error opening file" << endl;
        return;
    }
    //check all special keys individually (multiple may be pressed at once)
    if(key == VK_BACK){
        fout << "BACKSPACE ";
        cout << "BACKSPACE ";
    }
    if(key == VK_TAB){
        fout << "TAB ";
        cout << "TAB ";
    }
    if(key == VK_RETURN){
        fout << "ENTER ";
        cout << "ENTER ";
    }
    if(key == VK_CAPITAL){
        fout << "CAPSLOCK ";
        cout << "CAPSLOCK ";
    }
    if(key == VK_ESCAPE){
        fout << "ESCAPE ";
        cout << "ESCAPE ";
    }
    if(key == 0xBC){
        fout << "COMMA ";
        cout << "COMMA ";
    }
    if(key == VK_OEM_PERIOD){
        fout << "PERIOD ";
        cout << "PERIOD ";
    }
    if(key == VK_OEM_1){
        fout << "SEMICOLON ";
        cout << "SEMICOLON ";
    }
    if(key == VK_OEM_2){
        fout << "BACKSLASH ";
        cout << "BACKSLASH ";
    }
    if(key == VK_OEM_3){
        fout << "TILDE ";
        cout << "TILDE ";
    }
    if(key == VK_OEM_4){
        fout << "LEFTBRACKET ";
        cout << "LEFTBRACKET ";
    }
    if(key == VK_OEM_5){
        fout << "FORWARDSLASH ";
        cout << "FORWARDSLASH ";
    }
    if(key == VK_OEM_6){
        fout << "RIGHTBRACKET ";
        cout << "RIGHTBRACKET ";
    }
    if(key == VK_OEM_7){
        fout << "QUOTE ";
        cout << "QUOTE ";
    }
    if(key == VK_SPACE){
        fout << "SPACE ";
        cout << "SPACE ";
    }
    if(key == VK_LEFT){
        fout << "LEFT ";
        cout << "LEFT ";
    }
    if(key == VK_RIGHT){
        fout << "RIGHT ";
        cout << "RIGHT ";
    }
    if(key == VK_UP){
        fout << "UP ";
        cout << "UP ";
    }
    if(key == VK_DOWN){
        fout << "DOWN ";
        cout << "DOWN ";
    }
    if(key == VK_INSERT){
        fout << "INSERT ";
        cout << "INSERT ";
    }
    if(key == VK_HOME){
        fout << "HOME ";
        cout << "HOME ";
    }
    if(key == VK_END){
        fout << "END ";
        cout << "END ";
    }
    if(key == VK_PRIOR){
        fout << "PAGEUP ";
        cout << "PAGEUP ";
    }
    if(key == VK_NEXT){
        fout << "PAGEDOWN ";
        cout << "PAGEDOWN ";
    }
    if(key == 0xBB){
        cout << "+ ";
        fout << "+" ;
    }
    if(key == 0xBD){
        fout << "- ";
        cout << "- ";
    }

    counter = 0;
    fout.close();
    return;
}
// change attack mode - HID or HID STORAGE
bool ChangeAttackMode(string file, unsigned char &key, int &attackMode){

    fstream fout;
    fout.open(file.c_str(), ios::app);
    if(!fout){
        cout << endl << "Error opening file" << endl;
        return true;
    }

    //F9 to change attack mode of RUBBER DUCKY
    if(key == 0x78){
        if(attackMode % 2 == 0){
            cout << endl << "ATTACKMODE HID\n\n";
            fout << endl << "ATTACKMODE HID\n\n";
            attackMode++;
            return true;
        }
        else {
            string delay = "DELAY 600";
            
            cout << endl << "ATTACKMODE HID STORAGE" << endl << endl;
            fout << endl << "ATTACKMODE HID STORAGE" << endl << endl;
            //opens powershell in code and on machine in DUCKY filesystem 
            // can use \Ducky: as drive letter
            // transfer from ducky to machine or vice versa using cp
            // run scripts directly on ducky using elevated commands
            // python script.py, ./script.exe, etc. 
            ShellExecute
                ( NULL,
                "runas",
                "powershell.exe",
                    "-NoExit -Command \"cd \\; $Ducky = $DriveLetter = Get-Volume -FileSystemLabel 'DUCKY' | % DriveLetter \"",
                NULL,
                SW_SHOWNORMAL);
                
            fout << endl << "REM Admin Powershell instance created in DUCKY script and on current machine" << endl << endl
            << "GUI R" << endl << delay << endl
            << "STRING powershell" << endl << delay << endl
            << "CTRL SHIFT ENTER" << endl << delay << endl
            << "ALT Y" << endl << delay << endl
            << "STRING cd \\" << endl << delay << endl
            << "ENTER" << endl << delay << endl
            << "STRING $Ducky = Get-Volume -FileSystemLabel 'DUCKY' | % DriveLetter" << endl
            << "ENTER" << endl << delay << endl;
                        
            cout << endl << "REM Admin Powershell instance created in DUCKY script and on current machine" << endl << endl
            << "GUI R" << endl << delay << endl
            << "STRING powershell" << endl << delay << endl
            << "CTRL SHIFT ENTER" << endl << delay << endl
            << "ALT Y" << endl << delay << endl
            << "STRING cd \\" << endl << delay << endl
            << "ENTER" << endl << delay << endl
            << "STRING $Ducky = Get-Volume -FileSystemLabel 'DUCKY' | % DriveLetter" << endl
            << "ENTER" << endl << delay << endl;

            cout << endl << endl << "REM\t - - -Admin powershell opened  on current machine and in DUCKY script - - -"
                 << endl << "\tUse \"cd ${Ducky}:\" to change to DUCKY drive and run custom scripts" << endl
                 << "REM\t\t\tor" << endl
                 << "REM\tcopy files directly to ducky using \"cp file.txt ${Ducky}:\\PremadeDataFolder\""
                 << endl << endl;
            attackMode++;
                 return false;
        }
    }
    fout.close();
    return true;
}
// paste copied text
bool PasteText(string file, unsigned char key, bool ctrl){
    if(key == 0x56 && ctrl){
        fstream fout;
        fout.open(file.c_str(), ios::app);
        if(!fout){
            cout << "Error opening file";
            return false;
        }
        if (!OpenClipboard(NULL)) {
            cout << "Error opening clipboard." << endl;
            fout.close();
            return false;
        }

        HANDLE hClipboardData = GetClipboardData(CF_TEXT);
        if (hClipboardData == NULL) {
            cout << "Error getting clipboard data." << endl;
            CloseClipboard();
            fout.close();
            return false;
        }

        char* pszText = static_cast<char*>(GlobalLock(hClipboardData));
        if (pszText == NULL) {
            cout << "Error locking global memory." << endl;
            CloseClipboard();
            fout.close();
            return false;
        }

        string text(pszText);

        GlobalUnlock(hClipboardData);
        CloseClipboard();

        fout << text;
        cout << text;
        fout.close();
        return true;
        }
    else if(key == 0x43 && ctrl)
        return true;
    else if(key == 0x41 && ctrl)
        return true;
        
    else{
    return false;
    }
}
// cleans any errors made in transcription of keys (last escape character)
void CleanPayload(string file){
    fstream fin;
    fstream fout;
    //declare variables
    vector<string> contents;
    string content;
    int i = 0;

    fin.open(file.c_str());
    if(!fin){
        cout << endl << endl << "Error opening file" << endl;
        return;
    }
    //add current text file to vector for transfer

    while(getline(fin, content)){
        contents.push_back(content);
        //contents[i-1] = content;
        i++;
    } 
    fin.close();

    //replace file with contents vector (old file minus last line)
    fout.open(file.c_str(), ios::out | ios::trunc);
    if(!fout){
        cout << "Error opening file" << endl;
        return;
    }
    for(int j = 0; j < contents.size() - 1; j++){
        //fout << "[ " << j << " ] ";
        fout << contents[j] << endl;
        cout << "[ " << j << " ] ";
        cout << contents[j] << endl;
        Sleep(16.5);
    }
    fout.close();
    return;
}
// adds backspace functionality to string commands
void DeleteKey(string file){
    fstream fin;
    fstream fout;
    //declare variables
    vector<string> contents;
    string content;
    int i = 0;

    fin.open(file.c_str());
    if(!fin){
        cout << endl << endl << "Error opening file" << endl;
        return;
    }
    //add current text file to vector for transfer
    while(getline(fin, content)){
        contents.push_back(content);
        i++;
    } 
    fin.close();

    if (!contents.empty()) {
            contents.back().pop_back();
    }

    //replace file with contents vector (old file minus last line)
    fout.open(file.c_str(), ios::out | ios::trunc);
    if(!fout){
        cout << "Error opening file" << endl;
        return;
    }

    for(int j = 0; j < contents.size(); j++){
        fout << contents[j];
        //cout << contents[j];
        if(j != contents.size()-1){
            fout << endl;
            //cout << endl;
        }
    }
    fout.close();
    return;
}

bool AddDelay(string file, unsigned char key){
    fstream fout;
    //numlock command key
    if(GetAsyncKeyState(VK_NUMLOCK) & 0x8000){
        //opem file if command key pressed
        fout.open(file.c_str(), ios::app);
        if(!fout){
            cout << "Error opening file" << endl;
            return false;
        }

        if(GetAsyncKeyState(VK_LEFT) & 0x8000)
        {
            fout << "DELAY 300" << endl;
            cout << endl << "DELAY 300" << endl;
        }

        else if(GetAsyncKeyState(VK_UP) & 0x8000)
        {
            fout << "DELAY 600" << endl;
            cout << endl << "DELAY 600" << endl;
        }
        else if(GetAsyncKeyState(VK_RIGHT) & 0x8000)
        {
            fout << "DELAY 1500" << endl;
            cout << endl << "DELAY 1500" << endl;
        }

        else if(GetAsyncKeyState(VK_DOWN) & 0x8000)
        {
            fout << "DELAY 3000" << endl;
            cout << endl << "DELAY 3000" << endl;
        }
        else if(GetAsyncKeyState(VK_BACK) & 0x8000)
        {
            DeleteLine(file);
        }
        else if( key > 0x41 && key < 0x5A){
            //fout << key << endl << "DELAY 300" << endl;
            cout << key << endl << "DELAY 300" << endl;
        }
        //close file
        fout.close();
        return true;
    }

    else
    {
        //continue through main loop if numlock not pressed
    return false;
    }
}

bool DeleteLine(string file){
    cout << endl << endl << "\tDelay removed . . ." << endl << endl;
    CleanPayload(file);
    cout << endl << endl << "\tLine Deleted . . ." << endl << endl;
    Sleep(1);
    CleanPayload(file);
    cout << "REM PREVIOUS LINE DELETED" << endl;
    fstream fout;
    fout.open(file.c_str(), ios::app);
    if(!fout){
        cout << "Error opening file";
        return false;
    }
    //fout << "REM LINE DELETED" << endl;
    return true;
}