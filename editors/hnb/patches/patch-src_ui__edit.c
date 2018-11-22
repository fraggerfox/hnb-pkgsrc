$NetBSD$

1. Replaced int with uint64_t.
2. Replaced pointer to int type cast with a macro to help
   convert the pointer to uint64_t.

This prevents the segfault on startup in amd64 systems.

--- src/ui_edit.c.orig	2003-03-09 23:28:30.000000000 +0000
+++ src/ui_edit.c
@@ -28,7 +28,7 @@
 #include "evilloop.h"
 #include <stdlib.h>
 
-static int ui_edit_cmd (int argc, char **argv, void *data)
+static uint64_t ui_edit_cmd (int argc, char **argv, void *data)
 {
 	Tbinding *c;
 	int stop = 0;
@@ -46,7 +46,7 @@ static int ui_edit_cmd (int argc, char *
 
 	memset (input, 0, sizeof (input));
 
-	if (inputbuf[0]) {			/* there is data in the inputbuffer,.. 
+	if (inputbuf[0]) {			/* there is data in the inputbuffer,..
 								   we should not edit, but handle that
 								   data instead...  this doesn't really belong here,.. but the hack works
 								 */
@@ -61,7 +61,7 @@ static int ui_edit_cmd (int argc, char *
 			}
 		}
 		ui_current_scope = tempscope;
-		return (int) pos;
+		return PTR_TO_UINT64(pos);
 	}
 
 	node_backup = node_duplicate (pos);
@@ -208,7 +208,7 @@ static int ui_edit_cmd (int argc, char *
 	}
 	node_free (node_backup);
 	ui_current_scope = tempscope;
-	return (int) data;
+	return PTR_TO_UINT64(data);
 }
 
 int ui_getstr_loc (char *input, int x, int y, int maxlen)
