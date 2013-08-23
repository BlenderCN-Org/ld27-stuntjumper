#!/bin/bash
mkdir -p "$SRCROOT/../resources-pkg"
rm -f "$SRCROOT/../resources-pkg/*.zip"
pushd "$SRCROOT/../resources"
for f in *; do
	echo "Checking $f"
    if [ -d "$f" ]; then
		echo "Found dir $f"
        zip -r "$SRCROOT/../resources-pkg/$f" "$f"
    else
        zip "$SRCROOT/../resources-pkg/base.zip" "$f"
    fi
done
popd