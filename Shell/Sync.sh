#!/bin/sh
com="sync from"
now=$(date +"%d.%m.%y")
case "$(uname)" in
  Linux) os="peng" ;;
  Darwin) os="mac" ;;
esac
git add .
git commit -m "${com} ${os} : ${now}"