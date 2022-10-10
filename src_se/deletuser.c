#include "head.h"
#include "head2.h"

extern struct msg *head;       //在线用户的链表头   

void delete_user (struct msg *h, int fd)
{
        struct msg *p, *s;

        for(p = h; p != NULL; p = p->next)
        {
                if(p->next->fd == fd)
                {
                        s = p->next;
                        p->next = s->next;
                        free(s);
                        break;
                }
        }
}
