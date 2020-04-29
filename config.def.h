/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 12;        /* border pixel of windows */
static const unsigned int snap      = 6;       /* snap pixel */
static const unsigned int gappih    = 25;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 25;       /* vert inner gap between windows */
static const unsigned int gappoh    = 25;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 25;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

/*   Display modes of the tab bar: never shown, always shown, shown only in */
/*   monocle mode in presence of several windows.                           */
/*   Modes after showtab_nmodes are disabled                                */
enum showtab_modes { showtab_never, showtab_auto, showtab_nmodes, showtab_always};
static const int showtab            = showtab_auto; /* Default tab bar show mode */
static const Bool toptab            = False;    /* False means bottom tab bar */

static const int vertpad            = 5;       /* vertical padding of bar */
static const int sidepad            = 5;       /* horizontal padding of bar */
static const int horizpadbar        = 5;        /* horizontal padding for statusbar */
static const int vertpadbar         = 8;        /* vertical padding for statusbar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* default layout per tags */
/* The first element is for all-tag view, following i-th element corresponds to */
/* tags[i]. Layout is referred using the layouts array index.*/
static int def_layouts[1 + LENGTH(tags)]  = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class	instance	title		tags mask	isfloating	monitor */
	/* { "Gimp",	NULL,		NULL,		0,		1,		-1, }, */
	{ "Firefox",	NULL,		NULL,		0,		0,		-1, },
	{ "Firefox",	NULL,		"Library",	0,		1,		-1, },
	{ "Wpg",	"wpg",		NULL,		0,		1,		-1, },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "H[]",      deck },
	{ "[M]",      monocle },
	{ "⟦@⟧",      spiral },
	{ "⟦➘⟧",      dwindle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, topbar ? NULL : "-b", NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {	/* I currently bind all of my keys in SXHKD so no keys are bound here. */
			/* I'd like to move some WM-specific ones here later when I try other WM's, but for now, don't press F13. */
	/* modifier                     key                function        argument */
	{ MODKEY,                      /*XK_p,     */ XK_F13, spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,            /*XK_Return,*/ XK_F13, spawn,          {.v = termcmd } },
	{ MODKEY,                      /*XK_b,     */ XK_F13, togglebar,      {0} },
	{ MODKEY,                      /*XK_w,     */ XK_F13, tabmode,        {-1} },
	{ MODKEY|ShiftMask,            /*XK_j,     */ XK_F13, rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,            /*XK_k,     */ XK_F13, rotatestack,    {.i = -1 } },
	{ MODKEY,                      /*XK_j,     */ XK_F13, focusstack,     {.i = +1 } },
	{ MODKEY,                      /*XK_k,     */ XK_F13, focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,            /*XK_j,     */ XK_F13, inplacerotate,  {.i = +1} },
	{ MODKEY|ShiftMask,            /*XK_k,     */ XK_F13, inplacerotate,  {.i = -1} },
	{ MODKEY,                      /*XK_i,     */ XK_F13, incnmaster,     {.i = +1 } },
	{ MODKEY,                      /*XK_d,     */ XK_F13, incnmaster,     {.i = -1 } },
	{ MODKEY,                      /*XK_h,     */ XK_F13, setmfact,       {.f = -0.05} },
	{ MODKEY,                      /*XK_l,     */ XK_F13, setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,            /*XK_h,     */ XK_F13, setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,            /*XK_l,     */ XK_F13, setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,            /*XK_o,     */ XK_F13, setcfact,       {.f =  0.00} },
	{ MODKEY,                      /*XK_x,     */ XK_F13, transfer,       {0} },
	{ MODKEY,                      /*XK_Return,*/ XK_F13, zoom,           {0} },
	{ MODKEY|Mod4Mask,             /*XK_u,     */ XK_F13, incrgaps,       {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,   /*XK_u,     */ XK_F13, incrgaps,       {.i = -1 } },
	{ MODKEY|Mod4Mask,             /*XK_i,     */ XK_F13, incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,   /*XK_i,     */ XK_F13, incrigaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,             /*XK_o,     */ XK_F13, incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,   /*XK_o,     */ XK_F13, incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,             /*XK_6,     */ XK_F13, incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,   /*XK_6,     */ XK_F13, incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,             /*XK_7,     */ XK_F13, incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,   /*XK_7,     */ XK_F13, incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,             /*XK_8,     */ XK_F13, incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,   /*XK_8,     */ XK_F13, incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,             /*XK_9,     */ XK_F13, incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,   /*XK_9,     */ XK_F13, incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,             /*XK_0,     */ XK_F13, togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,   /*XK_0,     */ XK_F13, defaultgaps,    {0} },
	{ MODKEY,                      /*XK_Tab,   */ XK_F13, view,           {0} },
	{ MODKEY|ShiftMask,            /*XK_c,     */ XK_F13, killclient,     {0} },
	{ MODKEY,                      /*XK_t,     */ XK_F13, setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                      /*XK_f,     */ XK_F13, setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                      /*XK_m,     */ XK_F13, setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ControlMask,	       /*XK_comma, */ XK_F13, cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,          /*XK_period,*/ XK_F13, cyclelayout,    {.i = +1 } },
	{ MODKEY,                      /*XK_space, */ XK_F13, setlayout,      {0} },
	{ MODKEY|ShiftMask,            /*XK_space, */ XK_F13, togglefloating, {0} },
	{ MODKEY|ShiftMask,            /*XK_f,     */ XK_F13, togglefullscr,  {0} },
	{ MODKEY,                      /*XK_0,     */ XK_F13, view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,            /*XK_0,     */ XK_F13, tag,            {.ui = ~0 } },
	{ MODKEY,                      /*XK_comma, */ XK_F13, focusmon,       {.i = -1 } },
	{ MODKEY,                      /*XK_period,*/ XK_F13, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,            /*XK_comma, */ XK_F13, tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,            /*XK_period,*/ XK_F13, tagmon,         {.i = +1 } },
	TAGKEYS(                       /*XK_1,     */ XK_F13,                 0)
	TAGKEYS(                       /*XK_2,     */ XK_F13,                 1)
	TAGKEYS(                       /*XK_3,     */ XK_F13,                 2)
	TAGKEYS(                       /*XK_4,     */ XK_F13,                 3)
	TAGKEYS(                       /*XK_5,     */ XK_F13,                 4)
	TAGKEYS(                       /*XK_6,     */ XK_F13,                 5)
	TAGKEYS(                       /*XK_7,     */ XK_F13,                 6)
	TAGKEYS(                       /*XK_8,     */ XK_F13,                 7)
	TAGKEYS(                       /*XK_9,     */ XK_F13,                 8)
	{ MODKEY,                      /*XK_F5,    */ XK_F13, xrdb,           {.v = NULL } },
	{ MODKEY|ShiftMask,            /*XK_q,     */ XK_F13, quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTabBar,            0,              Button1,        focuswin,       {0} },
};

void
setlayoutex(const Arg *arg)
{
	setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

void
viewex(const Arg *arg)
{
	view(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
	view(&((Arg){.ui = ~0}));
}

void
toggleviewex(const Arg *arg)
{
	toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagex(const Arg *arg)
{
	tag(&((Arg) { .ui = 1 << arg->ui }));
}

void
toggletagex(const Arg *arg)
{
	toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagall(const Arg *arg)
{
	tag(&((Arg){.ui = ~0}));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
        /* signum           function */
        { "focusstack",     focusstack },
        { "setmfact",       setmfact },
        { "togglebar",      togglebar },
        { "incnmaster",     incnmaster },
        { "togglefloating", togglefloating },
        { "togglefullscr",  togglefullscr },
        { "focusmon",       focusmon },
        { "tagmon",         tagmon },
        { "zoom",           zoom },
        { "view",           view },
        { "viewall",        viewall },
        { "viewex",         viewex },
        { "toggleview",     view },
        { "toggleviewex",   toggleviewex },
        { "tag",            tag },
        { "tagall",         tagall },
        { "tagex",          tagex },
        { "toggletag",      tag },
        { "toggletagex",    toggletagex },
	{ "spawn",	    spawn },
        { "killclient",     killclient },
        { "quit",           quit },
/*      { "setgaps",        setgaps }, */
        { "setlayout",      setlayout },
        { "setlayoutex",    setlayoutex },
        { "cyclelayout",    cyclelayout },
        { "xrdb",           xrdb },
/*      { "togglermaster",  togglermaster }, */
        { "transfer",       transfer },
        { "pushup",         pushup },
        { "pushdown",       pushdown },
        { "rotatestack",    rotatestack },
        { "inplacerotate",  inplacerotate },
        { "switchcol",      switchcol },
        { "setcfact",       setcfact },
};
