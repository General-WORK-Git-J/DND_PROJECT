#include <gtest/gtest.h>
#include "H_Colours.h"

// ── Macro definitions ─────────────────────────────────────────────────────────

TEST(ColoursTest, MacroValuesMatchWindowsConsoleColourCodes)
{
    EXPECT_EQ(BLACK,         0);
    EXPECT_EQ(BLUE,          1);
    EXPECT_EQ(GREEN,         2);
    EXPECT_EQ(AQUA,          3);
    EXPECT_EQ(RED,           4);
    EXPECT_EQ(PURPLE,        5);
    EXPECT_EQ(YELLOW,        6);
    EXPECT_EQ(WHITE,         7);
    EXPECT_EQ(GRAY,          8);
    EXPECT_EQ(LIGHT_BLUE,    9);
    EXPECT_EQ(LIGHT_GREEN,   10);
    EXPECT_EQ(LIGHT_AQUA,    11);
    EXPECT_EQ(LIGHT_RED,     12);
    EXPECT_EQ(LIGHT_PURPLE,  13);
    EXPECT_EQ(LIGHT_YELLOW,  14);
    EXPECT_EQ(BRIGHT_WHITE,  15);
}

// ── Handle validity ───────────────────────────────────────────────────────────

TEST(ColourManagerTest, GetHandleReturnsValidHandle)
{
    Colour_manager cm;
    HANDLE h = cm.getHandle();
    EXPECT_NE(h, INVALID_HANDLE_VALUE);
    EXPECT_NE(h, static_cast<HANDLE>(nullptr));
}

// ── setColour: valid codes ─────────────────────────────────────────────────────

TEST(ColourManagerTest, SetColourAllValidCodesDoNotCrash)
{
    Colour_manager cm;
    for (int code = 0; code <= 15; ++code)
    {
        EXPECT_NO_FATAL_FAILURE(cm.setColour(code))
            << "crashed on colour code " << code;
    }
    // Restore default white so subsequent test output is readable
    cm.setColour(WHITE);
}

TEST(ColourManagerTest, SetColourWhiteRestoresDefault)
{
    Colour_manager cm;
    cm.setColour(RED);
    cm.setColour(WHITE);
    // SetConsoleTextAttribute succeeds when the handle is valid;
    // verifying via GetConsoleScreenBufferInfo
    CONSOLE_SCREEN_BUFFER_INFO info{};
    BOOL ok = GetConsoleScreenBufferInfo(cm.getHandle(), &info);
    if (ok)
    {
        EXPECT_EQ(info.wAttributes & 0x0F, WHITE);
    }
}
