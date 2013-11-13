macro_win  `main.exe'
=====================
## Click / Keystroke Macro Program (Windows)


### Use (Quickstart)
A compiled binary of the latest version of the code is available at
`build/main.exe`. `main.exe` and the `default.macro` file in the same
directory may be downloaded and run as is.

The `default.macro` file outlines the behavior of the macro program. The sample macro file is reproduced immedaitely below.
```bash
# Number of repeats
REPEATS=1
WAIT=0
# Commands in form:
# OPR (ARG1) (ARG2) [trailing space]
PAU 0.2 
CLK 0 
MOV 10 20 
TYP hello world 
POS 0 
MOV 200 340 

```
The first 5 lines must be in the format shown. __REPEATS__ indicates the number of times to repeat the full set of macro steps starting on line 6. __WAIT__ indicates the number of seconds to delay execution of the macro when the program is first run. Lines 6 list the macro steps.

Valid commands are:
* PAU sec - Pauses the program for "sec" seconds
* MOV x y - Moves the mouse to (x,y)
* CLK btn - Clicks the mouse button corresponding to btn: 0-left 1-right
* POS del - Reports the position of the mouse every "del" seconds or once if del=0
* TYP string - Types the given string on the keyboard

Each macro command line (with the exception of TYP) must have a space character following the last argument. The full file must end in a new line character.

The `-m` flag may be added after calling `main.exe` as in
```bash
main.exe -m name.macro
```
to run a macro script with a different name. In this way, multiple macros may be saved and run at any time.

A help page may be printed to the terminal by appending the `-h` flag to `main.exe` as in
```bash
main.exe -h
```

### Building from Source
The `main.exe` program may be compiled by source; all necessary files have been included in this repository in the root directory.

The following files should be included:
* io.hpp (file input library)
* keyboard_w32.hpp (win32 keyboard event library)
* mouse_w32.hpp (win32 mouse event library)
* mstep.hpp (class definition for macro step)
* main.cc (main program)

The code was developed using Bloodshed Dev-C++ version 4.9.9.2, released under the GNU General Public License version 2.


### Issues
* No dynamic text/mouse positions
* Not all keyboard characters are supported at this time
* No up/down click "drag" feature
* No backspace/delete key functionality
