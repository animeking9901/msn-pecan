#!/bin/sh

if test -f version
then
	cat version
else
	git describe --tags
fi
