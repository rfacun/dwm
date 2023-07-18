/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char fg_normal[]       = "#b3b1ad";
static const char bg_normal[]       = "#0a0e14";
static const char bo_normal[]       = "#0a0e14";
static const char fg_selected[]     = "#0a0e14";
static const char bg_selected[]     = "#e09d47";
static const char bo_selected[]     = "#e09d47";
static const char hi_selected[]     = "#e09d47";
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { fg_normal, bg_normal, bo_normal },
    [SchemeSel]  = { fg_selected, bg_selected, bo_selected },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
//static const char *tags[] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };

static const Rule rules[] = {
    /* class        instance    title           tags mask   isfloating  isterminal  noswallow   monitor */
    { "Gimp",       NULL,       NULL,           0,          1,          0,           0,         -1 },
    { "firefox",    NULL,       NULL,           1 << 8,     0,          0,          -1,         -1 },
    { "Alacritty",  NULL,       NULL,           0,          0,          1,           0,         -1 },
    { "Alacritty",  "floating", NULL,           0,          1,          1,           0,         -1 },
    { NULL,         NULL,       "Event Tester", 0,          0,          0,           1,         -1 }, /* xev */
};

/* layout(s) */
static const float mfact        = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;    /* number of clients in master area */
static const int resizehints    = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol   arrange function */
    { "[]=",    tile },    /* first entry is default */
    { "[M]",    monocle },
    { "><>",    NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,        view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,        toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,        tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,        toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2]         = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]   = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont,
    "-nb", bg_normal, "-nf", fg_normal, "-sb", bg_selected, "-sf", fg_selected,
    "-nhb", bg_normal, "-nhf", bg_selected, "-shb", "#b37d38", "-shf", fg_selected, NULL };
static const char *termcmd[]    = { "alacritty", NULL };

static const Key keys[] = {
    /* modifier         key             function        argument */
    /* base */
    { MODKEY,           XK_Return,      spawn,          {.v = termcmd } },
    { MODKEY,           XK_n,           spawn,          SHCMD("alacritty --class Alacritty,floating") },
    { MODKEY,           XK_p,           spawn,          {.v = dmenucmd } },
    { MODKEY,           XK_c,           killclient,     {0} },
    { MODKEY,           XK_0,           spawn,          SHCMD("session") },
    { MODKEY|ShiftMask, XK_q,           quit,           {0} },
    /* layout */
    { MODKEY,           XK_s,           zoom,           {0} },
    { MODKEY,           XK_t,           setlayout,      {.v = &layouts[0]} },
    { MODKEY,           XK_m,           setlayout,      {.v = &layouts[1]} },
    { MODKEY,           XK_space,       togglefloating, {0} },
    { MODKEY,           XK_h,           setmfact,       {.f = -0.05} },
    { MODKEY,           XK_l,           setmfact,       {.f = +0.05} },
    { MODKEY,           XK_f,           togglefullscr,  {0} },
    /* movement */
    { MODKEY,           XK_Tab,         view,           {0} },
    { MODKEY,           XK_j,           focusstack,     {.i = +1 } },
    { MODKEY,           XK_k,           focusstack,     {.i = -1 } },
    { MODKEY,           XK_comma,       focusmon,       {.i = -1 } },
    { MODKEY,           XK_period,      focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask, XK_comma,       tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask, XK_period,      tagmon,         {.i = +1 } },

    /* volume control */
    { Mod1Mask,         XK_comma,       spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5% ; kill -35 $(pidof dwmblocks)") },
    { Mod1Mask,         XK_period,      spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5% ; kill -35 $(pidof dwmblocks)") },
    { Mod1Mask,         XK_m,           spawn,          SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle ; kill -35 $(pidof dwmblocks)") },
    /* screenshots */
    { Mod1Mask,         XK_s,           spawn,          SHCMD("scrn") },
    /* redshift */
    { Mod1Mask,         XK_l,           spawn,          SHCMD("kill -38 $(pidof dwmblocks); chlight") },
    /* kb layout (latam-ru) -- surely there is a better way to do this... specially for multiple layouts... */
    { Mod1Mask,         XK_k,           spawn,          SHCMD("chkb ; kill -36 $(pidof dwmblocks)") },
    { Mod1Mask,         XK_Cyrillic_el, spawn,          SHCMD("chkb ; kill -36 $(pidof dwmblocks)") },
    /* other */
    { 0,                XK_Num_Lock,    spawn,          SHCMD("xdotool key Num_Lock ; kill -37 $(pidof dwmblocks)") },
    { 0,                XK_Caps_Lock,   spawn,          SHCMD("xdotool key Caps_Lock ; kill -37 $(pidof dwmblocks)") },

    /* tags */
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

