
LAST=LAST-UPDATE
DEST=/media/billaud/ftp.mbillaud.fr/www/notes/

find HTML-PUBLIC ZIPS -type f -newer $LAST \
	 -exec cp -v {} $DEST \;
date > $LAST
