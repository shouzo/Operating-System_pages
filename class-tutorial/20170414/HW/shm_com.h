/* A common header file to describe the shared memory we wish to pass about. */

#define TEXT_SZ 10

struct shared_use_st {
    int written_by_you;
    int answer_by_you;
    int some_text[TEXT_SZ];
};

