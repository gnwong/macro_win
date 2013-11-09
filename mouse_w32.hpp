/*  
 *  Copyright (C)  2013  George Wong
 *  GNU General Public License
 *
 *  Notes:
 *    > In MOUSE::moveTo, it's a bit of a misnomer to use dx and dy as
 *    they are not true deltas, but that's how the fields are called.
 */

namespace MOUSE {
  
  /* Forward declarations */
  int moveTo (size_t x, size_t y);
  int position (size_t &x, size_t &y);
  
  int rightClick ();
  int rightDown ();
  int rightUp ();
  
  int leftClick ();
  int leftDown ();
  int leftUp ();
  
  /* Move the position of the cursor */
  int moveTo (size_t x, size_t y) {
    double dx = x * (65535.0f / (::GetSystemMetrics (SM_CXSCREEN)-1));
    double dy = y * (65535.0f / (::GetSystemMetrics (SM_CYSCREEN)-1));
    
    INPUT Input = {0};
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE;
    Input.mi.dx = LONG(dx);
    Input.mi.dy = LONG(dy);
    ::SendInput(1,&Input,sizeof(INPUT));   
    return 0;
  }
  
  /* Return mouse position in pixels (x, y) */
  int position (size_t &x, size_t &y) {
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    x = cursorPos.x;
    y = cursorPos.y;
    return 0;
  }

  /* Right-button functions */
  int rightClick () {
    rightDown();
    rightUp();
  }
  int rightDown () {
    INPUT Input = {0};
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    ::SendInput(1,&Input,sizeof(INPUT));
    return 0;
  }
  int rightUp () {
    INPUT Input = {0};
    ::ZeroMemory(&Input,sizeof(INPUT));
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    ::SendInput(1,&Input,sizeof(INPUT));
    return 0; 
  }
  
  /* Left-button functions */
  int leftClick () {
    leftDown();
    leftUp();
  }
  int leftDown () {
    INPUT Input = {0};
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    ::SendInput(1,&Input,sizeof(INPUT));    
  }
  int leftUp () {
    INPUT Input = {0};
    ::ZeroMemory(&Input,sizeof(INPUT));
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    ::SendInput(1,&Input,sizeof(INPUT));
  }
  
}
