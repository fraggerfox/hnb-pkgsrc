$NetBSD$

1. Replaced int with uint64_t.
2. Replaced pointer to int type cast with a macro to help
   convert the pointer to uint64_t.

This prevents the segfault on startup in amd64 systems.

--- src/file.c.orig	2003-03-13 22:55:13.000000000 +0000
+++ src/file.c
@@ -150,7 +150,7 @@ int file_check (char *filename)
 }
 
 
-static int cmd_save (int argc,char **argv, void *data)
+static uint64_t cmd_save (int argc,char **argv, void *data)
 {
 	Node *pos = (Node *) data;
 
@@ -167,10 +167,10 @@ static int cmd_save (int argc,char **arg
 			docmd (node_root (pos), buf);
 		}
 	}
-	return (int) pos;
+	return PTR_TO_UINT64(pos);
 }
 
-static int cmd_revert (int argc,char **argv, void *data)
+static uint64_t cmd_revert (int argc,char **argv, void *data)
 {
 	Node *pos = (Node *) data;
 
@@ -181,11 +181,11 @@ static int cmd_revert (int argc,char **a
 			sprintf (buf, "import_%s %s", prefs.format, prefs.db_file);
 			node_free(pos);
 			pos=tree_new();
-			
+
 			pos=docmd (pos, buf);
 		}
 	}
-	return (int) pos;
+	return PTR_TO_UINT64(pos);
 }
 
 
