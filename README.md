# rfacun's `dwm`
This custom build of `dwm` is part of [my dotfiles](https://github.com/rfacun/dotfiles).

## Patches applied
### Functional
- [x] [actualfullscreen](https://dwm.suckless.org/patches/actualfullscreen/):
actually toggle fullscreen for a window, instead of toggling the status bar and
the monocle layout.
- [x] [shiftview.c](https://lists.suckless.org/dev/1104/7590.html): increment or
decrement the selected tag and rotate the selected tags.
- [x] [focusmaster-return](https://dwm.suckless.org/patches/focusmaster/):
switch to the master from anywhere in the stack, when the master is selected
return to the client switched from using the same keybind.
- [x] [pertag](https://dwm.suckless.org/patches/pertag/): enables one layout per
tag in contrast of one layout for all tags, also keeps layout, mwfact, barpos
and nmaster per tag.
- [x] [swallow](https://dwm.suckless.org/patches/swallow/): this patch adds
"window swallowing" to `dwm` as known from Plan 9's windowing system `rio`.
- [x] [alwayscenter](https://dwm.suckless.org/patches/alwayscenter/):
all floating windows are centered, like the
[center](https://dwm.suckless.org/patches/center/) patch, but without a rule.
- [x] [togglefloatingcenter](https://dwm.suckless.org/patches/togglefloatingcenter/):
togglefloating() floats the  client in a  centered position.
- [x] [scratchpads](https://dwm.suckless.org/patches/scratchpads/): enables
multiple scratchpads, each with one asigned window.
- [x] [status2d+systray](https://dwm.suckless.org/patches/status2d/): allows
colors and rectangle drawing in your `dwm` status bar, it also embeds
[systray patch](https://dwm.suckless.org/patches/systray/).

## Install
```
git clone https://github.com/rfacun/dwm.git
cd dwm
sudo make clean install
```
