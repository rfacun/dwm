/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;
static const unsigned int snap      = 10;
static const int showbar            = 1;
static const int topbar             = 1;
static const int swallowfloating    = 0;
static const char *fonts[]          = { "Noto Sans Mono:size=10" };
static const char light_grey[]      = "#b3b1ad";
static const char dark_grey[]       = "#0a0e14";
static const char orange[]          = "#e09d47";
static const char *colors[][3]      = {
    /*               fg             bg          border   */
    [SchemeNorm] = { light_grey,    dark_grey,  dark_grey },
    [SchemeSel]  = { dark_grey,     orange,     orange },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "firefox" };

/* rules */
static const Rule rules[] = {
    /* class        instance    title           tags mask   isfloating  isterminal  noswallow   monitor */
    { "Gimp",       NULL,       NULL,           0,          1,          0,           0,         -1 },
    { "firefox",    NULL,       NULL,           1 << 8,     0,          0,          -1,         -1 },
    { "Alacritty",  NULL,       NULL,           0,          0,          1,           0,         -1 },
    { "Alacritty",  "floating", NULL,           0,          1,          1,           0,         -1 },
    { NULL,         NULL,       "Event Tester", 0,          0,          0,           1,         -1 }, /* xev */
};

/* layout(s) */
static const float mfact        = 0.50;
static const int nmaster        = 1;
static const int resizehints    = 0;
static const int lockfullscreen = 1;
static const Layout layouts[] = {
    /* symbol   arrange function */
    { "/tiling  []=",    tile },
    { "/monocle [0]",    monocle },
    { "/float   ><>",    NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,        view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,        toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,        tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,        toggletag,      {.ui = 1 << TAG} },

static const Key keys[] = {
    /* modifier         key             function        argument */
    { MODKEY,           XK_c,           killclient,     {0} },

    { MODKEY,           XK_s,           zoom,           {0} },
    { MODKEY,           XK_t,           setlayout,      {0} },
    { MODKEY,           XK_f,           togglefloating, {0} },
    { 0,                XK_F11,         togglefullscr,  {0} },
    { MODKEY,           XK_Tab,         view,           {0} },

    { MODKEY,           XK_h,           setmfact,       {.f = -0.05} },
    { MODKEY,           XK_l,           setmfact,       {.f = +0.05} },
    { MODKEY,           XK_j,           focusstack,     {.i = +1 } },
    { MODKEY,           XK_k,           focusstack,     {.i = -1 } },

    TAGKEYS(            XK_1,                           0)
    TAGKEYS(            XK_2,                           1)
    TAGKEYS(            XK_3,                           2)
    TAGKEYS(            XK_4,                           3)
    TAGKEYS(            XK_5,                           4)
    TAGKEYS(            XK_6,                           5)
    TAGKEYS(            XK_7,                           6)
    TAGKEYS(            XK_8,                           7)
    TAGKEYS(            XK_9,                           8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
};

