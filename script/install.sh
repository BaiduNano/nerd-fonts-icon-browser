#!/bin/bash

APP_NAME="NerdFontsIconBrowser"
EXEC_NAME="nf-icon-browser"
GLYPH="glyphnames.json"

mkdir $HOME/.local/share/$APP_NAME
cp $GLYPH $HOME/.local/share/$APP_NAME/

sudo cp $APP_NAME /usr/bin/$EXEC_NAME
