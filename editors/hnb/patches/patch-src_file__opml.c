$NetBSD$

1. Replaced int with uint64_t.
2. Replaced pointer to int type cast with a macro to help
   convert the pointer to uint64_t.

This prevents the segfault on startup in amd64 systems.

--- src/file_opml.c.orig	2003-03-14 00:36:39.000000000 +0000
+++ src/file_opml.c
@@ -72,7 +72,7 @@ static void opml_export_nodes (FILE * fi
 			fprintf (file, " %s=\"%s\"", att->name, quoted);
 			free(quoted);
 			att=att->next;
-		 }		 
+		 }
 		}
 
 		if (node_right (node)) {
@@ -90,7 +90,7 @@ static void opml_export_nodes (FILE * fi
 	}
 }
 
-static int export_opml (int argc, char **argv, void *data)
+static uint64_t export_opml (int argc, char **argv, void *data)
 {
 	Node *node = (Node *) data;
 	char *filename = argc>=2?argv[1]:"";
@@ -103,7 +103,7 @@ static int export_opml (int argc, char *
 
 	if (!file) {
 		cli_outfunf ("opml export, unable to open \"%s\"", filename);
-		return (int) node;
+		return PTR_TO_UINT64(node);
 	}
 
 	fprintf (file, "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?><?pos=\"%s\"?>\n\
@@ -133,10 +133,10 @@ static int export_opml (int argc, char *
 
 	cli_outfunf ("opml export, wrote data to \"%s\"", filename);
 
-	return (int) node;
+	return PTR_TO_UINT64(node);
 }
 
-static int import_opml (int argc, char **argv, void *data)
+static uint64_t import_opml (int argc, char **argv, void *data)
 {
 	Node *node = (Node *) data;
 	char *filename = argc==2?argv[1]:"";
@@ -154,7 +154,7 @@ static int import_opml (int argc, char *
 	file = fopen (filename, "r");
 	if (!file) {
 		cli_outfunf ("opml import, unable to open \"%s\"", filename);
-		return (int) node;
+		return PTR_TO_UINT64(node);
 	}
 	s = xml_tok_init (file);
 	init_import (&ist, node);
@@ -164,7 +164,7 @@ static int import_opml (int argc, char *
 			cli_outfunf ("opml import error, parsing og '%s', line:%i %s", filename,
 						 s->line_no, rdata);
 			fclose (file);
-			return (int) node;
+			return PTR_TO_UINT64(node);
 		}
 		if (in_body) {
 			if (type == t_tag && !strcmp (rdata, "outline")) {
@@ -208,7 +208,7 @@ static int import_opml (int argc, char *
 
 	cli_outfunf ("opml import - imported \"%s\" %i lines", filename, s->line_no);
 	xml_tok_cleanup (s);
-	return (int) node;
+	return PTR_TO_UINT64(node);
 }
 
 
