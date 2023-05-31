# rfacun's `dwm`
This custom build of `dwm` is part of [my dotfiles](https://github.com/rfacun/dotfiles).

## Patches applied
- [x] [actualfullscreen](https://dwm.suckless.org/patches/actualfullscreen/):
actually toggle fullscreen for a window, instead of toggling the status bar and
the monocle layout.
- [x] [focusmaster-return](https://dwm.suckless.org/patches/focusmaster/):
switch to the master from anywhere in the stack, when the master is selected
return to the client switched from using the same keybind.
- [x] [pertag](https://dwm.suckless.org/patches/pertag/): enables one layout per
tag in contrast of one layout for all tags, also keeps layout, mwfact, barpos
and nmaster per tag.
- [x] [swallow](https://dwm.suckless.org/patches/swallow/): this patch adds
"window swallowing" to `dwm` as known from Plan 9's windowing system `rio`.
- [x] [status2d](https://dwm.suckless.org/patches/status2d/): allows colors and
rectangle drawing in your `dwm` status bar.

## Install
```
git clone https://github.com/rfacun/dwm.git
cd dwm
sudo make clean install
```
