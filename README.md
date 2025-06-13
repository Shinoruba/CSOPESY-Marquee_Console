# CSOPESY S20 | Semi-MO - Immediate-mode mockup - the marquee console

## Assignment Overview

This assignment is a **console-based animation and polling demo**, where the terminal displays a scrolling message ( bouncing around like those DVD screensavers lmao ), and responds to keyboard input while running.
- **Refresh Rate** — how fast the screen updates / Animation update frequency
- **Polling Rate** — how frequently keyboard input is checked / Input checking frequency

---

## Assignment Structure
CSOPESY-Marquee_Console/
- ├── `main.cpp` # Main loop and orchestration
- ├── `marquee.h / .cpp` # Marquee class: scrolling logic
- ├── `console_utils.h / .cpp` # Console clear, sleep, input polling helpers

---

```
g++ main.cpp marquee.cpp console_utils.cpp -o marquee.exe
```

You'll see the marquee message scroll across the console. You can test input responsiveness by typing keys while it runs.
