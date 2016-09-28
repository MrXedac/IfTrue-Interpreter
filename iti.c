#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "language.h"

void *exec_memory;
unsigned char *exec_ptr;
int exec_loop_ptr;
int ignoring_tokens = 0;

/* Reads token from file */
enum LANG_TOKEN read_token(FILE* source)
{
    char buffer[16]; /* Baaaaad */
    fscanf(source, "%s ", buffer);
    if(strcmp(buffer, SRC_LANG_INC) == 0)
        return LANG_INC;
    if(strcmp(buffer, SRC_LANG_DEC) == 0)
        return LANG_DEC;
    if(strcmp(buffer, SRC_LANG_PTR_INC) == 0)
        return LANG_PTR_INC;
    if(strcmp(buffer, SRC_LANG_PTR_DEC) == 0)
        return LANG_PTR_DEC;
    if(strcmp(buffer, SRC_LANG_PUTC) == 0)
        return LANG_PUTC;
    if(strcmp(buffer, SRC_LANG_GETC) == 0)
        return LANG_GETC;
    if(strcmp(buffer, SRC_LANG_WHILE) == 0)
        return LANG_WHILE;
    if(strcmp(buffer, SRC_LANG_ENDWHILE) == 0)
        return LANG_ENDWHILE;

    printf("Parse error: unknown token %s\n", buffer);
    exit(-1);
}

/* Processes a language token */
void process_token(enum LANG_TOKEN tok, FILE *src)
{
    switch(tok)
    {
        case LANG_INC:
            if(!ignoring_tokens) exec_ptr++;
            break;
        case LANG_DEC:
            if(!ignoring_tokens) exec_ptr--;
            break;
        case LANG_PTR_INC:
            if(!ignoring_tokens) (*exec_ptr)++;
            break;
        case LANG_PTR_DEC:
            if(!ignoring_tokens) (*exec_ptr)--;
            break;
        case LANG_PUTC:
            if(!ignoring_tokens) putchar(*exec_ptr);
            break;
        case LANG_GETC:
            if(!ignoring_tokens) (*exec_ptr) = getchar();
        case LANG_WHILE:
            exec_loop_ptr = ftell(src);
            if(!(*exec_ptr)) /* Tell our interpreter to ignore tokens until loop end if the condition is not fullfilled */
                ignoring_tokens = 1;
            else
                ignoring_tokens = 0;
            break;
        case LANG_ENDWHILE: 
            if(!ignoring_tokens) {
                fseek(src, exec_loop_ptr, SEEK_SET); /* Rewind the file to condition begin, and stop ignoring tokens */
                /* Check condition state */
                if(!(*exec_ptr))
                    ignoring_tokens = 1;
                else
                    ignoring_tokens = 0;
            }
            else ignoring_tokens = 0;
        default:
            break;
    }
}

/* Interpreter entrypoint */
int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("The all-mighty IfTrue Interpreter\n");
        printf("Usage: %s [source]\n", argv[0]);
        exit(-1);
    }
    FILE * src;
    src = fopen(argv[1], "r");
    if(src)
    {
        exec_memory = malloc(POOL_SIZE * sizeof(uint32_t));
        if(exec_memory) {
            exec_ptr = (unsigned char*)exec_memory;
            enum LANG_TOKEN tok;
            while(!feof(src)) {
                    tok = read_token(src);
                    process_token(tok, src);
            }
            fclose(src);
        } else {
            printf("Unable to allocate IfTrue pool.\n");
            exit(-1);
        }
    } else {
        printf("Unable to open source file.\n");
        exit(-1);
    }
}
