/*
 *  `main.cc'
 *    Windows mouse/keystroke auto macro program.
 *
 *  Copyright (C)  2013  George Wong
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see http://www.gnu.org/licenses/.
 *
 */
 
#define _WIN32_WINNT 0x500    // I have yet to encounter the case of 0x501,
                              //   but I am told it exists...

#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>

#include "mouse_w32.hpp"
#include "keyboard_w32.hpp"
#include "mstep.hpp"
#include "io.hpp"


// Forward declarations
void man ();
int parseCmd (int argc, char **argv, const char **fname);

//  Entry point
int main (int argc, char **argv) {
  
  // Init stuff
  std::cout << "Windows Mouse/Keyboard Macro Program\n" << std::endl;
  std::vector<MStep> MSteps; 
  
  uint32_t repeats = 0;
  uint32_t steps = 0;
  uint32_t wait = 0;
  const char *fname = "default.macro";
  
  // Setup
  if (parseCmd(argc, argv, &fname)) {
    return 0;
  }
  if (IO::load_macro(fname, &repeats, &steps, &wait, &MSteps)==1) return 0;
  std::cout << std::endl;
  
  std::cout << "Number of steps in base macro: " << steps << std::endl;
  std::cout << "Number of repeats of macro: " << repeats << std::endl;
  std::cout << "Pre-run wait time (s): " << wait << std::endl << std::endl;
  
  // Pre-run wait
  for (int i=0; i<wait; i++) {
    std::cout << wait-i << ".." << std::endl;
    Sleep(1000);
  }
  
  // For each iteration (in repeats)
  for (int i=0; i<repeats; i++) {
    std::cout << "\n[ REPEAT ]" << std::endl;
    // Steps within one repeat
    for (int j=0; j<steps; j++) {
      // move
      if (MSteps.at(j).ins_t()==1) {
        MOUSE::moveTo(MSteps.at(j).arg_ui(1),MSteps.at(j).arg_ui(2));
      }
      // click
      if (MSteps.at(j).ins_t()==2) {
        if (MSteps.at(j).arg_ui(1)==0) {
          MOUSE::leftClick(); 
        } else if (MSteps.at(j).arg_ui(1)==1) {
          MOUSE::rightClick();
        }
      }
      // type
      if (MSteps.at(j).ins_t()==3) {
        KEYBOARD::string_write(MSteps.at(j).arg_s(1));
      } 
      // pause
      if (MSteps.at(j).ins_t()==4) {
        Sleep((int)(MSteps.at(j).arg_d(1)*1000+0.5));
      }
    }
  }  
  
  return 0;
}

// Print man page
void man () {
 std::cout << " =================================================\n"
           << " =================================================" << std::endl;
}


int parseCmd (int argc, char **argv, const char **fname) {
  
  for (int i=0; i<argc; i++) {
    if (std::string(argv[i]).compare("-m")==0) {
      if ((i+1<argc) && (argv[i+1][0]!='-')) {
        *fname = argv[i+1];
      } else {
        std::cout << "Unable to load macro file as given." << std::endl; 
      }
    } else if (std::string(argv[i]).compare("-h")==0) {
      man();
      return 1;
    }
  }
  
  return 0;
}
