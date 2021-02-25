#!/bin/bash

[[ -d "$1" ]] || {
	echo "Usage: $(basename $0) <busybox_sourcedir>"
	exit 1
}

bbsrc="$(realpath $1)"
cd $(dirname $0)

[[ -e config.new ]] && {
	echo -n "config.new exists already. delete? [y|n] "
	read ans
	case "$ans" in
	y|Y)
		rm -rf config.new
		;;
	n|N)
		;;
	*)
		echo "what is '$ans'?"
		exit 1
	esac
}
mkdir -p config.new

# store config paths relative to $bbsrc into an array
readarray -t configs <<< $(cd "$bbsrc"; find . -type f -name Config.in)

# copy each config into config.new
for config in "${configs[@]}"; do
	mkdir -p config.new/$(dirname $config)
	cp "$bbsrc/$config" "config.new/$config"
done

# store defined config symbols into an array
readarray -t symbols <<< $(grep -hr '^config ' config.new | cut -d' ' -f2)

### customize busybox config system for OpenADK

cd config.new

# no extra mainmenu, allow replacing PREFIX
sed -i -e 's/^mainmenu/# mainmenu/' -e 's,./_install,@IDIR@,' Config.in

# prefix all symbols with BUSYBOX_ to create a namespace
# limit replacement to lines containing given keywords to
# not mess up help texts and prompts too much
keywords='\(config\|depends\|range\|select\|default\|^if \)'
sympipe=$(IFS='|'; echo "${symbols[*]}" | sed -e 's/|/\\|/g')
sympipe_s='/'$keywords'/s/\b\('$sympipe'\)\b/BUSYBOX_\1/g'

# fix path of all sourced files
source_s='s,^\(source *\)\([^ ]*\)$,\1package/busybox/config/\2,'

sed -i -e "$sympipe_s" -e "$source_s" "${configs[@]}"
