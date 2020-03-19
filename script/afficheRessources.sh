#!/bin/sh

grep  ":" json/Json.json | cut -f1 -d ',' | cut -f1 -d '[' 
#grep -n " " script/.temp
