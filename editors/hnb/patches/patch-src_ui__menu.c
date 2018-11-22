$NetBSD$

1. Replaced int with uint64_t.
2. Replaced pointer to int type cast with a macro to help
   convert the pointer to uint64_t.

This prevents the segfault on startup in amd64 systems.

--- src/ui_menu.c.orig	2003-03-14 03:54:52.000000000 +0000
+++ src/ui_menu.c
@@ -20,17 +20,17 @@ static MenuT menu[MENU_MAX_COLS][MENU_MA
 static int xpos_forcol(int colno){
 	int cumulated=0;
 	int col;
-	
+
 	for(col=0;col<colno;col++)
 		cumulated+=menu[col][0].width+1;
-		
+
 	return cumulated;
 }
 
 static void draw_menu(Node *pos, int cur_col, int cur_row){
 	int row,col;
 	ui_draw(pos,"",0);
-		
+
 	for(col=0;col<MENU_MAX_COLS;col++)
 		for(row=0;row<MENU_MAX_ROWS;row++){
 			if((row==0 || col==cur_col) && menu[col][row].label){
@@ -52,7 +52,7 @@ static void draw_menu(Node *pos, int cur
 				addch((col==cur_col && row==cur_row)?'<':' ');
 			}
 		}
-		move (LINES - 1, COLS - 1);	
+		move (LINES - 1, COLS - 1);
 }
 
 static Node *menu_do(Node *pos){
@@ -61,7 +61,7 @@ static Node *menu_do(Node *pos){
 	Tbinding *c;
 
 	while(!stop){
-		draw_menu(pos,col,row);	
+		draw_menu(pos,col,row);
 		c=parsekey(ui_input(),ui_scope_nodeedit);
 		switch(c->action){
 			case ui_action_right:
@@ -93,7 +93,7 @@ static Node *menu_do(Node *pos){
 					row++;
 				else
 					while(row>1)
-						row--;				
+						row--;
 				break;
 			case ui_action_cancel:
 				stop=1;
@@ -109,10 +109,10 @@ static Node *menu_do(Node *pos){
 	return pos;
 }
 
-static int cmd_menu(int argc,char **argv,void *data){
+static uint64_t cmd_menu(int argc,char **argv,void *data){
 	Node *pos=(Node *)data;
 	if(argc==1){ /* draw menu */
-		return (int)menu_do(pos);
+		return PTR_TO_UINT64(menu_do(pos));
 	} else if(argc==4){
 		char *submenu=argv[1];
 		char *label=argv[2];
@@ -132,17 +132,17 @@ static int cmd_menu(int argc,char **argv
 			menu[col][0].label=strdup(submenu);
 			menu[col][0].width=strlen(submenu);
 		}
-		
+
 		while(menu[col][row].label)
 			row++;
 		menu[col][row].label=strdup(label);
 		menu[col][row].command=strdup(command);
 		menu[col][row].width=strlen(label);
-		
+
 		if(menu[col][row].width>menu[col][0].width)
-			menu[col][0].width=menu[col][row].width;	
+			menu[col][0].width=menu[col][row].width;
 	}
-	return(int)pos;
+	return PTR_TO_UINT64(pos);
 }
 
 /*
