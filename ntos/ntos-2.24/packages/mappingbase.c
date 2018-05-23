#ifdef LATTICE
#include "/lpc_incl.h"
#else
#include "../lpc_incl.h"
#endif

// Rewrite by Hcifml on 2005/5/1
#define POP_ERR(x)  {\
                        pop_n_elems(st_num_arg);\
                        error(x);\
                    }

// Copy from mapping.c to do mapping building by Clode
INLINE_STATIC svalue_t *insert_in_mapping (mapping_t * m, char * key) {
    svalue_t lv;
    svalue_t *ret;
    
    lv.type = T_STRING;
    lv.subtype = STRING_CONSTANT;
    lv.u.string = key;
    ret = find_for_insert(m, &lv, 1);
    /* lv.u.string will have been converted to a shared string */
    free_string(lv.u.string);
    return ret;
}

//
// mb_set()
//
#ifdef F_MB_SET
void
f_mb_set (void) {
    int i, j;
    unsigned short type;
    object_t *ob;
    svalue_t *value;
    mapping_t *map;
    char *src, *dst;
    char *tmpstr;

    switch (st_num_arg)
    {
        case 4:
            if(sp->type == T_OBJECT)
                ob = sp->u.ob;
            else
                POP_ERR("Bad argment 4 to efun mb_set()\nExpect : Object\n")
            if((sp-1)->type == T_STRING) 
                tmpstr = (sp-1)->u.string;
            else
                POP_ERR("Bad argment 3 to efun mb_set()\nExpect : String\n")
            break;
        case 3:
            if(sp->type == T_MAPPING) {
                map = sp->u.map;
                goto set_pop;
            } else if(sp->type == T_STRING) {
                ob = current_object;
                tmpstr = sp->u.string;
            } else if(sp->type == T_OBJECT) {
                ob = sp->u.ob;
                tmpstr = "dbase";
            } else
                POP_ERR("Bad argment 3 to efun mb_set()\nExpect : Mapping or String or Object\n")
            break;
        case 1:
            ob = current_object;
            tmpstr = "dbase";
            break;
        default:
            POP_ERR("Too many argments to efun mb_set()\n")
    }

    i = find_global_variable(ob->prog, tmpstr, &type, 0);
    if (i == -1) {
        pop_n_elems(st_num_arg);
        error("(set) %s 物件未宣告全域映射资料库变数。\n", ob->obname);
    }
    value = &ob->variables[i];
    if( value->type != T_MAPPING ) {
        pop_n_elems(st_num_arg);
        error("(set) %s 物件的资料库变数型态错误。\n", ob->obname);
    }   
    map = value->u.map;

set_pop:
    pop_n_elems(st_num_arg - 2);
   
    src = (sp-1)->u.string;
    dst = tmpstr = DMALLOC(SVALUE_STRLEN(sp-1) + 1, TAG_STRING, "set");
    j=0;
    
    while (*src) 
    {
        i=0;
        if( ++j > 20 )
        {
                pop_2_elems();
                error("(set) %s too deep mapping(20)。\n", ob->obname);
        }
        
        while (*src != '/' && *src)
        {
            *(dst+i) = *src++;
            i++;
        }
            
        if (*src == '/') 
        {
            while (*++src == '/');
            if(!i) continue;
        }
        *(dst+i) = '\0';
        
        if(!*src)
        {
                value = insert_in_mapping(map, dst);
                *value = *sp--;
                break;
        }
        
        value = find_string_in_mapping(map, tmpstr);
        
        if(value == &const0u || value->type != T_MAPPING)
        {
                value = insert_in_mapping(map, dst);
                value->type = T_MAPPING;
                value->u.map = allocate_mapping(0);
        }
        
        map = value->u.map;
        dst = tmpstr;
    }

    FREE(tmpstr);
    free_string_svalue(sp--);
    push_svalue(value);
}
#endif

