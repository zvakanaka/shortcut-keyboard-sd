# SD Card Shortcut Keyboard
- [Stream deck print](https://www.thingiverse.com/thing:2822140)
- Sparkfun Pro Micro board ([Sparkfun](https://www.sparkfun.com/products/12640), [Amazon (clone)](https://www.amazon.com/gp/product/B08BJNV1J3))
- Gateron switches ([Amazon](https://www.amazon.com/gp/product/B08JP8ZBKJ))
- Relegendable keycaps ([Amazon](https://www.amazon.com/X-keys-Keycap-Cherry-Compatible-Transparent/dp/B00FYO8EDC), [Thingiverse](https://www.thingiverse.com/thing:3791028))
- microSD card reader ([Adafruit](https://www.adafruit.com/product/254), [Amazon](https://www.amazon.com/gp/product/B07BJ2P6X6))

![keyboard](https://user-images.githubusercontent.com/8365885/142738102-05f94c7d-b109-4187-99c4-2cb9c0f05725.png)


## Instructions
Place files `1.txt`, `2.txt`, etc. on the root of the microSD card. Pressing the corresponding key will execute the [script](https://docs.hak5.org/hc/en-us/articles/360010555153-Ducky-Script-the-USB-Rubber-Ducky-language). See [Duckduino-microSD](https://github.com/Seytonic/Duckduino-microSD) for limitations.

> Note: If you open a script in Notepad.exe, you'll notice everything is all nasty and on one [line](https://www.cs.toronto.edu/~krueger/csc209h/tut/line-endings.html). Use an IDE to edit the scripts if you are on Windows. 

## Printable Template
https://docs.google.com/document/d/1bIXJqAgq2c0NdrM7F2UUlvPY7I8CWgMdOjNfr_esz3Y

The initial setup template has 3 keys that go to this page (1 for each main OS), and 5 keys for numbers:  
![template](https://user-images.githubusercontent.com/8365885/142738169-82577e94-50a0-46f7-82cb-1c1ffff12f3c.png)


## Examples
- [Teams Mute](./examples/teams/1.txt)
- [Zoom Mute](./examples/zoom/1.txt)
- [SunVox](./examples/sunvox) (see [manual](https://www.warmplace.ru/soft/sunvox/manual.php#kbd))
- [Numbers](./examples/numbers) (helpful to check wiring after build)

## Thanks
https://github.com/Seytonic/Duckduino-microSD  
https://docs.hak5.org/hc/en-us/articles/360010555153-Ducky-Script-the-USB-Rubber-Ducky-language  
https://www.thingiverse.com/thing:2822140
