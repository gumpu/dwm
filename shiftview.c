#include <X11/cursorfont.h>
#include <X11/keysym.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xproto.h>
#include <X11/Xutil.h>
#ifdef XINERAMA
#include <X11/extensions/Xinerama.h>
#endif /* XINERAMA */
#include <X11/Xft/Xft.h>


#include "dwm.h"
#include "drw.h"
#include "util.h"


/** Function to shift the current view to the left/right
 *
 * @param: "arg->i" stores the number of tags to shift right (positive value)
 *          or left (negative value)
 */
void shiftview(const Arg* arg)
{
    Arg a;
    Client* c;
    unsigned visible = 0;
    int i = arg->i;
    int count = 0;
    int nextseltags, curseltags = selmon->tagset[selmon->seltags];

    do {
        if (i > 0) { // left circular shift
            nextseltags = (curseltags << i) | (curseltags >> (LENGTH(tags) - i));
        } else { // right circular shift
            nextseltags = curseltags >> (- i) | (curseltags << (LENGTH(tags) + i));
        }

        // Check if tag is visible
        for (c = selmon->clients; c && !visible; c = c->next) {
            if (nextseltags & c->tags) {
                visible = 1;
                break;
            }
        }
        i += arg->i;
    }
    while (!visible && ++count < 10);

    if (count < 10) {
        a.i = nextseltags;
        view(&a);
    }
}

void shifttag(const Arg* arg)
{
    Arg a;
    Client* c;
    unsigned visible = 0;
    int i = arg->i;
    int count = 0;
    int nextseltags, curseltags = selmon->tagset[selmon->seltags];

    do {
        if (i > 0) { // left circular shift
            nextseltags = (curseltags << i) | (curseltags >> (LENGTH(tags) - i));
        } else { // right circular shift
            nextseltags = curseltags >> (- i) | (curseltags << (LENGTH(tags) + i));
        }

        // Check if tag is visible
        for (c = selmon->clients; c && !visible; c = c->next) {
            if (nextseltags & c->tags) {
                visible = 1;
                break;
            }
        }
        i += arg->i;
    }
    while (!visible && ++count < 10);

    if (count < 10) {
        a.i = nextseltags;
        tag(&a);
    }
}

/* ------------------------ end of file -------------------------------*/
