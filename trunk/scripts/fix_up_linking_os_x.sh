#!/bin/sh

testdir=tests

get_cur_libn_path()
{
	otool -L "$1" | sed -n \
		-e '1d' \
		-e 's/libn/libn/; t found' \
		-e 'b' \
		-e ':found' \
		-e 's/^[[:space:]]*//' \
		-e 's/ (compatibility version .*, current version .*)$//' \
		-e 'p'
}

replace_path()
{
	install_name_tool -change "$@"
}

set -eu
set -o pipefail

case $1 in
	"${testdir}"*)
		curpath=$(get_cur_libn_path "$1")
		test -z "$curpath" && exit 0
		replace_path "$curpath" "$2" "$1";;
esac

# vi: set noexpandtab sw=4 ts=4:
