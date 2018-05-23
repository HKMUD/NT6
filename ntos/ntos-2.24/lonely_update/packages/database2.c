

#ifdef LATTICE
#include "/lpc_incl.h"
#else
#include "../lpc_incl.h"
#endif

#define POP_ERR(x)  {\
    pop_n_elems(st_num_arg);\
    error(x);\
}

// Copy from mapping.c to do mapping building
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
// set()
//
#ifdef F_SET
void f_set () {
    int i, j;
    object_t *ob;
    svalue_t *data, *value = NULL;
    mapping_t *map;
    unsigned short type;
    char *src, *dst;
    char *tmpstr;

    /*
    if( st_num_arg == 3 )
    {
        ob = sp->u.ob;
        pop_stack();
    }
    else
        ob = current_object;
    */
    switch (st_num_arg)
    {
        case 4:
            if(sp->type == T_OBJECT)
                ob = sp->u.ob;
            else
                POP_ERR("Bad argment 4 to efun set()\nExpect : Object\n")
            if((sp-1)->type == T_STRING)
                tmpstr = (sp-1)->u.string;
            else
                POP_ERR("Bad argment 3 to efun set()\nExpect : String\n")
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
                POP_ERR("Bad argment 3 to efun set()\nExpect : Mapping or String or Object\n")
            break;
        case 2:
        case 1:
            ob = current_object;
            tmpstr = "dbase";
            break;
        default:
            POP_ERR("Too many argments to efun set()\n")
    }

    i = find_global_variable(ob->prog, tmpstr, &type, 0);
    if (i == -1) {
        pop_n_elems(st_num_arg);
        error("(set) %s 物件未宣告全域映射资料库变数。\n", ob->obname);
    }

    data = &ob->variables[i];

    if( data->type != T_MAPPING ) {
        pop_n_elems(st_num_arg);
        error("(set) %s 物件的资料库变数型态错误。\n", ob->obname);
    }

    map = data->u.map;

set_pop:
    pop_n_elems(st_num_arg - 2);

    src = (char *)(sp-1)->u.string;
    dst = tmpstr = (char *)DMALLOC(SVALUE_STRLEN(sp-1) + 1, TAG_STRING, "set");
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
// set_temp()
//
#ifdef F_SET_TEMP
void f_set_temp () {
    int i, j;
    object_t *ob;
    svalue_t *data, *value = NULL;
    mapping_t *map;
    unsigned short type;
    char *src, *dst;
    char *tmpstr;

    /*
    if( st_num_arg == 3 )
    {
        ob = sp->u.ob;
        pop_stack();
    }
    else
        ob = current_object;
    */
    switch (st_num_arg)
    {
        case 4:
            if(sp->type == T_OBJECT)
                ob = sp->u.ob;
            else
                POP_ERR("Bad argment 4 to efun set_temp()\nExpect : Object\n")
            if((sp-1)->type == T_STRING)
                tmpstr = (sp-1)->u.string;
            else
                POP_ERR("Bad argment 3 to efun set_temp()\nExpect : String\n")
            break;
        case 3:
            if(sp->type == T_MAPPING) {
                map = sp->u.map;
                goto set_tmp_pop;
            } else if(sp->type == T_STRING) {
                ob = current_object;
                tmpstr = sp->u.string;
            } else if(sp->type == T_OBJECT) {
                ob = sp->u.ob;
                tmpstr = "tmp_dbase";
            } else
                POP_ERR("Bad argment 3 to efun set_temp()\nExpect : Mapping or String or Object\n")
            break;
        case 2:
        case 1:
            ob = current_object;
            tmpstr = "tmp_dbase";
            break;
        default:
            POP_ERR("Too many argments to efun set_temp()\n")
    }

    i = find_global_variable(ob->prog, tmpstr, &type, 0);
    if (i == -1) {
        pop_n_elems(st_num_arg);
        error("(set_temp) %s 物件未宣告全域映射资料库变数。\n", ob->obname);
    }

    data = &ob->variables[i];

    if( data->type != T_MAPPING ) {
        pop_n_elems(st_num_arg);
        error("(set_temp) %s 物件的资料库变数型态错误。\n", ob->obname);
    }

    map = data->u.map;

set_tmp_pop:
    pop_n_elems(st_num_arg - 2);

    src = (char *)(sp-1)->u.string;
    dst = tmpstr = (char *)DMALLOC(SVALUE_STRLEN(sp-1) + 1, TAG_STRING, "set_temp");
    j=0;

    while (*src)
    {
        i=0;
        if( ++j > 20 )
        {
                pop_2_elems();
                error("(set_temp) %s too deep mapping(20)。\n", ob->obname);
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
// query()
//
// 多层次 mapping 结构搜寻
// 记忆体节省机制 shadow_ob 检查
// 只要有 shadow_ob 就只查 shadow_ob, shadow_ob 就算查不到也不会再查本体, 而是传回 0
//
/*
#ifdef F_QUERY
void f_query () {
    int idx;
    object_t *ob;
    unsigned short type;
    svalue_t *value, *shadow;
    char *src, *dst;
    mapping_t *map;
    char *tmpstr;

    if( st_num_arg==2 )
    {
        ob=sp->u.ob;
        pop_stack();
    }
    else
        ob = current_object;

    idx = find_global_variable(ob->prog, "dbase", &type, 0);
    if (idx == -1)
    {
        free_string_svalue(sp--);
        push_undefined();
        return;
    }
    value = &ob->variables[idx];

    if( value->type != T_MAPPING )
    {
        free_string_svalue(sp--);
        error("(query) %s 物件的资料库变数型态错误。\n", ob->obname);
    }

    shadow = find_string_in_mapping(value->u.map, "shadow_ob");

    if( shadow != &const0u && shadow->type == T_OBJECT && ob != shadow->u.ob )
    {
        idx = find_global_variable(shadow->u.ob->prog, "dbase", &type, 0);
        if (idx != -1)
        {
                value = &shadow->u.ob->variables[idx];

                if( value->type != T_MAPPING )
                        value = &ob->variables[idx];
                else
                        ob = shadow->u.ob;
        }
    }

    map = value->u.map;
    src = (char *)sp->u.string;
    dst = tmpstr = (char *)DMALLOC(SVALUE_STRLEN(sp) + 1, TAG_STRING, "query");

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
*/

//
// query()
//
// 多层次 mapping 结构搜寻
// 记忆体节省机制 shadow_ob 检查
// 先搜查本体,没有找到则搜查shadow_ob
//

#ifdef F_QUERY
void f_query () {
    int idx;
    object_t *ob;
    unsigned short type;
    svalue_t *value;
    char *src, *dst;
    mapping_t *map;
    char *tmpstr;

    /*
    if( st_num_arg==2 )
    {
        ob=sp->u.ob;
        pop_stack();
    }
    else
        ob = current_object;
    */
    switch (st_num_arg)
    {
        case 3:
            if(sp->type == T_OBJECT)
                ob = sp->u.ob;
            else
                POP_ERR("Bad argment 3 to efun query()\nExpect : Object \n");
            if((sp-1)->type == T_STRING)
                tmpstr = (sp-1)->u.string;
            else
                POP_ERR("Bad argment 2 to efun query()\nExpect : String\n")
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
                POP_ERR("Bad argment 2 to efun query()\nExpect : Mapping or String or Object\n")
            break;
        case 1:
            tmpstr = "dbase";
            ob = current_object;
            break;
        default:
            POP_ERR("Too many argments to efun query()\n")
    }

    idx = find_global_variable(ob->prog, tmpstr, &type, 0);
    if (idx == -1)
    {
        pop_n_elems(st_num_arg);
        push_undefined();
        return;
    }
    value = &ob->variables[idx];

    if( value->type != T_MAPPING )
    {
        pop_n_elems(st_num_arg);
        error("(query) %s 物件的资料库变数型态错误。\n", ob->obname);
    }

    map = value->u.map;

query_pop:
    pop_n_elems(st_num_arg - 1);

    src = (char *)sp->u.string;
    dst = tmpstr = (char *)DMALLOC(SVALUE_STRLEN(sp) + 1, TAG_STRING, "query");

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

    if( value == &const0u )
    {
        svalue_t *shadow;

        value = &ob->variables[idx];

        shadow = find_string_in_mapping(value->u.map, "shadow_ob");

        if( shadow != &const0u && shadow->type == T_OBJECT && ob != shadow->u.ob)
        {
            idx = find_global_variable(shadow->u.ob->prog, "dbase", &type, 0);

            if (idx != -1)
            {
                value = &shadow->u.ob->variables[idx];

                if( value->type == T_MAPPING )
                {
                    ob = shadow->u.ob;

                    map = value->u.map;
                    src = (char *)sp->u.string;
                    dst = tmpstr = (char *)DMALLOC(SVALUE_STRLEN(sp) + 1, TAG_STRING, "query");

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
                }
                else
                    value = &const0u;
            }
            else
                value = &const0u;
        }
        else
            value = &const0u;
    }

    free_string_svalue(sp--);
    push_svalue(value);
}
#endif

//
// query_temp()
//
// 多层次 mapping 结构搜寻
//
#ifdef F_QUERY_TEMP
void f_query_temp () {
    int idx;
    object_t *ob;
    unsigned short type;
    svalue_t *value;
    char *src, *dst;
    mapping_t *map;
    char *tmpstr;

    /*
    if( st_num_arg==2 ) {
        ob=sp->u.ob;
        pop_stack();
    } else
        ob = current_object;
    */

    switch (st_num_arg)
    {
        case 3:
            if(sp->type == T_OBJECT)
                ob = sp->u.ob;
            else
                POP_ERR("Bad argment 3 to efun query_temp()\nExpect : Object \n");
            if((sp-1)->type == T_STRING)
                tmpstr = (sp-1)->u.string;
            else
                POP_ERR("Bad argment 2 to efun query_temp()\nExpect : String\n")
            break;
        case 2:
            if(sp->type == T_MAPPING) {
                map = sp->u.map;
                goto query_tmp_pop;
            } else if(sp->type == T_STRING) {
                tmpstr = sp->u.string;
                ob = current_object;
            } else if(sp->type == T_OBJECT) {
                tmpstr = "dbase";
                ob = sp->u.ob;
            } else
                POP_ERR("Bad argment 2 to efun query_temp()\nExpect : Mapping or String or Object\n")
            break;
        case 1:
            tmpstr = "dbase";
            ob = current_object;
            break;
        default:
            POP_ERR("Too many argments to efun query_temp()\n")
    }

    idx = find_global_variable(ob->prog, tmpstr, &type, 0);
    if (idx == -1)
    {
        pop_n_elems(st_num_arg);
        push_undefined();
        return;
    }
    value = &ob->variables[idx];

    if( value->type != T_MAPPING )
    {
        pop_n_elems(st_num_arg);
        error("(query_temp) %s 物件的资料库变数型态错误。\n", ob->obname);
    }

    map = value->u.map;

query_tmp_pop:
    pop_n_elems(st_num_arg - 1);

    src = (char *)sp->u.string;
    dst = tmpstr = (char *)DMALLOC(SVALUE_STRLEN(sp) + 1, TAG_STRING, "query_temp");

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
// addn()
//
#ifdef F_ADDN
void f_addn () {
    int i, j;
    object_t *ob;
    unsigned short type;
    mapping_t *map;
    svalue_t *value;
    char *src, *dst;
    char *tmpstr;

    if( st_num_arg == 3 )
    {
        ob = sp->u.ob;
        pop_stack();
    }
    else
        ob = current_object;

    i = find_global_variable(ob->prog, "dbase", &type, 0);
    if (i == -1)
    {
        pop_2_elems();
        error("(addn) %s 物件未宣告全域映射资料库变数。\n", ob->obname);
    }

    value = &ob->variables[i];

    if( value->type != T_MAPPING )
    {
        pop_2_elems();
        error("(addn) %s 物件的资料库变数型态错误。\n", ob->obname);
    }

    map = value->u.map;
    src = (char *)(sp-1)->u.string;
    dst = tmpstr = (char *)DMALLOC(SVALUE_STRLEN(sp-1) + 1, TAG_STRING, "addn");
    j=0;

    while (*src)
    {
        i=0;
        if( ++j > 20 )
        {
                pop_2_elems();
                error("(addn) %s too deep mapping(20)。\n", ob->obname);
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

        value = find_string_in_mapping(map, tmpstr);

        if(!*src)
        {
                if( value == &const0u || value->type != T_NUMBER )
                {
                        value = insert_in_mapping(map, dst);
                        *value = *sp--;
                }
                else
                        value->u.number += (sp--)->u.number;
                break;
        }

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
// addn_temp()
//
#ifdef F_ADDN_TEMP
void f_addn_temp () {
    int i, j;
    object_t *ob;
    unsigned short type;
    mapping_t *map;
    svalue_t *value;
    char *src, *dst;
    char *tmpstr;

    if( st_num_arg == 3 )
    {
        ob = sp->u.ob;
        pop_stack();
    }
    else
        ob = current_object;

    i = find_global_variable(ob->prog, "tmp_dbase", &type, 0);
    if (i == -1)
    {
        pop_2_elems();
        error("(addn_temp) %s 物件未宣告全域映射资料库变数。\n", ob->obname);
    }

    value = &ob->variables[i];

    if( value->type != T_MAPPING )
    {
        pop_2_elems();
        error("(addn_temp) %s 物件的资料库变数型态错误。\n", ob->obname);
    }

    map = value->u.map;
    src = (char *)(sp-1)->u.string;
    dst = tmpstr = (char *)DMALLOC(SVALUE_STRLEN(sp-1) + 1, TAG_STRING, "addn_temp");
    j=0;

    while (*src)
    {
        i=0;
        if( ++j > 20 )
        {
                pop_2_elems();
                error("(addn_temp) %s too deep mapping(20)。\n", ob->obname);
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

        value = find_string_in_mapping(map, tmpstr);

        if(!*src)
        {
                if( value == &const0u || value->type != T_NUMBER )
                {
                        value = insert_in_mapping(map, dst);
                        *value = *sp--;
                }
                else
                        value->u.number += (sp--)->u.number;
                break;
        }

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
// delete()
//
#ifdef F_DELETE
void f_delete () {
    int i;
    object_t *ob;
    svalue_t *value, lv;
    mapping_t *map;
    unsigned short type;
    char *src, *dst, *tmpstr;

    /*
    if( st_num_arg == 2 )
    {
        ob = sp->u.ob;
        pop_stack();
    }
    else
        ob = current_object;
    */
    switch (st_num_arg)
    {
        case 3:
            if(sp->type == T_OBJECT)
                ob = sp->u.ob;
            else
                POP_ERR("Bad argment 3 to efun delete()\nExpect : Object \n")
            if((sp-1)->type == T_STRING)
                tmpstr = (sp-1)->u.string;
            else
                POP_ERR("Bad argment 2 to efun delete()\nExpect : String\n")
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
                POP_ERR("Bad argment 2 to efun delete()\nExpect : Mapping or String or Object\n")
            break;
        case 1:
            tmpstr = "dbase";
            ob = current_object;
            break;
        default:
            POP_ERR("Too many argments to efun delete()\n")
    }

    i = find_global_variable(ob->prog, tmpstr, &type, 0);
    if (i == -1)
    {
        pop_n_elems(st_num_arg);
        error("(delete) %s 物件未宣告全域映射资料库变数。\n", ob->obname);
    }

    value = &ob->variables[i];

    if( value->type != T_MAPPING )
    {
        pop_n_elems(st_num_arg);
        error("(delete) %s 物件的资料库变数型态错误。\n", ob->obname);
    }

    map = value->u.map;

delete_pop:
    pop_n_elems(st_num_arg - 1);

    src = (char *)sp->u.string;
    dst = (char *)DMALLOC(SVALUE_STRLEN(sp)+1, TAG_STRING, "delete");

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

//
// delete_temp()
//
#ifdef F_DELETE_TEMP
void f_delete_temp () {
    int i;
    object_t *ob;
    svalue_t *value, lv;
    mapping_t *map;
    unsigned short type;
    char *src, *dst, *tmpstr;

    /*
    if( st_num_arg == 2 )
    {
        ob = sp->u.ob;
        pop_stack();
    }
    else
        ob = current_object;
    */
    switch (st_num_arg)
    {
        case 3:
            if(sp->type == T_OBJECT)
                ob = sp->u.ob;
            else
                POP_ERR("Bad argment 3 to efun delete_temp()\nExpect : Object \n")
            if((sp-1)->type == T_STRING)
                tmpstr = (sp-1)->u.string;
            else
                POP_ERR("Bad argment 2 to efun delete_temp()\nExpect : String\n")
            break;
        case 2:
            if(sp->type == T_MAPPING) {
                map = sp->u.map;
                goto delete_tmp_pop;
            } else if(sp->type == T_STRING) {
                tmpstr = sp->u.string;
                ob = current_object;
            } else if(sp->type == T_OBJECT) {
                tmpstr = "tmp_dbase";
                ob = sp->u.ob;
            } else
                POP_ERR("Bad argment 2 to efun delete_temp()\nExpect : Mapping or String or Object\n")
            break;
        case 1:
            tmpstr = "tmp_dbase";
            ob = current_object;
            break;
        default:
            POP_ERR("Too many argments to efun delete_temp()\n")
    }

    i = find_global_variable(ob->prog, tmpstr, &type, 0);
    if (i == -1)
    {
        pop_n_elems(st_num_arg);
        error("(delete_temp) %s 物件未宣告全域映射资料库变数。\n", ob->obname);
    }

    value = &ob->variables[i];

    if( value->type != T_MAPPING )
    {
        pop_n_elems(st_num_arg);
        error("(delete_temp) %s 物件的资料库变数型态错误。\n", ob->obname);
    }

    map = value->u.map;

delete_tmp_pop:
    pop_n_elems(st_num_arg - 1);

    src = (char *)sp->u.string;
    dst = (char *)DMALLOC(SVALUE_STRLEN(sp)+1, TAG_STRING, "delete_temp");

    while(*src)
    {
        i = 0;

        while(*src != '/' && *src)
            *(dst+(i++)) = *src++;

        if(*src == '/')
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
