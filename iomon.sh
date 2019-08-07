#!/bin/sh

INTERVAL=5

dev=$1
if [ -z $dev ]; then
	echo "usage: $0 device [interval]"
	exit 1
fi

if [ ! -z $2 ]; then
	INTERVAL=$2
fi

stat=/sys/block/$dev/stat
if [ ! -f $stat ]; then
	echo "$stat doesn't exist"
	exit 1
fi

read f1 f2 f3 f4 f5 f6 f7 f8 f9 f10 f11 <$stat
r0=$f1
w0=$f5

while true
do
	sleep $INTERVAL

	read f1 f2 f3 f4 f5 f6 f7 f8 f9 f10 f11 <$stat
	r=$f1
	w=$f5

	rps=$((($r - $r0) / $INTERVAL))
	wps=$((($w - $w0) / $INTERVAL))

	echo "$rps $wps"

	r0=$r
	w0=$w
done
