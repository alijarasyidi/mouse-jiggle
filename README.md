# mouse-jiggle
Mouse moving apps for Windows and macOS.

## Windows
Open `mouse-jiggle.sln` in Visual Studio and build.

## macOS
Requires the Xcode command line tools (`xcode-select --install`).

```sh
make
./mouse-jiggle
```

The first run will fail until your terminal app is allowed to control the mouse: open System Settings → Privacy & Security → Accessibility, enable your terminal (Terminal, iTerm, VS Code, etc.), then run again.
