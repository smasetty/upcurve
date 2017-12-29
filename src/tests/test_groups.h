#ifndef TESTGROUPS_H
#define TESTGROUPS_H value

extern const TestFamily* graphs_init(void);

typedef const TestFamily* (*InitFunction)(void);

struct TestGroups {
    const char *name;
    InitFunction init;
} groups[] = 
{
    {.init = graphs_init},
};

#endif /* ifndef TESTGROUPS_H */
