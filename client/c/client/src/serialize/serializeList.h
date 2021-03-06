/*
 *  Copyright Beijing 58 Information Technology Co.,Ltd.
 *
 *  Licensed to the Apache Software Foundation (ASF) under one
 *  or more contributor license agreements.  See the NOTICE file
 *  distributed with this work for additional information
 *  regarding copyright ownership.  The ASF licenses this file
 *  to you under the Apache License, Version 2.0 (the
 *  "License"); you may not use this file except in compliance
 *  with the License.  You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing,
 *  software distributed under the License is distributed on an
 *  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 *  KIND, either express or implied.  See the License for the
 *  specific language governing permissions and limitations
 *  under the License.
 */
#ifndef __SERIALIZE_LIST_H
#define __SERIALIZE_LIST_H
#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif

struct serialize_list {
	void *head;
	int typeId;
	struct serialize_list *tail;
};

static inline struct serialize_list* list_cons(void* head, int typeId, struct serialize_list* tail) {
	struct serialize_list* cell;

	cell = (struct serialize_list*) malloc(sizeof(struct serialize_list));
	cell->head = head;
	cell->tail = tail;
	cell->typeId = typeId;
	return cell;
}
static inline struct serialize_list* list_cons_back(void* head, int typeId, struct serialize_list* tail) {
	struct serialize_list* cell;
	struct serialize_list* lastCell;
	cell = (struct serialize_list*) malloc(sizeof(struct serialize_list));
	cell->head = head;
	cell->tail = NULL;
	cell->typeId = typeId;
	lastCell = tail->tail;
	while (lastCell) {
		if (lastCell->tail) {
			lastCell = lastCell->tail;
		} else {
			break;
		}
	}
	if (lastCell) {
		lastCell->tail = cell;
	} else {
		tail->tail = cell;
	}
	return tail;
}

static inline int list_length(struct serialize_list* list) {
	int i = 0;
	while (list) {
		i += 1;
		list = list->tail;
	}
	return i;
}

static inline struct serialize_list* list_nth(int indx, struct serialize_list* list) {
	while (indx-- != 0) {
		if (list->tail)
			list = list->tail;
		else
			return 0;
	}
	return list;
}

static inline void list_remove_head(struct serialize_list** list) {
	if ((*list)->tail) {
		struct serialize_list* tail = (*list)->tail;
		*(*list) = *tail;
		free(tail);
	} else {
		free(*list);
		(*list) = 0;
	}
}

static inline void list_remove_elem(struct serialize_list** list, void* elem) {
	while (*list) {
		if ((*list)->head == elem)
			list_remove_head(list);
		list = &((*list)->tail);
	}
}

static inline void list_mapcar(struct serialize_list* list, void(*function)(void*)) {
	while (list) {
		(*function)(list->head);
		list = list->tail;
	}
}

static inline struct serialize_list** list_find(struct serialize_list** list, void* elem) {
	while (*list) {
		if ((*list)->head == elem)
			return list;
		list = &((*list)->tail);
	}
	return NULL;
}

static inline void list_free(struct serialize_list* list) {
	if (list) {
		list_free(list->tail);
		free(list);
	}
}

#ifdef __cplusplus
}
#endif

#endif