//
// mb_query()
//
#ifdef F_MB_QUERY
void
f_mb_query (void) {
    int i;
    unsigned short type;
    svalue_t *value;
    object_t *ob;
    mapping_t *map;
    char *src, *dst;
    char *tmpstr;
    
    switch (st_num_arg)
    {
        case 3:
            if(sp->type == T_OBJECT)
                ob = sp->u.ob;
            else
                POP_ERR("Bad argment 3 to efun mb_query()\nExpect : Object \n");
            if((sp-1)->type == T_STRING)
                tmpstr = (sp-1)->u.string;
            else
                POP_ERR("Bad argment 2 to efun mb_query()\nExpect : String\n")
            break;
        case 2:
            if(sp->type == T_MAPPING) {
                map = sp->u.map;
                goto query_pop;
            } else if(sp->type == T_STRING) {
                tmpstr = sp->u.string;
                ob = current_object;
            } else if(sp->type == T_OBJECT) {
                tmpstr = "dbase";
                ob = sp->u.ob;
            } else
                POP_ERR("Bad argment 2 to efun mb_query()\nExpect : Mapping or String or Object\n")
            break;
        case 1:
            tmpstr = "dbase";
            ob = current_object;
            break;
        default:
            POP_ERR("Too many argments to efun mb_query()\n")
    }

    i = find_global_variable(ob->prog, tmpstr, &type, 0);
    if (i == -1) {
        pop_n_elems(st_num_arg);
        error("(set_temp) %s 物件未宣告全域映射资料库变数。\n", ob->obname);
    }
    value = &ob->variables[i];
    if( value->type != T_MAPPING ) {
        pop_n_elems(st_num_arg);
        error("(set_temp) %s 物件的资料库变数型态错误。\n", ob->obname);
    }   
    map = value->u.map;

query_pop:
    pop_n_elems(st_num_arg - 1);

    src = sp->u.string;
    dst = tmpstr = DMALLOC(SVALUE_STRLEN(sp) + 1, TAG_STRING, "query");
    
    while (*src) 
    {
        while (*src != '/' && *src)
            *dst++ = *src++;
        if (*src == '/') 
        {
            while (*++src == '/');
            if( dst == tmpstr ) continue;
        }
        *dst = '\0';
        value = find_string_in_mapping(map, tmpstr);

        if( value == &const0u ) break;
        if( value->type != T_MAPPING ) 
        {
            if(*src) value = &const0u;
            break;
        }
        map = value->u.map;
        dst = tmpstr;
    }

    FREE(tmpstr);
    free_string_svalue(sp--);
    push_svalue(value);
}
#endif


//
// mb_delete()
//

#ifdef F_MB_DELETE
void
f_mb_delete (void) {
    int i;
    unsigned short type;
    svalue_t *value, lv;
    object_t *ob;
    mapping_t *map;
    char *src, *dst, *tmpstr;
    
    switch (st_num_arg)
    {
        case 3:
            if(sp->type == T_OBJECT)
                ob = sp->u.ob;
            else
                POP_ERR("Bad argment 3 to efun mb_delete()\nExpect : Object \n")
            if((sp-1)->type == T_STRING)
                tmpstr = (sp-1)->u.string;
            else
                POP_ERR("Bad argment 2 to efun mb_delete()\nExpect : String\n")
            break;
        case 2:
            if(sp->type == T_MAPPING) {
                map = sp->u.map;
                goto delete_pop;
            } else if(sp->type == T_STRING) {
                tmpstr = sp->u.string;
                ob = current_object;
            } else if(sp->type == T_OBJECT) {
                tmpstr = "dbase";
                ob = sp->u.ob;
            } else
                POP_ERR("Bad argment 2 to efun mb_delete()\nExpect : Mapping or String or Object\n")
            break;
        case 1:
            tmpstr = "dbase";
            ob = current_object;
            break;
        default:
            POP_ERR("Too many argments to efun mb_delete()\n")
    }

    i = find_global_variable(ob->prog, tmpstr, &type, 0);
    if (i == -1) {
        pop_n_elems(st_num_arg);
        error("(delete) %s 物件未宣告全域映射资料库变数。\n", ob->obname);
    }
    value = &ob->variables[i];
    if( value->type != T_MAPPING ) {
        pop_n_elems(st_num_arg);
        error("(delete) %s 物件的资料库变数型态错误。\n", ob->obname);
    }   
    map = value->u.map;

delete_pop:
    pop_n_elems(st_num_arg - 1);

    src = sp->u.string;
    dst = DMALLOC(SVALUE_STRLEN(sp)+1, TAG_STRING, "delete");
    
    while (*src) 
    {
        i = 0;
        while (*src != '/' && *src)
        {
            *(dst+i) = *src++;
            i++;
        }
        if (*src == '/') 
        {
            while (*++src == '/');
            if(!i) continue;
        }

        *(dst+i) = '\0';
        
        value = find_string_in_mapping(map, dst);

        if( value == &const0u ) break;
        if(!*src)
        {
                lv.type = T_STRING;
                lv.subtype = STRING_CONSTANT;
                lv.u.string = dst;
                mapping_delete(map, &lv);
                FREE(dst);
                free_string_svalue(sp--);
                return;
        }
        if( value->type != T_MAPPING ) break;

        map = value->u.map;
    }

    FREE(dst);
    free_string_svalue(sp--);
}
#endif
