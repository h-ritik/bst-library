/* please take a glance at the shared main codes to get an idea about givig input */
/* caution : insertion and deletion is done one by one */


/* generic print function */
void printTree(void(* pri)(const void*));
/* generic insert function */
void insert(void* _New,size_t t,int(*comp)(const void*,const void*));
/* generic search function */
void search(void* _New,int (*comp)(const void*,const void*));
/* generic delete function */
void delete_it (void* _New,int (*comp)(const void*, const void*));