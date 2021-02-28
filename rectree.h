
#define ALLOC (rt*)calloc(1,sizeof(rt))


typedef struct rt{
    struct rt *alpha[26];
    char flag;
    char password[30];
}rt;


rt* checkUsername(char *username,rt *root);
rt *usernameAviable(char *username,rt *root);