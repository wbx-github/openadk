# newline
N="
"

append() {
	local var="$1"
	local value="$2"
	local sep="${3:- }"

	eval "export -- \"$var=\${$var:+\${$var}\${value:+\$sep}}\$value\""
}

load_modules() {
	if [ -d "/lib/modules/$(uname -r)" ]; then
  		(sed "s,^[^#][^[:space:]]*,insmod /lib/modules/$(uname -r)/&.ko," $* | sh 2>&- || :)
	fi
}

user_exists() {
	grep -q "^$1:" $IPKG_INSTROOT/etc/passwd 2>&-
}

group_exists() {
	grep -q "^$1:" $IPKG_INSTROOT/etc/group 2>&-
}

service_exists() {
	grep -q "^$1[[:space:]]*$2" $IPKG_INSTROOT/etc/services 2>&-
}

rcconf_exists() {
	grep -q "^#*$1=" $IPKG_INSTROOT/etc/rc.conf 2>&-
}

add_user() {
	user_exists $1 || {
		echo "adding user $1 to /etc/passwd"
		echo "$1:x:$2:${3:-$2}:$1:${4:-/tmp}:${5:-/bin/false}" \
		    >>$IPKG_INSTROOT/etc/passwd
	}
}

add_group() {
	group_exists $1 || {
		echo "adding group $1 to /etc/group"
		echo "$1:x:$2:$3" >>$IPKG_INSTROOT/etc/group
	}
}

add_service() {
	service_exists $1 $2 || {
		echo "adding service $1 to /etc/services"
		printf '%s\t%s\n' "$1" "$2" >>$IPKG_INSTROOT/etc/services
	}
}

add_rcconf() {
	rcconf_exists $1 || {
		echo "adding service $1 to /etc/rc.conf"
		printf '%s="%s"\n' "${1}" "${2:-NO}" \
			>>$IPKG_INSTROOT/etc/rc.conf
	}
}

get_next_uid() {
	uid=1
	while grep "^[^:]*:[^:]*:$uid:" $IPKG_INSTROOT/etc/passwd \
	    >/dev/null 2>&1; do
		uid=$(($uid+1))
	done
	echo $uid
}

get_next_gid() {
	gid=1
	while grep "^[^:]*:[^:]*:$gid:" $IPKG_INSTROOT/etc/group \
	    >/dev/null 2>&1; do
		gid=$(($gid+1))
	done
	echo $gid
}
