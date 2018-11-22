$NetBSD$

1. Replaced int with uint64_t.
2. Replaced pointer to int type cast with a macro to help
   convert the pointer to uint64_t.

This prevents the segfault on startup in amd64 systems.

--- src/tree_sort.c.orig	2003-03-14 00:12:44.000000000 +0000
+++ src/tree_sort.c
@@ -112,7 +112,7 @@ static Node *merge (Node *nodeA, Node *n
 	return thead;
 }
 
-/* 
+/*
 */
 static Node *node_mergesort (Node *head, int size, int (*cmp) (Node *a, Node *b))
 {
@@ -141,7 +141,7 @@ static int cmp_descending(Node *a,Node *
 	return cmp_todo(b,a);
 }
 
-static int sort_cmd (int argc, char **argv, void *data)
+static uint64_t sort_cmd (int argc, char **argv, void *data)
 {
 	Node *pos = (Node *) data;
 	int (*cmp) (Node *a, Node *b)=cmp_todo;
@@ -155,7 +155,7 @@ static int sort_cmd (int argc, char **ar
 	node_mergesort (node_top (pos), nodes_down (node_top (pos)) + 1, cmp);
 	if (node_left (pos))
 		node_left (pos)->right = node_top (pos);
-	return (int) pos;
+	return PTR_TO_UINT64(pos);
 }
 
 /*
