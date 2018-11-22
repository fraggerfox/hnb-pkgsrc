$NetBSD$

1. Replaced int with uint64_t.
2. Replaced pointer to int type cast with a macro to help
   convert the pointer to uint64_t.

This prevents the segfault on startup in amd64 systems.

--- src/libcli/cli.c.orig	2003-03-14 02:32:38.000000000 +0000
+++ src/libcli/cli.c
@@ -15,7 +15,7 @@
  * along with this program; if not, write to the Free Software
  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
  */
- 
+
 #include <stdlib.h>
 #include <stdio.h>
 #include <string.h>
@@ -44,9 +44,9 @@ static void default_output(char *data){
 	char *bp=tbuf,
 	     *wp=word,
 		 *dp=data;
-	
+
 	*bp=*wp='\0';
-	
+
 	while(1+1==2){
 		if(isspace((unsigned char)*dp) || *dp=='\0'){
 			if( (bp-tbuf) + (wp-word) +1 < COLS){
@@ -80,7 +80,7 @@ static void default_output(char *data){
 		dp++;
 	}
 	printf("%s\n",tbuf);
-	
+
 	free(word);
 	free(tbuf);
 }
@@ -99,7 +99,7 @@ int cli_width = 40;
 void cli_outfunf(char *format, ...){
 	va_list arglist;
 	char buf[128];
-	
+
 	va_start( arglist, format );
 	vsnprintf(buf,127,format,arglist);
 	va_end(arglist);
@@ -113,7 +113,7 @@ static  int item_matches (const char *it
 
 typedef struct ItemT {
 	char *name;					/* what the user types */
-	int (*func) (int argc,char **argv, void *data);	/* function that is the command */
+	uint64_t (*func) (int argc,char **argv, void *data);	/* function that is the command */
 	int *integer;				/* pointer to integer (set to NULL if string) */
 	char *string;				/* pointer to string (set to NULL if integer) */
 	char *usage;					/* helptext for this command */
@@ -130,7 +130,7 @@ static ItemT *items = NULL;
 void
 cli_add_item (char *name,
 		  int *integer, char *string,
-		  int (*func) (int argc,char **argv, void *data), char *usage)
+		  uint64_t (*func) (int argc,char **argv, void *data), char *usage)
 {
 	ItemT *titem = items;
 
@@ -191,8 +191,8 @@ void cli_add_help(char *name, char *help
 }
 
 
-static int help (int argc,char **argv, void *data);
-static int vars (int argc,char **argv, void *data);
+static uint64_t help (int argc,char **argv, void *data);
+static uint64_t vars (int argc,char **argv, void *data);
 
 static int inited = 0;
 
@@ -224,13 +224,13 @@ static void init_cli (void)
 
 int cli_calllevel=0;
 
-int cli_docmd (char *commandline, void *data)
+uint64_t cli_docmd (char *commandline, void *data)
 {
 	int largc=0;
 	char **largv;
-	
+
 	ItemT *titem = items;
-	int ret=(int)data;
+	uint64_t ret=(uint64_t)data;
 	cli_calllevel++;
 
 	if (cli_precmd)
@@ -249,13 +249,13 @@ int cli_docmd (char *commandline, void *
 		free(largv);
 		return ret;
 	}
-	
+
 	while (titem) {
 		if (!strcmp (largv[0], titem->name)) {
 			if (is_command (titem)) {
 
 				ret=titem->func (largc,largv, data);
-				
+
 				if (cli_postcmd)
 					cli_postcmd (commandline);
 				cli_calllevel--;
@@ -285,7 +285,7 @@ int cli_docmd (char *commandline, void *
 					cli_postcmd (commandline);
 				cli_calllevel--;
 
-				free(largv);				
+				free(largv);
 				return ret;
 			}
 		}
@@ -296,7 +296,7 @@ int cli_docmd (char *commandline, void *
 	if (cli_postcmd)
 		cli_postcmd (commandline);
 	cli_calllevel--;
-	
+
 	free(largv);
 	return ret;
 }
@@ -382,7 +382,7 @@ char *cli_complete (const char *commandl
 
 /* internal commands */
 
-static int help (int argc,char **argv, void *data)
+static uint64_t help (int argc,char **argv, void *data)
 {
 	if (argc == 1) {		/* show all help */
 		ItemT *titem = items;
@@ -410,17 +410,17 @@ static int help (int argc,char **argv, v
 						cli_outfun ("");
 						cli_outfun(titem->help);
 					}
-					return(int)data;
+					return(uint64_t)data;
 				}
 			}
 			titem = titem->next;
 		}
 		cli_outfunf ("unknown command '%s'", argv[1]);
 	}
-	return(int)data;	
+	return(uint64_t)data;
 }
 
-static int vars (int argc, char **argv, void *data)
+static uint64_t vars (int argc, char **argv, void *data)
 {
 	ItemT *titem = items;
 
@@ -446,7 +446,7 @@ static int vars (int argc, char **argv, 
 
 	cli_outfunf ("----------------");
 	cli_outfunf ("to change a variable: \"variablename newvalue\"");
-	return(int)data;
+	return(uint64_t)data;
 }
 
 char *cli_getstring(char *variable){
@@ -467,7 +467,7 @@ char *cli_getstring(char *variable){
 
 #include <stdio.h>
 
-int cli_load_file(char *filename){
+uint64_t cli_load_file(char *filename){
 	char buf[255];
 	FILE *file;
 
