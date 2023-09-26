#!/bin/sh
now=$(date +"%d.%m.%y")
case "$(uname)" in
  Linux) echo "Linux" ; echo "Next" ;;
  Darwin) echo "OSX" ;;
esac
#git add .
#git commit -m "sync from "