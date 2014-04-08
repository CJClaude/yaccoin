./src/yaccoind  getpeerinfo | egrep "(addr|subver)"  | egrep -o "\"[^\"]*[0-9.][^\"]*\"" | xargs -L2 echo | sort -k2r | column -ts" "
