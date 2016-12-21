#pragma once
#define UI_MAX_NODES 50 //PER PANEL

#define BTN_ACTIVE 0
#define BTN_DOWN 1
#define BTN_DISABLED 2
#define BTN_HOVER 3


/* Checkbox */
#define CHECKBOX_ACTIVE 0
#define CHECKBOX_DOWN 1

#define COMBO_ACTIVE 0
#define COMBO_OPEN 1
#define COMBO_HOVER 4

/* Style for panel */
#define STYLE_NORMAL 1
#define STYLE_ROUND 2

/* Other visual changes bitmask 
*	Values have to be powers of 2! (1, 2, 4, 8 etc.)
*	See UI_Panel for bitmask functions examples
*/
#define STYLEFLAG_OUTLINE 1

/* Title window defaults */
#define TITLE_WINDOW_SIZE_X GetSystemMetrics(SM_CXSCREEN)/5
#define TITLE_WINDOW_SIZE_Y GetSystemMetrics(SM_CYSCREEN)/4+130

/* Options window defaults */
#define OPTIONS_WINDOW_SIZE_X GetSystemMetrics(SM_CXSCREEN)/5
#define OPTIONS_WINDOW_SIZE_Y GetSystemMetrics(SM_CYSCREEN)/5
#define OPTIONS_WINDOW_SCALE_X windowSizeX/10
#define OPTIONS_WINDOW_SCALE_Y windowSizeY/10

/* Join Game window defaults */
#define JOINGAME_WINDOW_SIZE_X 350
#define JOINGAME_WINDOW_SIZE_Y 220
#define JOINGAME_WINDOW_SCALE_X windowSizeX/20
#define JOINGAME_WINDOW_SCALE_Y windowSizeY/20