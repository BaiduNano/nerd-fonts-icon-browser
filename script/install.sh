#!/bin/bash

CONFIG_NAME="nf-icon-browser"
APP_NAME="NerdFontsIconBrowser"
EXEC_NAME="nf-icon-browser"
GLYPH="glyphnames.json"

mkdir $HOME/.local/share/$CONFIG_NAME
cp $GLYPH $HOME/.local/share/$CONFIG_NAME/

sudo cp $APP_NAME /usr/bin/$EXEC_NAME
