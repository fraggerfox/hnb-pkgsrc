$NetBSD$

1. Replaced int with uint64_t.
2. Replaced pointer to int type cast with a macro to help
   convert the pointer to uint64_t.

This prevents the segfault on startup in amd64 systems.

--- src/ui_draw.c.orig	2003-03-10 00:44:29.000000000 +0000
+++ src/ui_draw.c
@@ -525,7 +525,7 @@ static struct {
 
 /* FIXME: make backup?,.. and make sure data is present,.., make possiblity to write back? */
 
-int display_format_cmd (int argc, char **argv, void *data)
+uint64_t display_format_cmd (int argc, char **argv, void *data)
 {
 	char *p = argv[1];
 	int width;
@@ -533,7 +533,7 @@ int display_format_cmd (int argc, char *
 	int col_no = 0;
 
 	if(argc<2){
-		return (int)data;
+		return PTR_TO_UINT64(data);
 	}
 
 	do {
@@ -618,7 +618,7 @@ int display_format_cmd (int argc, char *
 
 	col_def[col_no].type = col_terminate;
 
-	return (int) data;
+	return PTR_TO_UINT64(data);
 }
 
 
@@ -633,7 +633,7 @@ int display_format_cmd (int argc, char *
  *                   highlightmode: none, edit_mode: the position in the data
  *                   that should be highlighted,
  *                   completion: the number of matched chars in data
- *                   
+ *
  * @param draw_mode  1=draw, 0=test
  *
  * @return number of lines needed to draw item
