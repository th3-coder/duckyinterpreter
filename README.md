# Duckyinterpreter

* No need to manually write DUCKY scripts anymore!
* emulate and test payload at the same time


## IMPORTANT: 
* Run program as admin to prevent authority issues in certain applications - - - ONLY WORKS ON WINDOWS
* Create folder or file exlcusion if windows removes .exe 


**EITHER** 
* Compile interpreter.cpp yourself


    **or**


* Ensure dependecies are in same folder as interpreter.exe and run


### Running Program:
1. Run .exe
    * opens terminal which shows rubby DUCKY formatted file in real time
2. Enter file number (files with same name will be overwritten)
3. Manually enter all inputs and emulate your desired payload
4. Payload will then be saved to payload(_).dd in the same directory as the .exe
5. Rename to desired name and transfer to rubberDUCKY (or any badusb device that uses DUCKY language)
6. Plug in DUCKY and payload that you just emulated will run!


* **AUTOSTRING**: starts a string when any A-Z character is typed, and ends when ENTER is pressed
* **MANUAL STRING**: Press F2 to start/stop a manual string
* **CHAR PRESS**: Hold numlock and press character 
* **COPY/PASTE** (ONLY IN STRING MODE): CTRL+C (or copy with mouse), CTRL+V
     * If not in string mode, then
    1. Enter manual string mode (press F2)
    2. COPY CONTENTS
    3. PASTE CONTENTS
    4. Exit manual string mode (press F2)    
* **MANUAL DELAY**: NUMLOCK+ARROWS
* **REMOVE PREVIOUS LINE**: NUMLOCK+BACKSPACE
* **CHANGE ATTACKMODE (EXPERIMENTAL)**: Press F9 to change DUCKY from HID to STORAGE device
        
       **HID STORAGE MODE**
       * Opens an elevated powershell terminal in the machine root directory
       * saves the ducky drive letter to $Ducky variable in powershell instance for later reference

       **HID MODE**
       * once in this mode, DUCKY is not seen as a storage device
       * only useful for HID inputs as the name suggests