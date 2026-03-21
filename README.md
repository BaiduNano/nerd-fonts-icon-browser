<div align="center">
  <img src="res/etc/ss.png" width="480">
  <p>Note: Color and theme may look different depending on your Qt theme.</p>
</div>

# Nerd Fonts Icon Browser
<img src="res/icon/icon.png" width="64">
A Qt based desktop app for browsing and searching Nerd Fonts icons with copy paste support, so you don't have to open a web browser everytime you want to search for nerd font icons. 

## Download
Binary realeases are available [here](https://github.com/BaiduNano/nerd-fonts-icon-browser/releases).

## Copy Options

- **Icon**: copies the icon character
- **Name**: copies the icon class name
- **UTF-8**: copies the UTF-8 code

## Compiling
Requirements:
- Qt6
- CMake
- Ninja
- C++20 compatible compiler, <b>clang</b> is recommended. 

## Building
1.
```bash
cmake -B build
cmake --build build
```
2. Place `glyphnames.json` from the [Nerd Fonts repository](https://github.com/ryanoasis/nerd-fonts/blob/master/glyphnames.json) in the application directory, or `.local/share/NerdFontsIconBrowser` on unix, or `$APPDATA/NerdFontsIconBrowser` on windows.
3. Run `./build/NerdFontsIconBrowser`
