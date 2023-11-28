#include <stdio.h>
#include <stdlib.h>

#include "fakana_mombamomba.h"

int main(int argc, char **argv){
  

  return 0;
}

void manomboka_cgi(char *karazany, char *lohateny){
	printf(	"Context-Type:text/%s\n\n"
		"<!DOCTYPE html>\n"
		"<html>\n"
		"<head>\n"
		"	<meta charset=\"UTF-8\" />\n"
		"	<title>%s</title>\n"
		"	<link rel=\"stylesheet\" href=\"http://www.config.mg/style.css\">\n"
		"</head>\n"
		"<body>\n"
		, karazany, lohateny);
}

void mamarana_cgi(){
	printf(	"</body>\n"
		"</html> \n"
	      );
}



