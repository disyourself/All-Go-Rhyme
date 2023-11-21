
#include <stdio.h>
#include <stdlib.h>

typedef struct String
{
    char *data;
    int len;
} String;

String *
initString ()
{
    String *s = (struct String *)malloc (sizeof (struct String));
    s->data = nullptr;
    s->len = 0;
    return s;
}

void
stringAssign (String *s, char *data)
{
    if (s->data)
        free (s->data);
    int len = 0;
    char *temp = data;
    while (*temp)
    {
        len++;
        temp++;
    }
    if (len == 0)
    {
        s->data = NULL;
        s->len = 0;
    }
    else
    {
        temp = data;
        s->len = len;
        s->data = (char *)malloc (sizeof (char) * (len + 1));
        for (int i = 0; i < len; i++, temp++)
            s->data[i] = *temp;
    }
}

void
printString (String *s)
{
    for (int i = 0; i < s->len; i++)
    {
        printf (i == 0 ? "%c " : "-> %c", s->data[i]);
    }
    printf ("\n");
}

void
printNext (int *next, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf (i == 0 ? "%d" : "-> %d", next[i] + 1);
    }
    printf ("\n");
}

int *
getNext (String *s)
{
    int *next = new int[s->len];
    int i = 0;
    int j = -1;
    next[0] = -1;
    while (i < s->len - 1)
    {
        if (j == -1 || s->data[i] == s->data[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }

    return next;
}

void
kmpMatch (String *master, String *sub, int *next)
{
    int i = 0, j = 0;

    while (i < master->len && j < sub->len)
    {
        if (j == -1 || master->data[i] == sub->data[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }
    if (j == sub->len)
        printf ("kmp match success.\n");
    else
        printf ("kmp match failed.\n");
}

int
main (int argc, char **argv)
{
    String *s = initString ();
    stringAssign (s, argv[1]);
    printString (s);

    String *s1 = initString ();
    stringAssign (s1, argv[2]);
    printString (s1);

    int *next = getNext (s1);
    printNext (next, s1->len);

    kmpMatch (s, s1, next);

    return 0;
}
