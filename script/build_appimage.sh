#!/bin/bash
cd ..
cp build/nf-icon-browser appimage/usr/bin/
tools/appimagetool appimage build/nf-icon-browser.AppImage
