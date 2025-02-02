#pragma once
struct NeilButtons {
    int upKey;
    int downKey;
    int leftKey;
    int rightKey;
    int startKey;
    int selectKey;
    int rKey;
    int lKey;
    int aKey;
    int bKey;
    int xKey;
    int yKey;
    float axis0;
    float axis1;
    float axis2;
    float axis3;
    int touch;
};

struct MyConfig {
    char startupScript[80];
    char cpu[50];
    char ram[50];
    int mouseMode;
    int mouseXOffset;
    int mouseYOffset;
    int mobileMode;
};

extern struct NeilButtons neilbuttons;
extern struct MyConfig neilConfiguration;