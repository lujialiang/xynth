/***************************************************************************
    begin                : Sun Mar 18 2007
    copyright            : (C) 2007 by Alper Akcan
    email                : distchx@yahoo.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

typedef struct s_xml_node_attr_s s_xml_node_attr_t;
typedef struct s_xml_node_s s_xml_node_t;
typedef struct s_xml_data_s s_xml_data_t;

struct s_xml_node_attr_s {
	char *name;
	char *value;
	int dontparse;
};

struct s_xml_node_s {
	char *name;
	char *value;
	s_list_t *attrs;
	s_list_t *nodes;
	s_xml_node_t *parent;
	int dontparse;
};

struct s_xml_data_s {
	char *path;
	s_xml_node_t *active;
	s_xml_node_t *root;
	s_xml_node_t *elem;
};

int s_xml_node_path_normalize (char *out, int len);
s_xml_node_t * s_xml_node_get_path_ (s_xml_node_t *node, char *path);
s_xml_node_t * s_xml_node_get_path (s_xml_node_t *node, char *path);
char * s_xml_node_get_value (s_xml_node_t *node);
char * s_xml_node_get_path_value (s_xml_node_t *node, char *path);
s_xml_node_attr_t * s_xml_node_get_attr (s_xml_node_t *node, char *attr);
char * s_xml_node_get_attr_value (s_xml_node_t *node, char *attr);
int s_xml_node_dublicate (s_xml_node_t *node, s_xml_node_t **dub);
int s_xml_node_attr_dublicate (s_xml_node_attr_t *attr, s_xml_node_attr_t **dub);
s_xml_node_t * s_xml_node_get_parent (s_xml_node_t *node, char *name);
int s_xml_node_attr_init (s_xml_node_attr_t **attr);
int s_xml_node_attr_uninit (s_xml_node_attr_t *attr);
int s_xml_node_init (s_xml_node_t **node);
int s_xml_node_uninit (s_xml_node_t *node);
void s_xml_parse_start (void *xdata, const char *el, const char **xattr);
void s_xml_parse_end (void *xdata, const char *el);
void s_xml_parse_character_fixup (char *out);
void s_xml_parse_character (void *xdata, const char *txt, int txtlen);
int s_xml_parse_buffer (s_xml_node_t **node, char *buffer, unsigned int len);
int s_xml_parse_file (s_xml_node_t **node, char *file);
