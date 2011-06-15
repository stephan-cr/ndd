#include <stddef.h>

struct st {
    int x;
};

int main(void)
{
    struct st *s = NULL;
    return s->x;
}
