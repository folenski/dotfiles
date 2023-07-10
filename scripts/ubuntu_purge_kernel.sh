#!/usr/bin/env bash
# ubuntu, admin, delete old kernel

sudo apt-mark showmanual | grep -E "linux-.*[0-9]" | grep -v "hwe" | xargs -r sudo apt-mark auto
sudo apt-get autoremove --purge
