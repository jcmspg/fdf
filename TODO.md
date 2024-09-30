# TODO



## MAYBE ADD A FEATURE TO TURN HIDDEN LINES ON / OFF ?? --for the sake of readability

==1. refactor the reset_movement so it wont read the file all over again.. make it faster and simpler.== CHECK

2. need to implement rotation   CHECK

3. implement a way to raise or lower the p CHECK

5. find out a way to cycle through several color schemes?? CHECK

6. need to make a decent gui CHECK

7. also, adding a splash screen would be fun. CHECK

### make a toggle for keyboard commands CHECK


CHECK
- press P
  : ASD to pan around
- press R
  : WASD QE to rotate around each axis
- press R
  : WASD QE to rotate around each axis
- press Z
  : WS to zoom in and out
- press T
  : WS increase or decrease the heights

- non toggle
  - press Z
    : RESET
  - press C
    : switch color scheme (grayscale, RGB, etc etc)  CHECK
---
---

## TO DO
# 2024-09-04

need to fix the heights, the height scaling as well when pressing T... its not working very well...
----changed priorities... z scaling is postponed.. although z values are now normalized. so gg ////




need to fix rotation, so it can rotate in 360º it now rotates in any direction. PROBLEM IS I CANT ORBIT AND ZOOM.. IT SQUASHES>>>
GOTTA LOOK INTO IT

NEED TO FIX 3d ORBIT AND zoom ---> SORTA FIXED (SEE ABOVE)



*** MOST IMPORTANT ***

NOrminette
!!!!!!!!!!!

recheck VALGRIND (need to remove the GUI text or sort it out so i can free() it)
