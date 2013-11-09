/*  
 *  Copyright (C)  2013  George Wong
 *  GNU General Public License
 *
 *  Notes:
 *    > There is certainly not full support for all
 *    punctuation at this time
 */

namespace KEYBOARD {
  
  // Forward declarations
  int lchar_press (const char c);
  int char_press (const char c);
  int any_char_press (const char c);
  int string_write (std::string s);
  
  int space_press ();
  int num_press (uint32_t n);
  int gen_press (uint32_t n, bool shift);
  int gen_press (uint32_t n);
  
  int shift_down ();
  int shift_up ();
  
  
  // Lowercase character (alpha) press (down & up)
  int lchar_press (const char c) {
    try {
      INPUT Input = {0};
      Input.type = INPUT_KEYBOARD;
      Input.ki.wVk = toupper(c);
      ::SendInput(1,&Input,sizeof(INPUT));  
      Input.ki.dwFlags = KEYEVENTF_KEYUP;
      ::SendInput(1,&Input,sizeof(INPUT));  
    } catch (...) {
      std::cout << "Unable to write character " << c << std::endl;
      return 1;
    }
    return 0;
  }
  
  // General character (alpha) press (down & up)
  int char_press (const char c) {
    if (c == toupper(c)) {
      shift_down();
      lchar_press(c);
      shift_up();
    } else {
      lchar_press(c);
    }
    return 0;
  }
  
  // Any (all typeable) character press (down & up)
  int any_char_press (const char c) {
    
    // Space
    if (c==' ') {
      space_press();
      return 0;
    }
    
    // Number
    if (c>=0x30 && c<0x40) {
      num_press(c-0x30);
      return 0;
    }
    
    // Alpha
    if ((c>=65 && c<=90) || (c>=97 && c<=122)) {
      char_press(c);
      return 0;
    }
    
    // Punct (incomplete)
    switch ((int)c) {
      case 33:
        gen_press(0x31,true);
        return 0;
      case 64:
        gen_press(0x32,true);
        return 0;
      case 35:
        gen_press(0x33,true);
        return 0;
      case 36:
        gen_press(0x34,true);
        return 0;  
      case 37:
        gen_press(0x35,true);
        return 0;
      case 94:
        gen_press(0x36,true);
        return 0;
      case 38:
        gen_press(0x37,true);
        return 0;
      case 42:
        gen_press(0x38,true);
        return 0;
      case 40:
        gen_press(0x39,true);
        return 0;
      case 41:
        gen_press(0x30,true);
        return 0;
      case 46:
        gen_press(0xbe);
        return 0;
      case 44:
        gen_press(0xbc);
        return 0;
    }
    
    // Other
    std::cout << "Unrecognized character" << std::endl;
    std::cout << (int)c << " <- " << c << std::endl;
    return -1;
  }
  
  // Write a string of characters
  int string_write (std::string s) {
    const char *cs = s.c_str();
    for (size_t i=0; i<strlen(cs); i++) {
      any_char_press(cs[i]);
    }
    std::cout << std::endl;
    return 0;
  }
  
  // Space down&up
  int space_press () {
    INPUT Input = {0};
    Input.type = INPUT_KEYBOARD;
    Input.ki.wVk = VK_SPACE;
    ::SendInput(1,&Input,sizeof(INPUT));
    Input.ki.dwFlags = KEYEVENTF_KEYUP;
    ::SendInput(1,&Input,sizeof(INPUT));
    return 0;
  }
  
  // Number (single character) down&up
  int num_press (uint32_t n) {
    INPUT Input = {0};
    Input.type = INPUT_KEYBOARD;
    Input.ki.wVk = 0x30+n;
    ::SendInput(1,&Input,sizeof(INPUT));
    Input.ki.dwFlags = KEYEVENTF_KEYUP;
    ::SendInput(1,&Input,sizeof(INPUT));
    return 0;
  }
  
  // Press down key with wVk as given by `n' with or w/o `shift'
  int gen_press (uint32_t n, bool shift) {
    try {
      if (shift) shift_down();
      INPUT Input = {0};
      Input.type = INPUT_KEYBOARD;
      Input.ki.wVk = n;
      ::SendInput(1,&Input,sizeof(INPUT));
      Input.ki.dwFlags = KEYEVENTF_KEYUP;
      ::SendInput(1,&Input,sizeof(INPUT));
      if (shift) shift_up();
    } catch (...) {
      std::cout << "Unable to press key with wVk value " << n << std::endl;
      return -1;
    }
    return 0;
  }
  
  // Press down key with wVk as given by `n'
  int gen_press (uint32_t n) {
    return gen_press(n,false);
  }
  
  // Shift down
  int shift_down () {
    INPUT Input = {0};
    Input.type = INPUT_KEYBOARD;
    Input.ki.wVk = VK_LSHIFT;
    ::SendInput(1,&Input,sizeof(INPUT));
    return 0;
  }
  
  // Shift up
  int shift_up () {
    INPUT Input = {0};
    Input.type = INPUT_KEYBOARD;
    Input.ki.dwFlags = KEYEVENTF_KEYUP;
    Input.ki.wVk = VK_LSHIFT;
    ::SendInput(1,&Input,sizeof(INPUT));
    return 0;
  }
  
}
