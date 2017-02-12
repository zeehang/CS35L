tr [:upper:] [:lower:] | sed -e 's/<u>//g' | sed -e 's/<\/u>//g' | sed -e '/<\/table/,/<\/html>/d' | sed -e '/<!doctype/,/<tr>/d' | sed -e '/<tr/,/<\/td>/d' | sed -e '/<td width/,/<\/tr>/d' | sed -e '/td valign/,/<\/td>/d' | sed 's/<tr>//' | sed 's/<td>//' | sed 's/<\/tr>//' | sed 's/<\/td>//' | tr -d '[:blank:]' | tr " " "\n" | tr "," "\n" | tr "\`" "\'" | grep -v "[^uioeahlwnm'kp]" | sort -u

#sed 's/\<<u>>//g' 
#tr -cs 'A-Z''\''''a-z' '[\n*]' < hwnwdseng.htm | comm -23 - words


