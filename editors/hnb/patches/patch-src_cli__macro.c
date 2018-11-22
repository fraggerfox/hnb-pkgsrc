$NetBSD$

1. Replaced int with uint64_t.
2. Replaced pointer to int type cast with a macro to help
   convert the pointer to uint64_t.

This prevents the segfault on startup in amd64 systems.

--- src/cli_macro.c.orig	2003-03-09 20:44:27.000000000 +0000
+++ src/cli_macro.c
@@ -26,7 +26,7 @@
 #include <ctype.h>
 #include <string.h>
 
-static void (*precmd_backup) (char *)=NULL;	
+static void (*precmd_backup) (char *)=NULL;
 
 typedef struct MacroT{
 	char *name;
@@ -76,11 +76,11 @@ static Node *do_macro(MacroT *macro, Nod
 		pos=docmd(pos,*curcmd);
 		curcmd++;
 	}
-	
+
 	return pos;
 }
 
-static int cmd_macro (int argc, char **argv, void *data)
+static uint64_t cmd_macro (int argc, char **argv, void *data)
 {
 	Node *pos=(Node *)data;
 	if(argc==1){
@@ -88,7 +88,7 @@ static int cmd_macro (int argc, char **a
 	} else if(argc==2){
 		MacroT *tmacro=lookup_macro(argv[1]);
 		if(tmacro){
-			return (int)do_macro(tmacro,pos);
+			return PTR_TO_UINT64(do_macro(tmacro,pos));
 		} else {
 			cli_outfunf("no such macro defined '%s'",argv[1]);
 		}
@@ -97,7 +97,7 @@ static int cmd_macro (int argc, char **a
 		if(!strcmp(argv[1],"define") ){
 			if(lookup_macro(argv[2])){
 				cli_outfunf("error macro %s already exist,.. this might turn out badly,.. " ,argv[2]);
-				return (int) pos;
+				return PTR_TO_UINT64(pos);
 			} else {
 				MacroT *tmacro;
 				if(!macro){
@@ -116,10 +116,10 @@ static int cmd_macro (int argc, char **a
 				precmd_backup=cli_precmd;
 				cli_precmd=macro_pre_command;
 			}
-			
+
 		}
 	}
-	return (int) pos;
+	return PTR_TO_UINT64(pos);
 }
 
 
