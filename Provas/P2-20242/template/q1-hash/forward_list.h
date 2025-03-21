
#ifndef _FORWARD_LIST_H_
#define _FORWARD_LIST_H_

typedef void* data_type;
typedef struct ForwardList ForwardList;
typedef struct ListIterator ListIterator;

typedef struct FlNode
{
    data_type value;
    struct FlNode *next;
} FlNode;

struct ForwardList
{
    FlNode *head;
    int size;
};

struct ListIterator
{
    FlNode *current;
};

FlNode *node_construct(data_type value, FlNode *next);
void node_destroy(FlNode *n);

ForwardList *forward_list_construct();
void forward_list_push_front(ForwardList *l, data_type data);
int forward_list_size(ForwardList *l);
data_type forward_list_pop_front(ForwardList *l);
void forward_list_destroy(ForwardList *l);

#endif
