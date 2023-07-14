/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Misc Tamsyn:size=12" }; // change to monospace 10 when fonts.conf is done
static const char dmenufont[]       = "Misc Tamsyn:size=12"; // change to monospace 10 when fonts.conf is done
static const char fg_normal[]       = "#b3b1ad";
static const char bg_normal[]       = "#0a0e14";
static const char bo_normal[]       = "#0a0e14";
static const char fg_selected[]     = "#0a0e14";
static const char bg_selected[]     = "#f9af4f";
static const char bo_selected[]     = "#f9af4f";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { fg_normal, bg_normal, bo_normal },
	[SchemeSel]  = { fg_selected, bg_selected, bo_selected },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* class        instance    title       tags mask       isfloating      monitor */
	{ "Gimp",       NULL,       NULL,       0,              1,              -1 },
	{ "firefox",    NULL,       NULL,       1 << 8,         0,              -1 },
};

/* layout(s) */
static const float mfact        = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;    /* number of clients in master area */
static const int resizehints    = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol       arrange function */
	{ "tile",       tile },    /* first entry is default */
	{ "monocle",    monocle },
	{ "floating",   NULL },    /* no layout function means floating behavior */
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
static const char *dmenucmd[]   = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", bg_normal, "-nf", fg_normal, "-sb", bg_selected, "-sf", fg_selected, NULL };
static const char *termcmd[]    = { "alacritty", NULL };

static const Key keys[] = {
	/* modifier         key         function        argument */
    // Programs
	{ MODKEY,           XK_Return,  spawn,          {.v = termcmd } },
	{ MODKEY,           XK_p,       spawn,          {.v = dmenucmd } },
	{ MODKEY,           XK_c,       killclient,     {0} },

    // Layout
	{ MODKEY,           XK_s,       zoom,           {0} },
	{ MODKEY,           XK_t,       setlayout,      {.v = &layouts[0]} },
	{ MODKEY,           XK_m,       setlayout,      {.v = &layouts[1]} },
	{ MODKEY,           XK_space,   togglefloating, {0} },
	{ MODKEY,           XK_h,       setmfact,       {.f = -0.05} },
	{ MODKEY,           XK_l,       setmfact,       {.f = +0.05} },

    // Movement
	{ MODKEY|ShiftMask, XK_q,       quit,           {0} },
	{ MODKEY,           XK_Tab,     view,           {0} },
	{ MODKEY,           XK_j,       focusstack,     {.i = +1 } },
	{ MODKEY,           XK_k,       focusstack,     {.i = -1 } },

	{ MODKEY,           XK_comma,   focusmon,       {.i = -1 } },
	{ MODKEY,           XK_period,  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask, XK_comma,   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask, XK_period,  tagmon,         {.i = +1 } },
	TAGKEYS(            XK_1,                       0)
	TAGKEYS(            XK_2,                       1)
	TAGKEYS(            XK_3,                       2)
	TAGKEYS(            XK_4,                       3)
	TAGKEYS(            XK_5,                       4)
	TAGKEYS(            XK_6,                       5)
	TAGKEYS(            XK_7,                       6)
	TAGKEYS(            XK_8,                       7)
	TAGKEYS(            XK_9,                       8)
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

