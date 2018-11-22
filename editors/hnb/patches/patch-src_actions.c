$NetBSD$

1. Replaced int with uint64_t.
2. Replaced pointer to int type cast with a macro to help
   convert the pointer to uint64_t.

This prevents the segfault on startup in amd64 systems.

--- src/actions.c.orig	2003-03-14 01:06:36.000000000 +0000
+++ src/actions.c
@@ -32,17 +32,17 @@ static char address[1024]="";*/
 static char web_command[255] = "galeon -n *";
 static char mail_command[255] = "rxvt -rv +sb -e mutt *";
 
-static int cmd_system(int argc, char **argv, void *data){
+static uint64_t cmd_system(int argc, char **argv, void *data){
 	Node *pos=(Node *)data;
 	int ui_was_inited = ui_inited;
 	if (argc>1) {
 		if (ui_was_inited)
-			ui_end ();			
+			ui_end ();
 		system (argv[1]);
 		if (ui_was_inited)
 			ui_init ();
 	}
-	return (int)pos;
+	return PTR_TO_UINT64(pos);
 }
 
 static int action_node (Node *node)
@@ -132,25 +132,25 @@ static int action_node (Node *node)
 }
 
 /*
- * this is simplistic approach,.. should perhaps have another one that checks for 
+ * this is simplistic approach,.. should perhaps have another one that checks for
  * url/email address substring,.. and launches an app based on that?
  *
  */
-static int cmd_action (int argc, char **argv, void *data)
+static uint64_t cmd_action (int argc, char **argv, void *data)
 {
 	Node *pos = (Node *) data;
 	Node *node = node_right (pos);
 
 	while (node) {
 		if (!action_node (node))
-			return (int) pos;
+			return PTR_TO_UINT64(pos);
 		node = node_down (node);
 	}
 	if (!action_node (pos)) {
-		return (int) pos;
+		return PTR_TO_UINT64(pos);
 	} else {
 		cli_outfunf ("nothing to do");
-		return (int) pos;
+		return PTR_TO_UINT64(pos);
 	}
 
 	/***
