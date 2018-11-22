$NetBSD$

1. Replaced int with uint64_t.
2. Replaced pointer to int type cast with a macro to help
   convert the pointer to uint64_t.

This prevents the segfault on startup in amd64 systems.

--- src/ui_overlay.c.orig	2003-03-14 00:35:14.000000000 +0000
+++ src/ui_overlay.c
@@ -31,12 +31,12 @@
 #include "evilloop.h"
 
 /*	ui_overlay
-	
+
 	current node
 	dirtyness
-	
+
 	scope_no (and thus name and help texts)
-	
+
 	status
 	status_display_counter,..
 */
@@ -44,11 +44,11 @@
 
 static char *ui_helptext[MAX_SCOPES] = { 0 };
 
-static int ui_helptext_cmd (int argc, char **argv, void *data)
+static uint64_t ui_helptext_cmd (int argc, char **argv, void *data)
 {
 	if(argc>1)
 		ui_helptext[ui_current_scope] = strdup (argv[1]);
-	return (int) data;
+	return PTR_TO_UINT64(data);
 }
 
 #define MAX_STATUS_LINES 100
@@ -129,7 +129,7 @@ void set_status (char *message)
 }
 
 
-static int ui_status_cmd (int argc, char **argv, void *data)
+static uint64_t ui_status_cmd (int argc, char **argv, void *data)
 {
 	if(argc==2 && (!strcmp(argv[1],"-c") || !strcmp(argv[1],"--clear"))){
 		status_ttl=0;
@@ -138,7 +138,7 @@ static int ui_status_cmd (int argc, char
 		if(!ui_inited)
 		cli_outfun(argv[1]);
 	}
-	return (int) data;
+	return PTR_TO_UINT64(data);
 }
 
 
