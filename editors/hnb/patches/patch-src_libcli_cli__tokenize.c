$NetBSD$

1. Replaced int with uint64_t.
2. Replaced pointer to int type cast with a macro to help
   convert the pointer to uint64_t.

This prevents the segfault on startup in amd64 systems.

--- src/libcli/cli_tokenize.c.orig	2003-03-14 03:23:22.000000000 +0000
+++ src/libcli/cli_tokenize.c
@@ -36,8 +36,8 @@ enum actions{
 
 enum tokenize_string_states{
 	s_null=0,
-	s_start, 	
-	s_quo,	
+	s_start,
+	s_quo,
 	s_delimit,
 	s_wpp,
 	s_wescape,
@@ -68,14 +68,14 @@ typedef struct {
 
 #ifdef TESTit
 #define cli_getstring dummy_get_variable
-static char * dummy_get_variable(char *name){
+static char * dummy_get_variable(unsigned char *name){
 	static char *dummy="<variable expansion not implemented yet>";
 	return dummy;
 }
 #endif
 
 #ifndef TESTit
-char *cli_getstring(char *variable);
+char *cli_getstring(unsigned char *variable);
 #endif
 
 static rule_entry state_table[s_end][max_rules];
@@ -102,7 +102,7 @@ static void init_state_table(void){
 	memset(state_table,0,sizeof(state_table));
 	a(s_start,	s_start,	c_ws,	0,0,		a_eat,			0);
 	a(s_start,	s_quo,		NULL,	0,255,		a_nil,			0);
-	
+
 	a(s_quo,	s_delimit,	c_ws,	0,0,		a_eat+a_new,	0);
 	a(s_quo,	s_qpp,		NULL,	'"','"',	a_eat,			0);
 	a(s_quo,	s_app,		NULL,	'\'','\'',	a_eat,			0);
@@ -119,19 +119,19 @@ static void init_state_table(void){
 	a(s_wpp,	s_quo,		NULL,	'\0','\0',	a_nil,			0);
 	a(s_wpp,	s_wvar,		NULL,	'$','$',	a_eat+a_varclear,0);
 	a(s_wpp,	s_wpp,		NULL,	0,255,		a_eat+a_store,	0);
-	
+
 	a(s_wvar,	s_wvar,		NULL,	'a','z',	a_varstore+a_eat,0);
 	a(s_wvar,	s_wvar,		NULL,	'A','Z',	a_varstore+a_eat,0);
 	a(s_wvar,	s_wvar,		NULL,	'0','9',	a_varstore+a_eat,0);
 	a(s_wvar,	s_wvar,		NULL,	'_','_',	a_varstore+a_eat,0);
 	a(s_wvar,	s_wpp,		NULL,	0,255,		a_varinsert,	0);
-	
+
 	a(s_wescape, s_quo,	NULL,	'\0','\0',		a_nil,			0);
 	a(s_wescape, s_wpp,	NULL,	'n','n',		a_eat+a_store,	'\n');
 	a(s_wescape, s_wpp,	NULL,	'r','r',		a_eat+a_store,	'\r');
 	a(s_wescape, s_wpp,	NULL,	't','t',		a_eat+a_store,	'\t');
 	a(s_wescape, s_wpp,	NULL,	0,255,			a_eat+a_store,	0);
-	
+
 	a(s_qpp,	s_quo,	NULL,	'"','"',	a_eat,			0);
 	a(s_qpp,	s_qescape,	NULL,	'\\','\\',	a_eat,			0);
 	a(s_qpp,	s_quo,		NULL,	'\0','\0',	a_nil,			0);
@@ -182,9 +182,9 @@ char **argv_tokenize(char *input_string)
 	char *output;
 	unsigned char varname[MAX_VARNAMELENGTH]="";
 	int varname_pos=0;
-	
+
 	init_state_table();
-		
+
 	/* first we calculate and allocate space for the argv structure */
 	{
 		int state=s_start;
@@ -204,7 +204,7 @@ char **argv_tokenize(char *input_string)
 				}
 				r++;
 			}
-			
+
 			if(r->action & a_varclear){
 				varname_pos=0;
 				varname[varname_pos]=0;
@@ -227,7 +227,7 @@ char **argv_tokenize(char *input_string)
 
 			state=r->next_state;
 		}
-		
+
 		argv=malloc(	 sizeof(char*)*(tokens+1)            /* pointers and terminating NULL */
 							+sizeof(char)*(total_length+tokens)); /* character data and NUL for all strings */
 		memset(argv, 0, sizeof(char*)*(tokens+1)+sizeof(char)*(total_length+tokens));
@@ -236,7 +236,7 @@ char **argv_tokenize(char *input_string)
 		argv[0]=output;
 	}
 
-	/* then we make a second pass and actually fill up the argv structure */	
+	/* then we make a second pass and actually fill up the argv structure */
 	{
 		int state=s_start;
 		int tokens=0;
@@ -253,7 +253,7 @@ char **argv_tokenize(char *input_string)
 				}
 				r++;
 			}
-			
+
 
 			if(r->action & a_varclear){
 				varname_pos=0;
@@ -282,9 +282,9 @@ char **argv_tokenize(char *input_string)
 			}
 			state=r->next_state;
 		}
-		argv[tokens]=NULL;	
+		argv[tokens]=NULL;
 	}
-	
+
 	return argv;
 }
 
@@ -309,7 +309,7 @@ int main(int argc, char **argv){
 		tlargv++;
 	}
 	}
-	
+
 	printf("\n");
 	free(largv);
 	return 0;
