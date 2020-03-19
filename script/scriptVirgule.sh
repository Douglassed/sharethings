#!/bin/sh

nbligne=`grep -c "^" $1`
nbligne=`expr $nbligne - 2`
head -"$nbligne" $1>.temp
tail -2 $1 | head -1 | cut -f1 -d ',' >> .temp
echo '}'>>.temp
cat .temp>$1
rm .temp
