#!/bin/ksh

if [ -n "$1" ]
then
        echo ""

        utns="$(echo "$1" | awk '{print toupper($0)'})"

        awk "BEGIN{found=0}
        /^${utns}.*[ ,=]/ { found=1; print; next; }
        /^ /            { if(found){ print; } next; }
                        { if (found) { exit; } } " tnsnames.ora
        echo ""
else
        echo ""
        echo "No Alias given."
        echo ""
fi
