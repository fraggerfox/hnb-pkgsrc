$NetBSD$

1. Replaced int with uint64_t.
2. Replaced pointer to int type cast with a macro to help
   convert the pointer to uint64_t.

This prevents the segfault on startup in amd64 systems.

--- src/libcli/cli.h.orig	2003-03-12 12:20:05.000000000 +0000
+++ src/libcli/cli.h
@@ -15,7 +15,7 @@
  * along with this program; if not, write to the Free Software
  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
  */
-/* helper function 
+/* helper function
 
 	takes a orig.inal string
 	a char array of 40 to put first word in
@@ -29,10 +29,13 @@
 #define LIBCLI_H
 
 #include <stdarg.h>
+#include <stdint.h>
+
+#define PTR_TO_UINT64(x) (uint64_t)(uintptr_t)(x)
 
 void argv_sanity(void);
 
-void cli_split(char *orig, char *head, char **tail);	
+void cli_split(char *orig, char *head, char **tail);
 
 void cli_add_help(char *name,char *helptext);
 
@@ -41,7 +44,7 @@ void cli_cleanup(void);
 void
 cli_add_item (char *name,
 		  int *integer, char *string,
-		  int (*func) (int argc,char **argv, void *data), char *usage);
+		  uint64_t (*func) (int argc,char **argv, void *data), char *usage);
 
 #define cli_add_int(name,integer,usage)\
 	cli_add_item (name, integer, NULL, NULL, usage)
@@ -52,13 +55,13 @@ cli_add_item (char *name,
 #define cli_add_command(name,func,usage) \
 	cli_add_item(name, NULL, NULL, func, usage)
 
-int cli_load_file(char *filename);
+uint64_t cli_load_file(char *filename);
 
 char *cli_complete (const char *commandline);	/* returns a completed commandline */
-int cli_docmd (char *commandline, void *data);	/* run commandline */
+uint64_t cli_docmd (char *commandline, void *data);	/* run commandline */
 
 
-extern void (*cli_outfun) (char *);	/* the outputting function 
+extern void (*cli_outfun) (char *);	/* the outputting function
 									   assign cli_outfun a void function that takes a string
 									   to use something other than printf
 									 */
