BASE=https://www.openadk.org/distfiles
TARGET=$1
CONTROL=$2
VERSION=$3
ARCH=$4

WD=$(pwd)

mkdir -p "$TARGET/CONTROL"
grep '^[^(Version|Architecture)]' "$CONTROL" > "$TARGET/CONTROL/control"
grep '^Maintainer' "$CONTROL" 2>&1 >/dev/null || \
        echo "Maintainer: Waldemar Brodkorb <wbx@openadk.org>" >> "$TARGET/CONTROL/control"
grep '^Priority' "$CONTROL" 2>&1 >/dev/null || \
        echo "Priority: optional" >> "$TARGET/CONTROL/control"
grep '^Source' "$CONTROL" 2>&1 >/dev/null || {
        pkgbase=$(echo "$WD" | sed -e "s|^$ADK_TOPDIR/||g")
        [ "$pkgbase" = "$WD" ] && src="N/A" || src="$BASE"
        echo "Source: $src" >> "$TARGET/CONTROL/control"
}
echo "Version: $VERSION" >> "$TARGET/CONTROL/control"
echo "Architecture: $ARCH" >> "$TARGET/CONTROL/control"
chmod 644 "$TARGET/CONTROL/control"
