#pragma once
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

namespace ConsoleRawMode{
    static struct termios orig_termios;
    static void disableRawMode() {
      tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    }

    static void enableRawMode() {
      tcgetattr(STDIN_FILENO, &orig_termios);
      atexit(disableRawMode);
      struct termios raw = orig_termios;
      raw.c_lflag &= ~(ICANON);
      raw.c_cc[VMIN] = 0;
      raw.c_cc[VTIME] = 1;
      tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    }
}
