#!/bin/bash

EXEC_NAME="nf-icon-browser"
GLYPH="glyphnames.json"
FONT_NAME="fallback/0xProtoNerdFontPropo-Regular.ttf"
APPDATA="$HOME/.local/share/$EXEC_NAME"

mkdir "$APPDATA"
mkdir "$APPDATA/fallback"
cp $GLYPH $APPDATA
cp $FONT_NAME "$APPDATA/fallback/"

sudo cp $EXEC_NAME /usr/bin/$EXEC_NAME
echo -e "\n\nDone: run it with 'nf-icon-browser'\n"
