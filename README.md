# SD Card Shortcut Keyboard
[Stream Cheap (Mini Macro Keyboard)](https://www.thingiverse.com/thing:2822140) + [Duckduino-microSD](https://github.com/Seytonic/Duckduino-microSD)
## Materials
- [Stream deck print](https://www.thingiverse.com/thing:5237714)
- Sparkfun Pro Micro board ([Sparkfun](https://www.sparkfun.com/products/12640), [Amazon (clone)](https://amzn.to/3VAQRhi))
- Gateron switches ([Amazon](https://amzn.to/3IaJqKC))
- Relegendable keycaps ([Amazon](https://amzn.to/3WG48X6), [Thingiverse](https://www.thingiverse.com/thing:3791028), [Other on Thingiverse](https://www.thingiverse.com/thing:4126150))
- microSD card reader ([Adafruit](https://www.adafruit.com/product/254), [Amazon](https://amzn.to/3YXaqDr))

![shortcut_keyboard](https://user-images.githubusercontent.com/8365885/154828694-d706b5c4-2969-453b-9fc2-412868c813c3.jpg)

![build](https://user-images.githubusercontent.com/8365885/210162516-476d40cf-f464-426e-a49f-1d3ea1a3b25f.png)

## Instructions
Place files `1.txt`, `2.txt`, etc. on the root of the microSD card. Pressing the corresponding key will execute the [script](https://docs.hak5.org/hc/en-us/articles/360010555153-Ducky-Script-the-USB-Rubber-Ducky-language). See [Duckduino-microSD](https://github.com/Seytonic/Duckduino-microSD) for limitations (with the exception that this project adds support for `MEDIA_PLAY_PAUSE`, `MEDIA_VOLUME_UP`, `MEDIA_VOLUME_MUTE`, a few others, and [hex codes](http://www.freebsddiary.org/APC/usb_hid_usages.php) for just about any key you want).

> Note: If you open a script in Notepad.exe, you'll notice everything is all nasty and on one [line](https://www.cs.toronto.edu/~krueger/csc209h/tut/line-endings.html). Use an IDE to edit the scripts if you are on Windows. 

## Printable Template
https://docs.google.com/document/d/1bIXJqAgq2c0NdrM7F2UUlvPY7I8CWgMdOjNfr_esz3Y 
![template](https://user-images.githubusercontent.com/8365885/154828762-8e268f02-904f-4a69-88bd-9ad119a25dbc.png)


## Examples
- [Teams Mute](./examples/teams/1.txt)
- [Zoom Mute](./examples/zoom/1.txt)
- [SunVox](./examples/sunvox) (see [manual](https://www.warmplace.ru/soft/sunvox/manual.php#kbd))
- [Numbers](./examples/numbers) (these are the default if you boot it without an SD card - helpful to check wiring)

## Thanks!
https://github.com/Seytonic/Duckduino-microSD  
https://docs.hak5.org/hc/en-us/articles/360010555153-Ducky-Script-the-USB-Rubber-Ducky-language  
https://www.thingiverse.com/thing:2822140
