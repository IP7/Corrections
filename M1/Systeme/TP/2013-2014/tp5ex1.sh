display=`man ls | grep -n "display[^a-zA-Z0-9]\|display$" | wc -l`
list=`man ls | grep -n "list[^a-zA-Z0-9]\|list$" | wc -l`
echo "display=$display, list=$list"