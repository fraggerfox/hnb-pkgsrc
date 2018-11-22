$NetBSD$

1. Replaced int with uint64_t.
2. Replaced pointer to int type cast with a macro to help
   convert the pointer to uint64_t.

This prevents the segfault on startup in amd64 systems.

--- src/tree_todo.c.orig	2003-03-09 17:23:18.000000000 +0000
+++ src/tree_todo.c
@@ -108,7 +108,7 @@ int node_calc_complete (Node *node)
 
 static int prefs_bullet_empty = 0;	/*could be made a preference, but I'm not sure */
 
-/** 
+/**
 	@return -1, no todo information, 0 not started, 1..1000 = 1..100% , 2000 = done */
 int done_status (Node *a)
 {
@@ -184,13 +184,13 @@ int node_calc_size (Node *node)
 
 #define def_size 1
 
-/** 
+/**
     @param Node *node the node that we calculate for
 	@param *retsize a parameter to put accumulated size in
 
 	@return -1       no todo information,
-			 0       not started, 
-			 1..1000 1..100% , 
+			 0       not started,
+			 1..1000 1..100% ,
 			 2000    done            percentage
 */
 
@@ -260,7 +260,7 @@ int calc_percentage_size (Node *node, in
 
 #include "cli.h"
 
-static int toggle_todo_cmd (int argc, char **argv, void *data)
+static uint64_t toggle_todo_cmd (int argc, char **argv, void *data)
 {
 	Node *pos = (Node *) data;
 
@@ -271,15 +271,15 @@ static int toggle_todo_cmd (int argc, ch
 		node_unset(pos,"type");
 	}
 
-	return (int) pos;
+	return PTR_TO_UINT64(pos);
 }
 
-static int toggle_done_cmd (int argc, char **argv, void *data)
+static uint64_t toggle_done_cmd (int argc, char **argv, void *data)
 {
 	Node *pos = (Node *) data;
 
 	if (strcmp(fixnullstring(node_get(pos,"type")),"todo")) {	/* bail out if not todo info set */
-		return (int) pos;
+		return PTR_TO_UINT64(pos);
 	}
 
 	if (!strcmp(fixnullstring(node_get(pos,"done")),"yes")) {	/* bail out if not todo info set */
@@ -288,7 +288,7 @@ static int toggle_done_cmd (int argc, ch
 		node_set(pos,"done","yes");
 	}
 
-	return (int) pos;
+	return PTR_TO_UINT64(pos);
 }
 
 /*
