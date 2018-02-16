#ifndef TESTGROUPS_H
#define TESTGROUPS_H value

extern const TestFamily* graphs_init(void);
extern const TestFamily* matrix_init(void);
extern const TestFamily* strings_init(void);
extern const TestFamily* arrays_init(void);
extern const TestFamily* trees_init(void);
extern const TestFamily* backtrack_init(void);
extern const TestFamily* ll_init(void);
extern const TestFamily* stack_init(void);

typedef const TestFamily* (*InitFunction)(void);

struct TestGroups {
    const char *name;
    InitFunction init;
} groups[] = 
{
    {.init = graphs_init},
    {.init = matrix_init},
    {.init = strings_init},
    {.init = arrays_init},
    {.init = trees_init},
    {.init = backtrack_init},
    {.init = ll_init},
    {.init = stack_init},
};

#endif /* ifndef TESTGROUPS_H */
