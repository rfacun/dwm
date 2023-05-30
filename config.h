/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */

static const int showsystray             = 1;   /* 0 means no systray */
static const unsigned int systraypinning = 1;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 3;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/

static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */

static const unsigned int gappih    = 5;        /* horiz inner gap between windows */
static const unsigned int gappiv    = 5;        /* vert inner gap between windows */
static const unsigned int gappoh    = 5;        /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 5;        /* vert outer gap between windows and screen edge */
static int smartgaps                = 0;        /* 1 means no outer gap when there is only one window */

static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";

static const char col_bg[]          = "#0a0e14";
static const char col_fg[]          = "#b3b1ad";
static const char col_fg_sel[]      = "#0a0e14";
//static const char col_bg_sel[]      = "#748f4e";    // green accent
static const char col_bg_sel[]      = "#c78c3f";    // orange accent
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_fg, col_bg, col_bg },
    [SchemeSel]  = { col_fg_sel, col_bg_sel,  col_bg_sel  },
};

/* scratchpads */
typedef struct {
    const char *name;
    const void *cmd;
} Sp;
const char *spcmd1[] = {"alacritty", "--class", "Alacritty,terminal", NULL };
const char *spcmd2[] = {"alacritty", "--class", "Alacritty,pulsemixer", "-e", "pulsemixer", NULL };
static Sp scratchpads[] = {
    /* name          cmd  */
    {"terminal", spcmd1},
    {"pulsemixer", spcmd2},
};

/* tagging */
static const char *tags[] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class       instance     title           tags mask       isfloating  isterminal  noswallow  monitor */
    { "Alacritty", NULL,        NULL,           0,              0,          1,           0,        -1 },
    { "Firefox",   NULL,        NULL,           1 << 8,         0,          0,          -1,        -1 },
    { NULL,        NULL,        "Event Tester", 0,              0,          0,           1,        -1 }, /* xev */

    { NULL,       "terminal",   NULL,           SPTAG(0),       1,          1,           0,        -1 },
    { NULL,       "pulsemixer", NULL,           SPTAG(1),       1,          1,           0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
    /* symbol     arrange function */
    //{ "[]=",      tile },    /* first entry is default */
    //{ "><>",      NULL },    /* no layout function means floating behavior */
    //{ "[M]",      monocle },
    { " tiling ",      tile },    /* first entry is default */
    { "floating",      NULL },    /* no layout function means floating behavior */
    { " monokl ",      monocle },
    { " spiral ",      spiral },
    { " dwindl ",     dwindle },
    { "  deck  ",      deck },
    { " bstack ",      bstack },
    { "bstackhz",      bstackhoriz },
    { "  grid  ",      grid },
    { "nrowgrid",      nrowgrid },
    { " hzgrid ",      horizgrid },
    { " glgrid ",      gaplessgrid },
    { "ctmaster",      centeredmaster },
    { "cfmaster",      centeredfloatingmaster },
    { NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_bg, "-nf", col_fg, "-sb", col_bg_sel, "-sf", col_fg_sel, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

#include "shiftview.c"
static const Key keys[] = {
    /* modifier                     key             function        argument */
    // Base
    { MODKEY,                       XK_Return,      spawn,          {.v = termcmd } },
    { MODKEY,                       XK_q,           killclient,     {0} },
    { MODKEY|ControlMask,           XK_c,           quit,           {0} },
    { MODKEY,                       XK_p,           spawn,          {.v = dmenucmd } },

    // Intra-tag movement
    { MODKEY,                       XK_k,           focusstack,     {.i = -1 } },
    { MODKEY,                       XK_j,           focusstack,     {.i = +1 } },
    { MODKEY|ShiftMask,             XK_h,           setmfact,       {.f = -0.05} },
    { MODKEY|ShiftMask,             XK_l,           setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_j,           setcfact,       {.f = +0.25} },
    { MODKEY|ShiftMask,             XK_k,           setcfact,       {.f = -0.25} },

    { MODKEY,                       XK_i,           incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_o,           incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_w,           focusmaster,    {0} },
    { MODKEY,                       XK_b,           zoom,           {0} },
    { MODKEY,                       XK_t,           setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_f,           setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_m,           setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_space,       togglefullscr,  {0} },
    { MODKEY|ShiftMask,             XK_space,       togglefloating, {0} },


    // Inter-tag movement
    { MODKEY,                       XK_Tab,         view,           {0} },
    { MODKEY,                       XK_h,           shiftview,      { .i = -1 } },
    { MODKEY,                       XK_l,           shiftview,      { .i = +1 } },
    { MODKEY,                       XK_0,           view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,           tag,            {.ui = ~0 } },


    { ControlMask|ShiftMask,        XK_g,           togglegaps,     {0} },

    // Programs
    { ControlMask|ShiftMask,        XK_t,           togglescratch,  {.ui = 0 } },
    { MODKEY,                       XK_apostrophe,  spawn,          SHCMD("xsecurelock") },

    { ControlMask|ShiftMask,        XK_a,           togglescratch,  {.ui = 1 } },
    { ControlMask|ShiftMask,        XK_comma,       spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5% ; kill -35 $(pidof dwmblocks)") },
    { ControlMask|ShiftMask,        XK_period,      spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5% ; kill -35 $(pidof dwmblocks)") },
    { ControlMask|ShiftMask,        XK_m,           spawn,          SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle ; kill -35 $(pidof dwmblocks)") },

    { ControlMask|ShiftMask,        XK_k,           spawn,          SHCMD("chkb ; kill -36 $(pidof dwmblocks)") }, // Not satisfied with this... fix.
    { ControlMask|ShiftMask,        XK_Cyrillic_el, spawn,          SHCMD("chkb ; kill -36 $(pidof dwmblocks)") },

    // Tags
    TAGKEYS(                        XK_1,                           0)
    TAGKEYS(                        XK_2,                           1)
    TAGKEYS(                        XK_3,                           2)
    TAGKEYS(                        XK_4,                           3)
    TAGKEYS(                        XK_5,                           4)
    TAGKEYS(                        XK_6,                           5)
    TAGKEYS(                        XK_7,                           6)
    TAGKEYS(                        XK_8,                           7)
    TAGKEYS(                        XK_9,                           8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {.v = &layouts[0]} },

    { ClkWinTitle,          MODKEY,         Button2,        zoom,           {0} },

    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },

    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
    { ClkTagBar,            0,              Button4,        shiftview,      { .i = -1 } },
    { ClkTagBar,            0,              Button5,        shiftview,      { .i = +1 } },
};
