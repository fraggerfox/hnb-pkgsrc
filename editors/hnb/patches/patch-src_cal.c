$NetBSD$

In NetBSD-1.6.2, the <stdlib.h> header uses the word bufsize as a
parameter name in a function prototype. The "file.h" header #defines
bufsize to 4096, which leads to a parser error.

Above fix made by rilling on 2005/03/11

1. Replaced int with uint64_t.
2. Replaced pointer to int type cast with a macro to help
   convert the pointer to uint64_t.

This prevents the segfault on startup in amd64 systems.

--- src/cal.c.orig	2003-03-14 01:06:36.000000000 +0000
+++ src/cal.c
@@ -19,32 +19,32 @@
  */
 
 /**************/
+#include <stdlib.h>
+#include <stdio.h>
+#include <time.h>
+
 #include "tree.h"
 #include "cli.h"
 #include "ui.h"
 #include "file.h"
 
-#include <stdlib.h>
-#include <stdio.h>
-#include <time.h>
-
-static char *const wday[] = 
+static char *const wday[] =
 	{ "Sun", "Mon", "Tue",  "Wed", "Thu", "Fri", "Sat", "   "};
 
 static char *const mname[] = {
 	  "", "January", "February", "March", "April", "May" ,"June", "July",
 	  "August", "September", "October", "November" , "December"};
 
-static int insert_cal(int argc, char **argv, void *data){
+static uint64_t insert_cal(int argc, char **argv, void *data){
 	Node *pos=(void *)data;
 
 	int year;
 	int month;
 	import_state_t ist;
-	
+
 	if( (argc!=3) || (atoi(argv[1])>12 )){
 		cli_outfunf("usage: %s <month> <year>", argv[0]);
-		return (int)data;
+		return PTR_TO_UINT64(data);
 	}
 
 	month=atoi(argv[1]);
@@ -54,7 +54,7 @@
 	if(year<2000){  /* nasty,.. 2yk like fix,.. but,.. it's just here */
 		year+=2000;
 	}
-	
+
 	init_import(&ist, pos);
 	{
 		char tmpstr[40];
@@ -76,7 +76,7 @@
 			while(tdata.tm_mon==month-1){
 				sprintf (tmpstr,"%s%c%02i\n", wday[tdata.tm_wday], (tdata.tm_wday==0 || tdata.tm_wday==6)?'_':' ', tdata.tm_mday);
 				import_node_text(&ist, 1, tmpstr);
-				
+
 				/* I prefer not to plan on this level
 				import_node_text(&ist, 2, "08:00");
 				import_node_text(&ist, 2, "09:00");
@@ -94,9 +94,9 @@
 				mktime (&tdata);
 			}
 		}
-	}	
+	}
 
-	return (int)pos;
+	return PTR_TO_UINT64(pos);
 }
 
 /*
