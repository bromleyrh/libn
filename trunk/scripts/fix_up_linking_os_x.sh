#!/bin/sh

testdir=tests

get_cur_libn_path()
{
	otool -L "$1" | grep libn | cut -d ' ' -f 1 | cut -f 2-
}

replace_path()
{
	install_name_tool -change "$@"
}

case $1 in
	"${testdir}"*)
		curpath=$(get_cur_libn_path "$1")
		test -z "$curpath" && exit 0
		replace_path "$curpath" "$2" "$1";;
esac

# vi: set noexpandtab sw=4 ts=4:
